#include<stdio.h>
#include<stdlib.h>
#include"structures.h"
#include"functions.h"
#include<string.h>



int height(treeNode* Node){
	if(Node == NULL)
		return 0;
	else
		return Node->height;
}
treeNode* create_treeNode(struct tm date){
		treeNode* new_node = malloc(sizeof(struct treeNode));

		new_node->left = NULL;
		new_node->right = NULL;
		new_node->date = date; 
		new_node->height = 1;

		new_node->duplicates = malloc(sizeof(struct List));
		new_node->duplicates->head = NULL;
		new_node->duplicates->tail = NULL;

		


		return new_node;
}

int new_height(treeNode* node){
	int right_height = height(node->right);
	int left_height = height(node->left);
	if(right_height > left_height)
		return right_height;
	else 
		return left_height;
	

}

treeNode* right_rotate(treeNode* node){

		treeNode* left = node->left;												// if the key < parent  key goes to the left
		treeNode* temp = left->right;													//left left rotate
		node->left = temp; // node->left->right to right subtree
		left->right = node;	// new subtree root is the left child of node.
		node->height = new_height(node) + 1; // take the max and add 1 
		left->height = new_height(left) + 1;
			
		return left;
}

treeNode* left_rotate(treeNode* node){

	treeNode* right = node->right;
	treeNode* temp = right->left;

	node->right = temp;
	right->left = node;

	node->height = new_height(node) + 1;
	right->height = new_height(right) + 1; // right child of node goes at root so height +1


	return right; // now right is the root

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
		new_node->record =  tail;
		new_node->duplicates->counter = 0;
		return new_node;

	}
	if(difftime(mktime(&(patient->entryDate)), mktime(&(node->date))) == 0){ //if the key is tha same
		list_node* duplicate = malloc(sizeof(struct list_node));

		duplicate->next = NULL;
		duplicate->record = tail; //now new_node points to the tail of the  outer list

		list_node* temp;

		if(node->duplicates->head == NULL){
			node->duplicates->head = duplicate;
			
		}
		else{
			temp = node->duplicates->tail;
			temp->next = duplicate; // now tail points to the new node
		}

		node->duplicates->tail = duplicate; //new tail is the duplicate
		node->duplicates->counter++;
		return node;
	}
	if(difftime(mktime(&(patient->entryDate)), mktime(&(node->date))) < 0){
		node->left = insert_date(node->left,patient,tail);	
		
	}
	else if(difftime(mktime(&(patient->entryDate)), mktime(&(node->date))) > 0){
		node->right =  insert_date(node->right,patient,tail);	
	}
		
	node->height = 1 + new_height(node);  // root height by one

	int balance_factor =  get_height(node->left) - get_height(node->right);
	if(balance_factor > 1){ 
		if(difftime(mktime(&(patient->entryDate)), mktime(&(node->date))) < 0){   // balance > 1 means the  node is left unbalanced
			return right_rotate(node);
		}
		if( difftime(mktime(&(patient->entryDate)), mktime(&(node->date)))){  //left right

			node->left  = left_rotate(node->left);
			return right_rotate(node);
		
		}
	}
	else if( balance_factor < -1 ){
	
		if(difftime(mktime(&(patient->entryDate)), mktime(&(node->date))) > 0){
			return left_rotate(node); 					//right right case
		}
		if(difftime(mktime(&(patient->entryDate)), mktime(&(node->date))) < 0 ){ // right left;
			node->right = right_rotate(node->right);
			return left_rotate(node);
		}
	}


		return node;

}
void print_tree_node(treeNode* node){

	print_patient(node->record->patient);
	if(node->duplicates->head != NULL){
		list_node* temp = node->duplicates->head;
		while(temp != NULL){
			print_patient(temp->record->patient);
			temp = temp->next;
		}
	}

}
int tree_attribute(treeNode* root, char* diseaseID,char* country,struct tm date1,struct tm date2){
	int count = 0;
	list_node* temp;

	if(root){ 
		if(difftime(mktime(&(date1)),mktime(&(root->date))) <= 0 && difftime(mktime(&(date2)), mktime(&(root->date))) >= 0){

			if(!strcmp(root->record->patient->diseaseID,diseaseID))
				count++;
			if(root->duplicates->head){
				temp = root->duplicates->head;
				while(temp != NULL){
					if(!strcmp(temp->record->patient->diseaseID,diseaseID))
						count++;
				}
				temp = temp->next;
			}
		}
		count += tree_attribute(root->left,diseaseID,country,date1,date2);
		count += tree_attribute(root->right,diseaseID,country,date1,date2);
	}
	return count;
}

int tree_no_exit(treeNode* root){
	int count = 0;
	if(root){
		//printf("DiseaseID %")
		if(!is_date(root->record->patient->exitDate)){
			//printf(" id %d first name %s %s\n",root->record->patient->id,root->record->patient->firstname,root->record->patient->lastname);
			count++;
			if(root->duplicates->head){
				list_node* temp = root->duplicates->head;	
				while(temp != NULL){
					if(!is_date(temp->record->patient->exitDate)){
						print_patient(temp->record->patient);
						count++;
					}
					temp = temp->next;
				}
			}
		}
		count += tree_no_exit(root->left);
		count += tree_no_exit(root->right);
	}

	return count;
	
}

int count_interval(treeNode* node,struct tm date1,struct tm date2){  //[date1,date2]

	int count = 0;
	if(node){ 

		if(difftime(mktime(&(date1)),mktime(&(node->date))) <= 0 && difftime(mktime(&(date2)), mktime(&(node->date))) >= 0){
			count++;
			if(node->duplicates->head)
				count += node->duplicates->counter;
		}
		count += count_interval(node->left,date1,date2);
		count += count_interval(node->right,date1,date2);

	}
	return count;
}

int count_tree_nodes(treeNode* node){
	int count = 0;
	if(node){
		count++;
		if(node->duplicates->head)
			count += node->duplicates->counter;

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
	
