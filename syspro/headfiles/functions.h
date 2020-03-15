#ifndef __FUNCTIONS__
#define	__FUNCTIONS__
#define DXOPEN_SOURCE 700
#include<time.h>
#include"hash_table.h"
int check_duplicates(FILE* fp);
struct tm string_to_date(char* date);
int hash(char* string,int Buckets);
void print_table(HashEntry* table,int buckets);
void print_hash_cell(HashEntry* table,int hash);
#endif