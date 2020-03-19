 #include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"structures.h"
#include"functions.h"
struct tm string_to_date(char* string){

struct tm time_struct;
strptime(string,"%d-%m-%Y",&time_struct);
//printf("Month is %d\n",time_struct.tm_mon);
return time_struct;

}
int is_date(struct tm date){
	if( date.tm_year == 0 && date.tm_mday == 0 && date.tm_mon == 0 )
		return 0;
	else 
		return 1;
}

list* list_init(list* list){
	list->head = NULL;
	list->tail = NULL;
	return list;
}
int hash(char* string,int Buckets){
	int length = strlen(string);
	return  length % Buckets;
}

void print_hash_cell(HashEntry* table,int hash){
	Bucket* bucket = table[hash].head;
	int current_entries;
	if(bucket == NULL){
		printf("Bucket is empty\n");
		return;
	}
	else{
		current_entries = bucket->counter;
		printf("Bucket keys %d :",hash);
		while(bucket->next != NULL ){
			for(int i = 0; i < current_entries; i++)
				printf("Key %s ",bucket->entries[i].key);
	
		}
	}
}


void print_patient(Patient* patient){

	printf("%s %s %s %s exitDate: %d-%d-%d\n",patient->firstname,patient->lastname,patient->diseaseID,patient->country,
		patient->exitDate.tm_mday,patient->exitDate.tm_mon,patient->exitDate.tm_year);
	return;

}




