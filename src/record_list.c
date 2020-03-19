#include<stdio.h>
#include<stdlib.h>
#include"functions.h"
#include"structures.h"

list* insert_list(list* list,Patient* p){  // ths exw perasei hdh desmeumenh mnhmh gia patient
	list_node* new_node = malloc(sizeof(struct list_node));
	new_node->patient = p;
	new_node->next = NULL;
	new_node->record = NULL; // record member is used for trees only
	list_node* temp;
	list->tail = new_node;
	//printf("id %d, first name: %s, disease: %s ,country %s: , year %d to %d\n",patient->id,patient->firstname,patient->diseaseID,patient->country,patient->entryDate.tm_year,patient->exitDate.tm_year);
	// isws kai sinartisi na ftiaksw
	if( list->head == NULL){
		list->head = new_node;
	}
	else{
		temp = list->head;
		while(temp->next != NULL){
			if(temp->patient->id == p->id){
				printf("Duplicate record with id %d, give another txt file..\n",p->id);
				exit(0);
			}
			temp = temp->next;
		}
		temp->next = new_node;
	}

	return list;
}

void print_list(list* list){

list_node* temp = list->head;
Patient* patient;
if(temp == NULL){
	printf("List is empty\n");
	return;
}
while(temp != NULL){
	patient = temp->patient;
	printf("%d %s %s %s %s  with entry Date ",patient->id,patient->firstname,patient->lastname,patient->diseaseID,patient->country);
	printf("%d-%d-%d exit Date %d-%d-%d\n",patient->entryDate.tm_mday,patient->entryDate.tm_mon,patient->entryDate.tm_year,
		patient->exitDate.tm_mday,patient->exitDate.tm_mon,patient->exitDate.tm_year);
	temp = temp->next;

}


}

