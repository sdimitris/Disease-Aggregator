#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structures.h"
#include"functions.h"

HashEntry* hash_table_init(int Buckets){
	HashEntry* Hash_table = malloc(Buckets*sizeof(struct HashEntry)); 
	for(int i = 0; i < Buckets; i++){
		Hash_table[i].head = NULL;
	}

	Hash_table->buckets = Buckets;
	return Hash_table;
}
int counter = 0;
Bucket* create_bucket(char* key,int BucketSize){
	int free_space = 0;
	int pos = 0;

	free_space = BucketSize - sizeof(int) - sizeof(struct Bucket*);           //pame emfoleumena apo mesa pros ta eksw.
	int amount_entries = free_space/(ENTRY_SIZE);
	Bucket* new_bucket = malloc(sizeof(struct Bucket));
	new_bucket->entries = malloc(amount_entries*sizeof(struct BucketEntry));  //entry size up to 20
	new_bucket->next = NULL;

		//printf("free space is  %d kai eimai to prwto sto bucket auto me hash value  %d\n",free_space,hash);
		for(int i = 0; i < amount_entries; i++){
			new_bucket->entries[i].key = malloc(ENTRY_SIZE*sizeof(char));
			new_bucket->entries[i].root = NULL;
		}
	
		memcpy(new_bucket->entries[0].key,key,ENTRY_SIZE);
		new_bucket->counter = 1;
	
	return new_bucket;

}

int key_duplicate(HashEntry* Table,Bucket**  bucket_pos,char* key, int hash){
	Bucket* bucket = Table[hash].head;  // go to the hash ceil
	int current_entries = 0;
	if(bucket == NULL){
		return -1; // theres no duplicate,cause bucket == NULL
	}
	else{
		while(bucket != NULL){
			current_entries = bucket->counter;
			for(int i = 0; i < current_entries; i++){
				if(!strcmp(key,bucket->entries[i].key)){
					*(bucket_pos) = bucket;				
					return i; // RETURN TRUE
				}
			}

			bucket = bucket->next;
		}
	}
	return -1;  // means there is no duplicate
}

HashEntry* insert_bucket(HashEntry* table,int option,list_node* tail,int BucketSize,int hash){
	int free_space=0;
	int current_entries=0;
	Bucket* bucket_pos,*temp;
	int duplicate_pos = 0;
	char* key = malloc(ENTRY_SIZE*sizeof(char));
	if(option == 1)
		key = tail->patient->diseaseID;
	else
		key = tail->patient->country;

	Bucket* head =  table[hash].head;
	if(head == NULL){
		head = create_bucket(key,BucketSize);
		head->entries[0].root = insert_date(head->entries[0].root,tail->patient,tail);
		table[hash].head = head;
	}
	else if(duplicate_pos = key_duplicate(table,&bucket_pos,key,hash)  == -1){ //if there is no duplicate

		while(head->next != NULL)
			head = head->next;

		current_entries = head->counter;
		printf("current_entries %d\n",current_entries);
		free_space = BucketSize - sizeof(int) - sizeof(Bucket*) - (current_entries*ENTRY_SIZE);
		if(ENTRY_SIZE <= free_space){
			printf("free_space %d bs %d\n",free_space,BucketSize);

			printf("bucket %s\n",head->entries[0].key);
			printf("key %s\n",key);
			memcpy(head->entries[current_entries].key,key,ENTRY_SIZE);
			head->entries[current_entries].root = insert_date(head->entries[current_entries].root,tail->patient,tail);
			head->counter++;
		}
		else{

			temp =  create_bucket(key,BucketSize);
			head->next = temp;
			head->next->entries[0].root = insert_date(head->next->entries[0].root,tail->patient,tail);

		}
	}
	else{
		bucket_pos->entries[duplicate_pos].root = insert_date(bucket_pos->entries[duplicate_pos].root,tail->patient,tail);	
	}

	return table;

}


