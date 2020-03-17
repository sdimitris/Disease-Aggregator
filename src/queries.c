#include<stdio.h>
#include<time.h>
#include"functions.h"
#include"structures.h"

void globalDiseaseStats(HashEntry* disease,struct tm date1,struct tm date2){

treeNode* root;
int buckets = disease->buckets;
Bucket* bucket;
int current_entries = 0;
for(int i = 0; i < buckets; i++){
	bucket =  disease[i].head;
	if(bucket == NULL)
		continue;
	while(bucket != NULL){
		current_entries = bucket->counter;
		for( int j = 0; j < current_entries; j++){
			printf("Disease %s:\n",bucket->entries[j].key);
			print_tree_interval(bucket->entries[j].root,date1,date2);

		}
		bucket = bucket->next;
	}
}




} 