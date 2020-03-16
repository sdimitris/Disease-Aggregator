#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"list.h"
#include"hash_table.h"
list_node* insert_list(list_node* head,Patient* p){  // ths exw perasei hdh desmeumenh mnhmh gia patient
	list_node* new_node = malloc(sizeof(struct list_node));
	new_node->patient = p;
	new_node->next = NULL;

	list_node* temp;
	//printf("id %d, first name: %s, disease: %s ,country %s: , year %d to %d\n",patient->id,patient->firstname,patient->diseaseID,patient->country,patient->entryDate.tm_year,patient->exitDate.tm_year);
	// isws kai sinartisi na ftiaksw
	if( head == NULL){
		head = new_node;

	}
	else{
		temp = head;
		while(temp->next != NULL){
			if(temp->patient->id == p->id){
				printf("Duplicate record with id %d, give another txt file..\n",p->id);
				exit(0);
			}

			temp = temp->next;
		}
		temp->next = new_node;
	}
	
	if(temp->patient->id == p->id){
		printf("Duplicate record with id %d, give another txt file..\n",p->id);
		exit(0);
	}
	return head;
}

void print_list(list_node* head){

list_node* temp = head;
Patient* patient;
if(head == NULL){
	printf("List is empty\n");
	return;
}
while(temp != NULL){
	patient = temp->patient;
	printf("%d %s %s %s %s  with entry Date ",patient->id,patient->firstname,patient->lastname,patient->diseaseID,patient->country);
	printf("%d-%d-%d\n",patient->entryDate.tm_mday,patient->entryDate.tm_mon,patient->entryDate.tm_year);
	temp = temp->next;

}


}

