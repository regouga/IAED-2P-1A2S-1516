#ifndef _ST_
#define _ST_
#include <stdlib.h>
#include <stdio.h>
#include "Item.h"


typedef struct STnode* link;
struct STnode { 
	Item item; 
	link l, r;
	int height;
};


void STinit(link*);
int STcount(link);
Item STsearch(link,Key);
void STinsert(link*,Item);
void STdelete(link*,Key);
void STsort(link,void (*visit)(Item));
void STfree(link*);
void copy_tree(link h, Item *vec, int *i);

#endif