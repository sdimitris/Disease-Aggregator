#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"avl_tree.h"

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
		//new_head->list = NULL

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
treeNode* insert_date(treeNode* node,Patient* patient){
	if(node == NULL){
		
		return create_treeNode(patient->entryDate);
	}
	if(difftime(mktime(&(patient->entryDate)), mktime(&(node->date))) < 0){
		node->left = insert_date(node->left,patient);	
		
	}
	else if(difftime(mktime(&(patient->entryDate)), mktime(&(node->date))) > 0){
		node->right =  insert_date(node->right,patient);	
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

void print_tree(treeNode* node){
	if(node == NULL)
		return;
	print_tree(node->left);
	print_tree(node->right);
	printf("%d-%d-%d\n",node->date.tm_mday,node->date.tm_mon,node->date.tm_year);

}