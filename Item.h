#ifndef _ITEM_
#define _ITEM_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define key(a) (a != NULL ? a->text : "")
#define less(a,b) (strcmp(a,b)<0)
#define eq(a,b) (strcmp(a, b)==0)

typedef char* Key;

typedef struct hashtag {
	char* text; 
	int count; 
}* Item;

Item newItem(char*text);
void deleteItem(Item a);
void visitItem(Item a);

#endif