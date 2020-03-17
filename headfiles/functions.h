#ifndef __FUNCTIONS__
#define	__FUNCTIONS__
#define DXOPEN_SOURCE 700
#include<time.h>
#include"structures.h"

int check_duplicates(FILE* fp);
struct tm string_to_date(char* date);
int hash(char* string,int Buckets);
void print_table(HashEntry* table,int buckets);
void print_hash_cell(HashEntry* table,int hash);
HashEntry* hash_table_init(int Buckets);
HashEntry* create_bucket(HashEntry* Hash_Table ,char* key , struct Bucket* bucket , int hash,int BucketSize);
HashEntry* insert_bucket(HashEntry* Hash_Table,int option,list_node* tail,int BucketSize,int Buckets);
int key_duplicate(HashEntry* Table,Bucket** bucket_pos,char* key, int hash);



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



void globalDiseaseStats(HashEntry*,struct tm,struct tm);
void print_tree_interval(treeNode* node,struct tm date1,struct tm date2);
void print_patient(Patient* patient);

#endif