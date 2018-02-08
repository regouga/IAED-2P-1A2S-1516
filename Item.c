#include "Item.h"

Item newItem(char*text)
/* Cria um novo Item */
{
    Item x = (Item)malloc(sizeof(struct hashtag));
    x->text = strdup(text);
    x->count = 1;
	return x; 
}

void deleteItem(Item a)
/* Apaga o Item a */
{
    free(a->text);
    free(a); 
}

void visitItem(Item a)
/* Imprime o Item a */
{
    printf("%s %d\n",a->text, a->count);
}
