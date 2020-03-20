#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void swap( int* root, int* parent){

	int temp = *root;
	*root = *parent;
	*parent = temp;

}

void swap_string(char** str1,char** str2){

 	char *temp = *str1; 
  	*str1 = *str2; 
  	*str2 = temp; 

}
int main(){


	int a = 5;
	int b = 6;
	swap(&a,&b);
	printf("a %d b %d",a,b);

	char* giorgos = "giorgos";
	char* maria = "maria";
	swap_string(&giorgos,&maria);
	printf("Girgos %s maria %s\n",giorgos,maria);




}