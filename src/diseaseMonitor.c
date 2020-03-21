#define  _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"structures.h"
#include"functions.h"

Patient* create_patient(int id,char* firstname,char* lastname,char* diseaseID,char* country, char* entryDate, char* exitDate){
    Patient* patient = malloc(sizeof(struct Patient));
    struct tm date1,date2;
    patient->id = id;

    memset(&date1, 0, sizeof(struct tm));
	memset(&date2, 0, sizeof(struct tm));

    patient->firstname = malloc(ENTRY_SIZE*sizeof(char));
    strcpy(patient->firstname,firstname);


    patient->lastname = malloc(ENTRY_SIZE*sizeof(char));
    strcpy(patient->lastname,lastname);


    patient->diseaseID = malloc(ENTRY_SIZE*sizeof(char));
    strcpy(patient->diseaseID,diseaseID);

    patient->country = malloc(ENTRY_SIZE*sizeof(char));
    strcpy(patient->country,country);

    strptime(entryDate,"%d-%m-%Y",&date1);
    strptime(exitDate,"%d-%m-%Y",&date2);

    memcpy(&patient->entryDate,&date1,sizeof(struct tm));
    memcpy(&patient->exitDate,&date2,sizeof(struct tm));

    return patient;


}
int main(int argc, char *argv[]){
int opt,BucketSize,id;
int diseaseHashtableNumofEntries,countryHashtableNumofEntries;
char* fileName;
while((opt = getopt(argc, argv, "p:1:2:b:h")) != -1){
	switch(opt){
        case 'p':  
        	fileName = optarg;
           //printf("patients file: %s \n",fileName);
            break;  
        case 'h':
        	break;
        case '1':
        	diseaseHashtableNumofEntries = atoi(optarg);
        	//printf("diseaseHashtableNumofEntries %d\n",diseaseHashtableNumofEntries);
        	break;
        case '2':
        	countryHashtableNumofEntries = atoi(optarg);
       	 	//printf("countryHashtableNumofEntries %d\n",countryHashtableNumofEntries);
        	break;
        case 'b':
        	BucketSize = atoi(optarg);
        	if(!BucketSize || BucketSize < ENTRY_SIZE + sizeof(int) +  sizeof(struct Bucket*) ){
        		printf("Invalid bucket size, please type a number greater or equal than %ld\n",ENTRY_SIZE + sizeof(int) + sizeof(Bucket*));
        		return 0;
        	}
        	//printf("BucketSize %d\n",BucketSize);
        	break;
        case '?':
        	printf("Wrong option %c\n",optopt);
        	break;

        }  
}  

FILE *fp = fopen(fileName,"r");
HashEntry* diseaseHashtable = hash_table_init(diseaseHashtableNumofEntries);
HashEntry* countryHashtable = hash_table_init(countryHashtableNumofEntries);
 
treeNode* root = NULL;
list* patient_list = malloc(sizeof(struct List));
patient_list = list_init(patient_list);


if(!fp){
	printf("File does not exists\n");
	return 0;
}
int hash_value;
int buffer_size = 100;
char* buffer = malloc(buffer_size*sizeof(char)); // max characters in line


Patient* patient;
char* firstname,*lastname,*diseaseID,*country,*entryDate,*exitDate;


while(fgets(buffer,buffer_size,fp)){
	id = atoi(strtok(buffer," ")); // initialize
    firstname = strtok(NULL," ");
    lastname = strtok(NULL," ");
    diseaseID = strtok(NULL," ");
    country = strtok(NULL," ");
    entryDate = strtok( NULL, " ");
    exitDate = strtok(NULL," ");

    patient = create_patient(id,firstname,lastname,diseaseID,country,entryDate,exitDate);

    duplicate_id(patient_list,id);

    patient_list = insert_list(patient_list,patient); /// 1 2 3 4

	hash_value = hash(patient->diseaseID,diseaseHashtableNumofEntries);
	diseaseHashtable = insert_bucket(diseaseHashtable,1,patient_list->tail,BucketSize,hash_value);
    
    hash_value = hash(patient->country,countryHashtableNumofEntries);
    countryHashtable = insert_bucket(countryHashtable,2,patient_list->tail,BucketSize,hash_value);
}

char* command = NULL;
struct tm date1,date2;

memset(&date1, 0, sizeof(struct tm));
memset(&date2, 0, sizeof(struct tm));
char* temp = NULL;
char* uknown = NULL;
size_t size = 100;

label:
    printf("Type the aprpropiate command\n");
    while(getline(&buffer,&size,stdin) != -1){  
            
        
        command = strtok(buffer,"\n");
 		
 		temp = strtok(command," ");

            if(!strcmp(temp,"/exit")){

                printf("Deallocating memory..\n");
                free_list(patient_list);
                free(patient_list);
                free(buffer);
                free_hash_table(countryHashtable);
                free_hash_table(diseaseHashtable);
                break;
            }
            
            else if(!strcmp(temp,"/globalDiseaseStats")){
            	entryDate = strtok(NULL," ");
            	exitDate = strtok(NULL," ");
                if(entryDate && !exitDate){
                    printf("Please give valid exit date\n");
                    continue;
                }
                
            	globalDiseaseStats(diseaseHashtable,entryDate,exitDate);
                continue;

            }
            else if(!strcmp(temp,"/diseaseFrequency")){
            	diseaseID = strtok(NULL," ");
            	country = strtok(NULL," ");
            	entryDate = strtok(NULL," ");
            	exitDate = strtok(NULL," ");
            	if(exitDate == NULL){
            		exitDate = entryDate;
            		entryDate = country;
                    country = NULL;
            	    diseaseFrequency(diseaseHashtable,diseaseID,country,entryDate,exitDate);
            	}
                else{
                    diseaseFrequency(countryHashtable,diseaseID,country,entryDate,exitDate);
                }
                continue;
            }
            else if(!strcmp(temp,"/insertPatientRecord")){
                id = atoi(strtok(NULL," ")); // initialize
                firstname = strtok(NULL," ");
                lastname = strtok(NULL," ");
                diseaseID = strtok(NULL," ");
                country  = strtok(NULL," ");
                entryDate = strtok(NULL," ");
                exitDate = strtok(NULL," ");

                if(patient_list)
                    duplicate_id(patient_list,id);

                if(exitDate == NULL)
                    exitDate = "-";
                patient = create_patient(id,firstname,lastname,diseaseID,country,entryDate,exitDate);
                patient_list = insert_list(patient_list,patient); /// 1 2 3 4

                hash_value = hash(patient->diseaseID,diseaseHashtableNumofEntries);
                diseaseHashtable = insert_bucket(diseaseHashtable,1,patient_list->tail,BucketSize,hash_value);
    
                hash_value = hash(patient->country,countryHashtableNumofEntries);
                countryHashtable = insert_bucket(countryHashtable,2,patient_list->tail,BucketSize,hash_value);
                print_list(patient_list);
                continue;
            }
            else if(!strcmp(temp,"/recordPatientExit")){

                id = atoi(strtok(NULL," ")); // initialize
                exitDate = strtok(NULL," ");

                if(exitDate == NULL){
                    printf("Please give valid aguments\n");
                    continue;
                }
                strptime(exitDate,"%d-%m-%Y",&date2);
                insert_exitDate(patient_list,id,date2);
                continue;

            }
            else if(!strcmp(temp,"/numCurrentPatients")){
            	diseaseID = strtok(NULL," "); // initialize
            	numCurrentPatients(diseaseHashtable,diseaseID);
            }
            else if(!strcmp(temp,"/topk-Diseases")){

                int k  = atoi(strtok(NULL," "));
                country = strtok(NULL," ");
                entryDate = strtok(NULL," ");
                exitDate = strtok(NULL," ");
                if(entryDate && !exitDate){
                    printf("Please give valid exit date\n");
                    continue;
                }

                int size = differentRecs(diseaseHashtable);
                char** recs = array(diseaseHashtable);
                int temp_size = size;

                heap_node* temp1 = fill_heap(recs,countryHashtable,country,size,entryDate,exitDate,1);
                heap_node* root = NULL;
                                  
                for(int i = 0; i < temp_size; i++)
                    root = insert_heap(root,temp1[i].name,temp1[i].counter);

                heap_node* last = NULL;
                int last_level = -1;

                heap_node* max = malloc(sizeof(heap_node));
                max->name = malloc(ENTRY_SIZE*sizeof(char));

                for(int i = 0; i < k; i++){
                     if(temp_size == 0)
                        break;
                    last_level = -1;
                    find_last(root,-1,&last_level,&last);
                    root = pop_root(root,&last,temp_size--,&max);
                    printf("%s %d\n",max->name,max->counter); 

                }

                for(int i = 0; i < size; i++)
                    free(temp1[i].name);
                
                free(temp1);
                free(max->name);
                free(max);    
                free_heap(root);
                free_array(recs,size); 
                continue;
            }
            else if(!strcmp(temp,"/topk-Countries")){
                int k = atoi(strtok(NULL," "));
                diseaseID = strtok(NULL," ");
                entryDate = strtok(NULL," ");
                exitDate = strtok(NULL," ");
                if(entryDate && !exitDate){
                    printf("Please give valid exit date\n");
                    continue;
                }

                int size = differentRecs(countryHashtable);
                int temp_size = size;
                char** recs = array(countryHashtable);
                heap_node* temp1 = fill_heap(recs,diseaseHashtable,diseaseID,size,entryDate,exitDate,2);
                heap_node* root = NULL;
                 for(int i = 0; i < size ; i++)
                    root = insert_heap(root,temp1[i].name,temp1[i].counter);

                heap_node* last = NULL;
                int last_level = -1;

                heap_node* max = malloc(sizeof(heap_node));
                max->name = malloc(ENTRY_SIZE*sizeof(char));

                for(int i = 0; i < k; i++){
                    if(temp_size == 0)
                        break;
                    last_level = -1;
                    find_last(root,0,&last_level,&last);
                    root = pop_root(root,&last,temp_size--,&max);
                    printf("%s %d\n",max->name,max->counter); 


                }
                 for(int i = 0; i < size; i++)
                    free(temp1[i].name);
                
                free(temp1);
                free(max->name);
                free(max);    
                free_heap(root);
                free_array(recs,size); 
                continue;

            }

    }

    fclose(fp);
    printf("Terminating disease monitor...\n");
    return 0;

}

	








