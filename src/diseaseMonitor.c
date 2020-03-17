#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"structures.h"
#include"functions.h"

Patient* create_patient(int id,char* firstname,char* lastname,char* diseaseID,char* country, char* entryDate, char* exitDate){
    Patient* patient = malloc(sizeof(struct Patient));

    patient->id = id;

    patient->firstname = malloc(ENTRY_SIZE*sizeof(char));
    memcpy(patient->firstname,firstname,ENTRY_SIZE);


    patient->lastname = malloc(ENTRY_SIZE*sizeof(char));
    memcpy(patient->lastname,lastname,ENTRY_SIZE);


    patient->diseaseID = malloc(ENTRY_SIZE*sizeof(char));
    memcpy(patient->diseaseID,diseaseID,ENTRY_SIZE);

    patient->country = malloc(ENTRY_SIZE*sizeof(char));
    memcpy(patient->country,country,ENTRY_SIZE);

    strptime(entryDate,"%d-%m-%Y",&(patient->entryDate));
    strptime(exitDate,"%d-%m-%Y",&(patient->exitDate));

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
            printf("patients file: %s \n",fileName);
            break;  
        case 'h':
        	break;
        case '1':
        	diseaseHashtableNumofEntries = atoi(optarg);
        	printf("diseaseHashtableNumofEntries %d\n",diseaseHashtableNumofEntries);
        	break;
        case '2':
        	countryHashtableNumofEntries = atoi(optarg);
       	 	printf("countryHashtableNumofEntries %d\n",countryHashtableNumofEntries);
        	break;
        case 'b':
        	BucketSize = atoi(optarg);
        	if(!BucketSize || BucketSize < ENTRY_SIZE + sizeof(int) +  sizeof(struct Bucket*) ){
        		printf("Invalid bucket size, please type a number greater or equal than %ld\n",ENTRY_SIZE + sizeof(int) + sizeof(Bucket*));
        		return 0;
        	}
        	printf("BucketSize %d\n",BucketSize);
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
    

    patient_list = insert_list(patient_list,patient); /// 1 2 3 4

	hash_value = hash(patient->diseaseID,diseaseHashtableNumofEntries);
	diseaseHashtable = insert_bucket(diseaseHashtable,1,patient_list->tail,BucketSize,hash_value);
    
    hash_value = hash(patient->country,countryHashtableNumofEntries);
    countryHashtable = insert_bucket(countryHashtable,2,patient_list->tail,BucketSize,hash_value);

    
}
printf("Printing disease hash table\n");
//print_table(diseaseHashtable,diseaseHashtableNumofEntries);
//printf("\n");
//printf("Printing country hash table...\n\n");
//print_table(countryHashtable,countryHashtableNumofEntries);

//list_node* temp = patient_list->head;

//printf("Printing patients...\n");
//print_list(patient_list);

//printf("Printing tree...\n");
//printf("edw\n");
printf("\n\n");

char* command = malloc(sizeof(char)*100);
struct tm date1,date2;

memset(&date1, 0, sizeof(struct tm));
memset(&date2, 0, sizeof(struct tm));


entryDate = malloc(20);
exitDate = malloc(20);


label:
    while(1){  
        printf("Type the aprpropiate command\n");
        scanf("%s",command);
        
        buffer = strtok(command," ");
        
            if(!strcmp(buffer,"/exit")){
                printf("Terminating disease monitor...\n");
                exit(0);
            }
            else if(!strcmp(buffer,"/global")){
                strptime(strtok(NULL," "),"%d-%m-%Y",&date1);
                strptime(strtok(NULL," "),"%d-%m-%Y",&date2);
                break;

            }
    }



}

	








