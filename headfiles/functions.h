#ifndef __FUNCTIONS__
#define	__FUNCTIONS__
#define DXOPEN_SOURCE 700
#include<time.h>
#include"structures.h"

void duplicate_id(list* list,int id);
struct tm string_to_date(char* date);
int hash(char* string,int Buckets);
void print_hash_cell(HashEntry* table,int hash);
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


heap* make_heap(int size);
heap* fill_heap(HashEntry*,heap* heap,char* country);
#endif