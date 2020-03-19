#include<stdio.h>
#include<time.h>
#include<string.h>
#include"functions.h"
#include"structures.h"

void globalDiseaseStats(HashEntry* disease,char* entryDate,char* exitDate){
	struct tm date1,date2;
	memset(&date1, 0, sizeof(struct tm));
	memset(&date2, 0, sizeof(struct tm));
	if( entryDate != NULL && exitDate != NULL){
		strptime(entryDate,"%d-%m-%Y",&date1);
   		strptime(exitDate,"%d-%m-%Y",&date2);
   	}
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
				if(entryDate != NULL)
					printf("Disease %s: %d\n",bucket->entries[j].key,count_interval(bucket->entries[j].root,date1,date2));
				else
					printf("Disease %s: %d\n",bucket->entries[j].key,count_tree_nodes(bucket->entries[j].root));
				
			}
			bucket = bucket->next;
		}
	}

} 
int virusStats(HashEntry* table,char* diseaseID,struct tm date1,struct tm date2){
	Bucket* bucket = NULL;
	int buckets = table->buckets;
	int current_entries = 0;
	for(int i = 0; i < buckets; i++){
		bucket =  table[i].head;
		if(bucket == NULL)
			continue;
		while(bucket != NULL){
			current_entries = bucket->counter;
			for( int j = 0; j < current_entries; j++){
				if(!strcmp(bucket->entries[j].key,diseaseID)){
					
					return count_interval(bucket->entries[j].root,date1,date2);
				}
			}
			bucket = bucket->next;
		}
	}

}
int countryStats(HashEntry* table,char* diseaseID,char* country,struct tm date1,struct tm date2){
	Bucket* bucket = NULL;
	int current_entries = 0;
	int buckets = table->buckets;
	for(int i = 0; i < buckets; i++){
		bucket =  table[i].head;
		if(bucket == NULL)
			continue;
		while(bucket != NULL){
			current_entries = bucket->counter;
			for( int j = 0; j < current_entries; j++){
				if(!strcmp(bucket->entries[j].key,country)){
					treeNode* root = bucket->entries[j].root;
					return tree_attribute(root,diseaseID,country,date1,date2);
				}
			}
			bucket = bucket->next;
		}
	}



}
void diseaseFrequency(HashEntry* table,char* diseaseID,char* country,char* entryDate,char* exitDate){
	struct tm date1,date2;
	memset(&date1, 0, sizeof(struct tm));
	memset(&date2, 0, sizeof(struct tm));
	if(exitDate == NULL){
		strptime(country,"%d-%m-%Y",&date1);  // now country is the entryDate
   		strptime(entryDate,"%d-%m-%Y",&date2);
   	}
   	else{
   		strptime(entryDate,"%d-%m-%Y",&date1);
   		strptime(exitDate,"%d-%m-%Y",&date2);
   	}
   	if(country == NULL){
   		printf("%s :%d\n",diseaseID,virusStats(table,diseaseID,date1,date2));
   		return;
   	}
   	else{
   		printf("%s %s: %d\n",country,diseaseID,countryStats(table,diseaseID,country,date1,date2));
   		return;
   	}
}

void insert_exitDate(list* list,int id,struct tm exitDate){
	list_node* temp =  list->head;

	while(temp != NULL){
		if( temp->patient->id == id){
			memcpy(&temp->patient->exitDate,&exitDate,sizeof(struct tm));
			printf("Exit date on %d inserted\n",id);
			return;
		}
		temp = temp->next;
	}
	printf("Patient with id %d not found\n",id);
	return;

}

void numCurrentPatients(HashEntry* table,char* diseaseID){
	int hash_value = 0;
	int current_entries = 0;
	treeNode* root = NULL;
	Bucket* bucket = NULL;
	if(diseaseID){
		hash_value = hash(diseaseID,table->buckets);
		bucket = table[hash_value].head;
		current_entries = bucket->counter;
		for( int i = 0; i < current_entries; i++){
			root = bucket->entries[i].root;
			if(diseaseID){
				if(!strcmp(bucket->entries[i].key,diseaseID)){
					printf("%s: %d\n",diseaseID,tree_no_exit(root));
					return;
				}
			}
		}
	}
	else{
		for( int i = 0; i < table->buckets; i++){
			bucket = table[i].head;
			if(bucket == NULL)
				continue;
			while(bucket != NULL){
				current_entries = bucket->counter;
				for(int j = 0; j < current_entries; j++){
					root = bucket->entries[j].root;
					printf("%s: %d\n",bucket->entries[j].key,tree_no_exit(root));
				}
				bucket = bucket->next;
			}
		}
	}
	return;
}