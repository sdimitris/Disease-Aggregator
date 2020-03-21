#include<stdio.h>
#include<stdlib.h>
#include"structures.h"
#include"functions.h"
#include<string.h>
treeNode* create_treeNode(struct tm date){
		treeNode* new_node = malloc(sizeof(struct treeNode));

		new_node->left = NULL;
		new_node->right = NULL;
		new_node->date = date; 
		new_node->height = 1;


		return new_node;
}

treeNode* right_rotate(treeNode* node){

    treeNode *left = node->left;  
    treeNode *temp = left->right;  
  
    // Perform rotation  
    left->right = node;  
    node->left = temp;  
  
 
    node->height = max(get_height(node->left),get_height(node->right)) + 1;  
    left->height = max(get_height(left->left),get_height(left->right)) + 1;  
  
    // Return new root  
    return left;  
			
}
int balance(treeNode* node){
	if(node == NULL)
		return 0;
	return get_height(node->left) - get_height(node->right);
}
treeNode* left_rotate(treeNode* node){

    treeNode *right = node->right;  
    treeNode *temp = right->left;  
  
    right->left = node;  
    node->right = temp;  
  
    node->height = max(get_height(node->left),get_height(node->right)) + 1;  
    right->height = max(get_height(right->left),get_height(right->right)) + 1;  
  

    return right;

}
int max(int a, int b){
	return (a > b) ? a : b;
}
int get_height(treeNode* node){

	if(node == NULL)
		return 0;
	else
		return node->height;

}
treeNode* insert_date(treeNode* node,Patient* patient,list_node* tail){
	if(node == NULL){

		treeNode* new_node = create_treeNode(patient->entryDate);
		new_node->record = tail;
		return new_node;
	}
	if(difftime(mktime(&patient->entryDate),mktime(&node->date)) < 0 )
		node->left= insert_date(node->left,patient,tail);
	if(difftime(mktime(&patient->entryDate),mktime(&node->date)) >= 0 )
		node->right = insert_date(node->right,patient,tail);
	else{
		return node;
	}
	
	
	node->height = 1 + max(get_height(node->left),get_height(node->right));
	int balance_factor = balance(node);

	if(balance_factor > 1 && difftime(mktime(&patient->entryDate),mktime(&node->left->date)) < 0)
		return right_rotate(node);
	if(balance_factor < -1 &&  difftime(mktime(&patient->entryDate),mktime(&node->right->date)) > 0)
		return left_rotate(node);
	if(balance_factor > 1 && difftime(mktime(&patient->entryDate),mktime(&node->left->date)) < 0){
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	if(balance_factor < -1 && difftime(mktime(&patient->entryDate),mktime(&node->right->date)) < 0){
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	return node;


}
int tree_attribute(treeNode* root, char* uknown,struct tm date1,struct tm date2,int option){
	int count = 0;
	list_node* temp;

	if(root){ 
		if(difftime(mktime(&(date1)),mktime(&(root->date))) <= 0 && difftime(mktime(&(date2)), mktime(&(root->date))) >= 0){
			if( option == 1 && !strcmp(root->record->patient->diseaseID,uknown))
				count++;
			else if( option == 2 && !strcmp(root->record->patient->country,uknown)){
				count++;
			}
			
		}
		count += tree_attribute(root->left,uknown,date1,date2,option);
		count += tree_attribute(root->right,uknown,date1,date2,option);
	}
	return count;
}

int tree_no_exit(treeNode* root){
	int count = 0;
	if(root){
		//printf("DiseaseID %")
		if(!is_date(root->record->patient->exitDate)){
			count++;
		
		}
		count += tree_no_exit(root->left);
		count += tree_no_exit(root->right);
	}

	return count;
	
}

int count_interval(treeNode* node,struct tm date1,struct tm date2){  //[date1,date2]

	int count = 0;
	if(node){ 

		if(difftime(mktime(&(date1)),mktime(&(node->date))) <= 0 && difftime(mktime(&(date2)), mktime(&(node->date))) >= 0)
			count++;
		count += count_interval(node->left,date1,date2);
		count += count_interval(node->right,date1,date2);

	}
	return count;
}

int count_tree_nodes(treeNode* node){
	int count = 0;
	if(node){
		count++;
	
		count += count_tree_nodes(node->left);
		count += count_tree_nodes(node->right);
	}
	return count;
}

void print_tree(treeNode* node){
	if(node == NULL)
		return;
	print_tree(node->right);
	print_tree(node->left);
	print_patient(node->record->patient);
}
	
void free_tree(treeNode* root){

	if(root == NULL)
		return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);

}
int count_attribute(treeNode* root, char* uknown,int option){  // option 1 for diseases 
	int count = 0;
	if(root){

		if(option == 1 && !strcmp(uknown,root->record->patient->diseaseID))
			count++;
		else if( option == 2 && !strcmp(uknown,root->record->patient->country))
			count++;
		
		count += count_attribute(root->left,uknown,option);
		count += count_attribute(root->right,uknown,option);

	}
	return count;
}








