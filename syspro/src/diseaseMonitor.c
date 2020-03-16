#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"hash_table.h"
#include"functions.h"
#include"list.h"
#include"avl_tree.h"

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
list_node* patient_list =  NULL;    // initialize patient list
treeNode* root = NULL;



if(!fp){
	printf("File does not exists\n");
	return 0;
}
int hash_value;
int buffer_size = 100;
char* buffer = malloc(buffer_size*sizeof(char)); // max characters in line



Patient* patient;
char* firstname,*lastname,*diseaseID,*country,*entryDate,*exitDate;

//char* key = malloc(20*sizeof(char)); // key max 10 characters

while(fgets(buffer,buffer_size,fp)){

	id = atoi(strtok(buffer," ")); // initialize
    firstname = strtok(NULL," ");
    lastname = strtok(NULL," ");
    diseaseID = strtok(NULL," ");
    country = strtok(NULL," ");
    entryDate = strtok( NULL, " ");
    exitDate = strtok(NULL," ");
 

    patient = create_patient(id,firstname,lastname,diseaseID,country,entryDate,exitDate);

    //printf("id %d, first name: %s, disease: %s ,country %s: , year %d to %d\n",patient->id,patient->firstname,patient->diseaseID,patient->country,patient->entryDate.tm_year,patient->exitDate.tm_year);

    patient_list = insert_list(patient_list,patient);


	hash_value = hash(patient->diseaseID,diseaseHashtableNumofEntries);
	diseaseHashtable = insert_bucket(diseaseHashtable,1,patient,BucketSize,hash_value);

    hash_value = hash(patient->country,countryHashtableNumofEntries);
    countryHashtable = insert_bucket(countryHashtable,2,patient,BucketSize,hash_value);
    //insert(patient->entryDate)

}
printf("Printing disease hash table\n");
print_table(diseaseHashtable,diseaseHashtableNumofEntries);
printf("\n");
printf("Printing country hash table...\n\n");
print_table(countryHashtable,countryHashtableNumofEntries);

printf("Printing patients...\n");
print_list(patient_list);

printf("Printing tree...\n");
print_tree(root);

//free(hash_tables);
 
fclose(fp);
}
	








