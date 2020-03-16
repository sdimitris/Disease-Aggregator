#ifndef __LIST__
#define __LIST__
#include"hash_table.h"
typedef struct list_node{

	Patient* patient;
	struct list_node* next;


}list_node;

list_node* insert_list(list_node* Node,Patient* patient);
void print_list(list_node* Node);

#endif