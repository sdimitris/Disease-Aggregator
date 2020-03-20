#ifndef __FUNCTIONS__
#define	__FUNCTIONS__
#define DXOPEN_SOURCE 700
#include<time.h>
#include"structures.h"

void duplicate_id(list* list,int id);
struct tm string_to_date(char* date);
int hash(char* string,int Buckets);
HashEntry* hash_table_init(int Buckets);
Bucket* create_bucket(char* key,int BucketSize);
HashEntry* insert_bucket(HashEntry* Hash_Table,int option,list_node* tail,int BucketSize,int Buckets);
int key_duplicate(HashEntry* Table,Bucket** bucket_pos,char* key, int hash);

int differentRecs(HashEntry* table);

void diseaseFrequency(HashEntry*,char* ,char*,char*,char* );

list* insert_list(list* list,struct Patient* patient);
void print_list(list* list);
list* list_init(list* list);
treeNode* free_patient_list(list_node* head);

int new_height(treeNode* Node);
int get_height(treeNode* node);
treeNode* create_treeNode(struct tm date);
treeNode* insert_date(treeNode* Node,Patient* patient,list_node* node);
void print_tree(treeNode* Node);
treeNode* right_rotate(treeNode* node);
treeNode* left_rotate(treeNode* node);
void print_tree_node(treeNode* node);
void insert_exitDate(list* list,int id,struct tm exitDate);
int count_tree_nodes(treeNode* node);
void print_tree(treeNode* node);
void globalDiseaseStats(HashEntry*,char*,char*);
void printDiseaseStats(treeNode* ,char* ,char* );
int count_interval(treeNode* node,struct tm date1,struct tm date2);
void print_patient(Patient* patient);
int virusStats(HashEntry* table,char* diseaseID,struct tm date1,struct tm date2);
int countryStats(HashEntry* table,char* diseaseID,char* country,struct tm date1,struct tm date2);
int tree_attribute(treeNode* root, char* diseaseID,char* country,struct tm date1,struct tm date2);
int tree_no_exit(treeNode* root);
void numCurrentPatients(HashEntry* table,char* diseaseID);
int is_date(struct tm date);

int max(int a, int b);
int balance(treeNode* node);
void free_patient(Patient*);
void free_list(list*);
void free_hash_table(HashEntry*);
void free_tree(treeNode* root);
int count_attribute(treeNode* root, char* uknown);

int subtree_height(heap_node* root);
char** array(HashEntry*);
heap_node* fill_heap(char**,HashEntry*,char*,int k);
int exists(char** table,char* key,int size);
heap_node* insert_heap(heap_node* root,char* name,int counter);

void print_heap(heap_node* root,int k);
void swap( int* a, int * b);
void swap_string(char** str1,char** str2);

void print_level(heap_node* root,int* k,int level);
void print_topk(heap_node* root,int* k);

#endif