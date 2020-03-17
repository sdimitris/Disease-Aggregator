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
void print_table(HashEntry* table,int buckets){
	int counter = 0;
	Bucket* bucket;
	for( int i = 0; i < buckets; i++){
		bucket = table[i].head;
		if(bucket == NULL){
			printf("Bucket: %d is empty\n",i);
			continue;
		}
		else{
			printf("Bucket: %d ",i);
			while(bucket != NULL){
				printf("\nKeys: ");
					counter = 0;
					while(counter < bucket->counter){
						printf("%s\n",bucket->entries[counter].key);
						print_tree(bucket->entries[counter].root);
						counter++;
					}
				bucket = bucket->next;
			}
			printf("\n");
		}	
	}

}

void print_patient(Patient* patient){

	printf("%s %s %s %s exitDate: %d-%d-%d\n",patient->firstname,patient->lastname,patient->diseaseID,patient->country,
		patient->exitDate.tm_mday,patient->exitDate.tm_mon,patient->exitDate.tm_year);
	return;

}




