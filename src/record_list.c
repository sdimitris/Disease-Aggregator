#include<stdio.h>
#include<stdlib.h>
#include"functions.h"
#include"structures.h"
#include<string.h>

list* insert_list(list* list,Patient* p){  // ths exw perasei hdh desmeumenh mnhmh gia patient
	list_node* new_node = malloc(sizeof(struct list_node));
	new_node->patient = p;
	new_node->next = NULL;

	if(list->head == NULL){
		list->head = new_node;
		list->tail = new_node;

		return list;
	}
	list->tail->next = new_node;
	list->tail = new_node;
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
			temp = temp->next;

	}
}

void free_list(list* list){

	list_node* node = list->head;
	list_node* temp;
	while(node != NULL){
		temp = node;
		node = node->next;
		free_patient(temp->patient);
		free(temp->patient);
		free(temp);
	}
	list->head = NULL;
	list->tail = NULL;
}

void free_patient(Patient* patient){
	
	free(patient->firstname);
	free(patient->lastname);
	free(patient->country);
	free(patient->diseaseID);

}

