 #include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"functions.h"
#include"hash_table.h"

struct tm string_to_date(char* string){

struct tm time_struct;
strptime(string,"%d-%m-%Y",&time_struct);
//printf("Month is %d\n",time_struct.tm_mon);
return time_struct;

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
						printf(" %s ",bucket->entries[counter].key);
						counter++;
					}
				bucket = bucket->next;
			}
			printf("\n");
		}	
	}


}

