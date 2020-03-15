#ifndef __AVL_TREE__
#define __AVL_TREE__
#include<time.h>
#include"hash_table.h"
typedef struct treeNode{
	struct tm date;
	struct treeNode* left;
	struct treeNode* right;
	int height;
	list_node* record;

}treeNode;



int new_height(treeNode* Node);
int get_height(treeNode* node);
treeNode* create_treeNode(struct tm date);
treeNode* insert_date(treeNode* Node,Patient* patient);
void print_tree(treeNode* Node);
treeNode* right_rotate(treeNode* node);
treeNode* left_rotate(treeNode* node);


#endif