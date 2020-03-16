#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structures.h"
#include"functions.h"

HashEntry* hash_table_init(int Buckets){
	HashEntry* Hash_table = malloc(Buckets*sizeof(struct HashEntry)); 
	for(int i = 0; i < Buckets; i++)
		Hash_table[i].head = NULL;


	return Hash_table;
}
int counter = 0;
HashEntry* create_bucket(HashEntry* HashTable,char* key,Bucket* bucket,int hash,int BucketSize){
	int free_space = 0;
	int pos = 0;

		free_space = BucketSize - sizeof(int) - sizeof(struct Bucket*);           //pame emfoleumena apo mesa pros ta eksw.
		int amount_entries = free_space/ENTRY_SIZE;
		Bucket* new_bucket = malloc(sizeof(struct Bucket));
		new_bucket->entries = malloc(amount_entries*sizeof(struct BucketEntry));  //entry size up to 20
		new_bucket->next = NULL;

		//printf("free space is  %d kai eimai to prwto sto bucket auto me hash value  %d\n",free_space,hash);
		for(int i = 0; i < amount_entries; i++){
			new_bucket->entries[i].key = malloc(20*sizeof(char));
			new_bucket->entries[i].root = NULL;
		}
	
		memcpy(new_bucket->entries[pos].key,key,20);

		new_bucket->counter = 1;
		if(bucket == NULL)
			HashTable[hash].head = new_bucket;
		else
			bucket->next = new_bucket;
		
		

	
	return HashTable;

}

int key_duplicate(HashEntry* Table,Bucket**  bucket_pos,char* key, int hash){
	Bucket* bucket = Table[hash].head;  // go to the hash ceil
	int current_entries = 0;
	if(bucket == NULL){
		return 0; // theres no duplicate,cause bucket == NULL
	}
	else{
		while(bucket->next != NULL){
			current_entries = bucket->counter;
			for(int i = 0; i < current_entries; i++){
				if(!strcmp(key,bucket->entries[i].key)){
					*(bucket_pos) = bucket;
					return i; // RETURN TRUE
				}
			}

			bucket = bucket->next;
		}

		current_entries = bucket->counter;
		for(int i = 0; i < current_entries; i++){	
			if(!strcmp(key,bucket->entries[i].key)){
				*(bucket_pos) = bucket;
				return i; 						// there is a duplciate so return true
			}
		}
	}
	return -1;  // means there is no duplicate
}

HashEntry* insert_bucket(HashEntry* table,int option,list_node* tail,int BucketSize,int hash){
	int free_space;
	int current_entries;
	Bucket* bucket =  table[hash].head;
	Bucket* bucket_pos;
	char* key = malloc(ENTRY_SIZE*sizeof(char));
	if(option == 1)
		key = tail->patient->diseaseID;
	else
		key = tail->patient->country;

	if(bucket == NULL){  // if bucket == NULL its empty.
		table = create_bucket(table,key,NULL,hash,BucketSize);
		table[hash].head->entries[0].root = insert_date(table[hash].head->entries[0].root,tail->patient,tail);
	}
	else{ 
		
		current_entries = bucket->counter;
		free_space = BucketSize - sizeof(int) - sizeof(struct Bucket*) - (current_entries*ENTRY_SIZE);
		int duplicate_pos = key_duplicate(table,&bucket_pos,key,hash);
		if(duplicate_pos < 0){
			while(bucket->next != NULL)
				bucket = bucket->next;

			if(free_space >= ENTRY_SIZE ){  // then it fits
					//printf("free space is %d  kai xwraw sto %d \n",free_space,hash);
				memcpy(bucket->entries[current_entries].key,key,20);
				bucket->entries[current_entries].root = insert_date(bucket->entries[current_entries].root,tail->patient,tail);
				bucket->counter++;


			}
			else{
				//printf(" wp kainourio bucket gt den xwraw sto %d \n",hash);
				table = create_bucket(table,key,bucket,hash,BucketSize);
				bucket->entries[0].root = insert_date(bucket->entries[0].root,tail->patient,tail);
			}
		}
		else{
			//printf(" ti ekana edw o poystis me diplo pointer\n");		// otk
			bucket_pos->entries[duplicate_pos].root = insert_date(bucket_pos->entries[duplicate_pos].root,tail->patient,tail);
		}		
	}



	return table;



}