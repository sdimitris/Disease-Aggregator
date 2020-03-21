#include<stdio.h>
#include<stdlib.h>
#include"functions.h"
#include"structures.h"
#include<string.h>

list* insert_list(list* list,Patient* p){  // ths exw perasei hdh desmeumenh mnhmh gia patient
	list_node* new_node = malloc(sizeof(struct list_node));
	new_node->patient = p;
	new_node->next = NULL;
	new_node->record = NULL; // record member is used for trees only

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

	list_node* head = list->head;
	list_node* temp  = head;
	while(head != NULL){
		free_patient(head->patient);
		temp = head;
		head = head->next;
		free(temp);
	}
}

void free_patient(Patient* patient){
	
	free(patient->firstname);
	free(patient->lastname);
	free(patient->country);
	free(patient->diseaseID);
}

