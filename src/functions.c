 #include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"structures.h"
#include"functions.h"
#define A 54059 
#define B 76963 
#define C 86969 
#define FIRSTH 37
struct tm string_to_date(char* string){

struct tm time_struct;
strptime(string,"%d-%m-%Y",&time_struct);
//printf("Month is %d\n",time_struct.tm_mon);
return time_struct;

}
int is_date(struct tm date){
	if( date.tm_year== 0 && date.tm_mday== 0 && date.tm_mon == 0)
		return 0;
	else 
		return 1;
}
void duplicate_id(list* list,int id){
	list_node* temp = list->head;
	while(temp != NULL){
		if(temp->patient->id == id){
			printf("Duplicate id..\n");
			exit(0);
		}
		temp = temp->next;
	}
	return;
}
list* list_init(list* list){
	list->head = NULL;
	list->tail = NULL;
	return list;
}
int hash(char* string,int Buckets){
	unsigned h = FIRSTH;
   while (*string) {
     	h = (h * A) ^ (string[0] * B);
     	string++;
   	}


   return h%Buckets; // or return h % C;sh;
}

void print_patient(Patient* patient){
	printf("%s %s %s %s exitDate: %d-%d-%d\n",patient->firstname,patient->lastname,patient->diseaseID,patient->country,
		patient->exitDate.tm_mday,patient->exitDate.tm_mon,patient->exitDate.tm_year);
	return;

}

void free_array(char** array,int size){

	for (int i = 0; i < size; ++i)
        free(array[i]);

	free(array);
}


