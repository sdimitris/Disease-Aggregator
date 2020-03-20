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
int exists(char** table,char* key,int size){
	for(int i = 0; i < size; i++){
		if(!strcmp(table[i],key))
			return 1;

	}
	return 0;

}
char** array(HashEntry* table){
	int pivot = 0;
	Bucket* bucket = NULL;
	Bucket* target = NULL;
	char* temp_country = NULL;
	int pos = 0;
	int size = 0;
	int counter = 0;
	int i,j;
	char** array = NULL;
	heap_node* heap = NULL;

	size = differentRecs(table);
	array = malloc(sizeof(char*)*size);
	for (i = 0; i < size; i++)
		array[i] = malloc(ENTRY_SIZE*sizeof(char));

	for( i = 0; i < table->buckets; i++){
		bucket = table[i].head;
		if(bucket == NULL)
			continue;
		while(bucket != NULL){
			counter = bucket->counter;
			for( j = 0; j < counter; j++){
				if(!exists(array,bucket->entries[j].key,size)){
					strcpy(array[pos],bucket->entries[j].key);
					pos++;
				}
			}
		bucket  = bucket->next;

		}
	}
	return array;
}


heap_node* fill_heap(char** differentRecs,HashEntry* table,char* name,int size){

	int hash_value = hash(name,table->buckets);
	Bucket* bucket = table[hash_value].head;
	int current_entries;
	int count = 0;
	treeNode* root = NULL;
	int flag = 0;
	int i,j;

	heap_node* couples = malloc(size*sizeof(struct heap_node));  // pinakas apo komvous heap
	for(int i = 0; i < size; i ++)
		couples[i].name = malloc(ENTRY_SIZE*sizeof(char));

	
	while(bucket != NULL && !flag){
		current_entries = bucket->counter;
		for(i = 0; i < current_entries && !flag; i++)

			if(!strcmp(name,bucket->entries[i].key)){

				root = bucket->entries[i].root;
				for(j = 0; j < size; j++){
					strcpy(couples[j].name,differentRecs[j]);
					count = count_attribute(root,differentRecs[j]);
					couples[j].counter = count;
				}


				flag = 1;
				break;
			}
		bucket = bucket->next;
	}


	return couples;
}

int subtree_height(heap_node* root){
	if(root == NULL)
		return 0;
	int lheight = subtree_height(root->left);
	int rheight = subtree_height(root->right);
	return max(lheight,rheight) + 1;

}
void swap( int* root, int* parent){

	int temp = *root;
	*root = *parent;
	*parent = temp;

}

void swap_string(char** str1,char** str2){

 	char *temp = *str1; 
  	*str1 = *str2; 
  	*str2 = temp; 

}
heap_node* insert_heap(heap_node* root,char* name, int counter){
	int height1;
	int height2;
	if(root == NULL){
		heap_node* node = malloc(sizeof(heap_node));
		node->name = malloc(ENTRY_SIZE*sizeof(char));
		strcpy(node->name,name);
		node->counter = counter;
		node->right = NULL;
		node->left = NULL;
		node->parent = NULL;

		return node;
	}	
	else{
		height1 = subtree_height(root->left);
		height2 = subtree_height(root->right);
		if(height1 <= height2){

			root->left  = insert_heap(root->left,name,counter);	
			
			if(root->left->counter >= root->counter){
				swap(&root->left->counter,&root->counter);
				swap_string(&root->left->name,&root->name);
			}

			if( height1 == height2 && root->left && root->right ){
				if( root->left->counter < root->right->counter ){
					swap(&root->left->counter,&root->right->counter);
					swap_string(&root->left->name,&root->right->name);
				}

			}

		}
		else if(height1 > height2){
			root->right = insert_heap(root->right,name,counter);
			if(root->right->counter > root->counter ){

				swap(&root->right->counter,&root->counter);
				swap_string(&root->right->name,&root->name);	

			}
		}
	}
	

	

	return root;
}

void print_topk(heap_node* root,int* k){
  
    int height = subtree_height(root);  
    int i;  
    for (i = 1; i <= height; i++)  
        print_level(root,k,i);  
}  
void print_level(heap_node* root,int* k,int level){

if (root == NULL)  
        return;  
    if (level == 1){
  
        printf("ss%s %d\n",root->name,root->counter); 
    }  
    else if (level > 1){  
       print_level(root->left,k,level-1);  
       print_level(root->right,k,level-1);  
    }  
}







































	
