#ifndef __DISEASE__
#define __DISEASE__
#include<time.h>
#include"avl_tree.h"
#define ENTRY_SIZE 20 


typedef struct BucketEntry{
 	char* key;
 	treeNode* root;
}BucketEntry;

typedef struct Bucket{
	BucketEntry* entries;
	struct Bucket* next;
	int counter; // counts how keys are in.
}Bucket;

typedef struct HashEntry{
	Bucket* head;
}HashEntry;

typedef struct Patient{
	int id;
	char* firstname;
	char* lastname;
	char* diseaseID;
	char* country;
	struct tm entryDate;
	struct tm exitDate;
}Patient;

HashEntry* hash_table_init(int Buckets);
HashEntry* create_bucket(HashEntry* Hash_Table ,char* key , struct Bucket* bucket , int hash,int BucketSize);
HashEntry* insert_bucket(HashEntry* Hash_Table,int option,Patient* patient,int BucketSize,int Buckets);
int key_duplicate(HashEntry* Table, char* key, int hash);

#endif