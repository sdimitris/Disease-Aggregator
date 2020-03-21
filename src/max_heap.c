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
	int i = 0;
	int j = 0;
	heap_node* heap = NULL;

	size = differentRecs(table);
	char** array = malloc(sizeof(char*)*size);
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

int min(int a,int b){

	return( a < b) ? a : b;


}
heap_node* fill_heap(char** differentRecs,HashEntry* table,char* name,int size,char* date11,char* date22,int option){

	int hash_value = hash(name,table->buckets);
	Bucket* bucket = table[hash_value].head;
	int current_entries;
	int count = 0;
	treeNode* root = NULL;
	int flag = 0;
	int i,j;
	struct tm date1,date2;

	memset(&date1, 0, sizeof(struct tm));
	memset(&date2, 0, sizeof(struct tm));

	if(date11 && date22){
		strptime(date11,"%d-%m-%Y",&date1);
    	strptime(date22,"%d-%m-%Y",&date2);
	}


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
					if(date11 && date22)
						count = tree_attribute(root,differentRecs[j],date1,date2,option);
					else
						count = count_attribute(root,differentRecs[j],option);
					

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
	return min(lheight,rheight) + 1;

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
	int height1 = 0;
	int height2 = 0;
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
	height1 = subtree_height(root->left);
	height2 = subtree_height(root->right);
	if(height1 <= height2){
		heap_node* lchild  = insert_heap(root->left,name,counter);
		root->left = lchild;

		lchild->parent = root;
		if(lchild->parent != NULL){
			if(lchild->counter > root->counter){
				swap(&lchild->counter,&root->counter);
				swap_string(&lchild->name,&root->name);
			
			}
		}
	}
	if(height1 > height2){
		heap_node* rchild = insert_heap(root->right,name,counter);
		root->right = rchild;
		rchild->parent = root;

		if(rchild->parent != NULL){
			if(rchild->counter > root->counter ){
				swap(&rchild->counter,&root->counter);
				swap_string(&rchild->name,&root->name);
				
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
        printf("%s %d\n",root->name,root->counter); 
    }  
    else if (level > 1){  
       print_level(root->left,k,level-1);  
       print_level(root->right,k,level-1);  
    }  
}

void find_last(heap_node* root,int level,int* last_level,heap_node** res){

	if(root ==  NULL)
		return;
	if(!root->left && !root->right && level > *last_level){
		*res = root;
		*last_level = level;
		return;
	}

	find_last(root->right,level+1,last_level,res);
	find_last(root->left,level+1,last_level,res);
}



heap_node* pop_root(heap_node* root, heap_node** last,int size,heap_node** max){
	if(root == NULL)
		return NULL;
	if(!root->right && !root->left){
		(*max)->counter = root->counter;
		strcpy((*max)->name,root->name);
		return root;
	}
	swap(&root->counter,&(*last)->counter);
	swap_string(&root->name,&(*last)->name);
	
	(*max)->counter = (*last)->counter;
	strcpy((*max)->name,(*last)->name);

	if((*last)->parent){
		if((*last)->parent->right  == *last )
			(*last)->parent->right = NULL;
		else
			(*last)->parent->left = NULL; 	
	}
	
	free((*last)->name);
	free(*last);
	heap_node* temp = root;

	
	for( int i = 0; i < size && temp ; i++){
		if( temp->left && temp->right){  // an exei duo paidia vres to megalutero
			if(temp->left->counter >= temp->right->counter){ 
				if(temp->left->counter > temp->counter){
					swap(&temp->counter,&temp->left->counter);
					swap_string(&temp->name,&(temp->left->name));
					temp = temp->left;
				}
			}
			else if( temp->right->counter > temp->left->counter){
				if( temp->right->counter > temp->counter){
					swap(&temp->counter,&temp->right->counter);
					swap_string(&temp->name,&(temp->right->name));
					temp = temp->right;	
				}
			}
		}
		else if( !temp->left && temp->right){                // an exei 1 paidi deksi tote tsekare
			if(temp->right->counter > temp->counter){
				swap(&temp->counter,&temp->right->counter);
				swap_string(&temp->name,&temp->right->name);
				temp = temp->right;
			}
		}
		else if(temp->left && !temp->right){
			if(temp->left->counter > temp->counter){
				swap(&temp->counter,&temp->left->counter);
				swap_string(&temp->name,&(temp->left->name));
				temp = temp->left;
			}
		}
	}

	return root;
}

void free_heap(heap_node* root){
	if(root == NULL)
		return;

	free_heap(root->left);
	free_heap(root->right);
	free(root->name);
	free(root);



}











































	
