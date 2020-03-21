#ifndef __STRUCTURES__
#define __STRUCTURES__
#include<time.h>
#define ENTRY_SIZE 20

typedef struct Patient{
	int id;
	char* firstname;
	char* lastname;
	char* diseaseID;
	char* country;
	struct tm entryDate;
	struct tm exitDate;
}Patient;

typedef struct list_node{
	struct Patient* patient;
	struct list_node* next;
}list_node;

typedef struct List{
	list_node* head;
	list_node* tail;
	int counter;
}list;


typedef struct treeNode{
	struct tm date;
	struct treeNode* left;
	struct treeNode* right;
	int height;
	list_node* record;


}treeNode;

typedef struct BucketEntry{

 	char* key;		//country/disease
 	treeNode* root;
}BucketEntry;

typedef struct Bucket{
	BucketEntry* entries;        // key/value  country,disease/ bucket_next
	struct Bucket* next;
	int counter; // counts how keys are in.
}Bucket;

typedef struct HashEntry{
	Bucket* head;
	int buckets;
}HashEntry;
typedef struct heap_node{
	char* name;
	int counter;
	struct heap_node* left;
	struct heap_node* right;
	struct heap_node* parent;

}heap_node;
#endif