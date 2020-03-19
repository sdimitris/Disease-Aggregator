#include<stdio.h>
#include<string.h>
#include"functions.h"
#include"structures.h"
#include<stdlib.h>


int differentRecs(HashEntry* table){
	Bucket* bucket = NULL;
	int counter = 0;
	int buckets = table->buckets;
	for( int i = 0; i < buckets; i++){
		bucket = table[i].head;
		if(bucket == NULL)
			continue;
		while(bucket != NULL){
			counter += bucket->counter;
			bucket = bucket->next;
		}
	}
	printf("%d\n",counter);
	return counter;
}

heap* make_heap(int size){

	heap* heap = malloc(size*sizeof(struct heap));
	for(int i = 0; i < size ;i++){
		heap->counter = 0;
		heap->key = malloc(ENTRY_SIZE*sizeof(char));
	}
	return heap;
}

heap* fill_heap(HashEntry* disease,heap* heap,char* country){
	int pivot = 0;
	Bucket* bucket = NULL;
	Bucket* target = NULL;
	char* virus = NULL;
	int pos = 0;
	int counter = 0;
	int buckets =	bucket->counter;
	for( int i = 0; i < buckets; i++){
		bucket = disease[i].head;
		if(bucket == NULL)
			continue;
		while(bucket != NULL){
			counter = bucket->counter;
			for(int j = 0; j < counter; j++){
				virus = bucket->entries[i].key;

			}
			bucket = bucket->next;

		}
		
		for(int i = 0; i < heap->counter; i++){


		}
	}





}




	
