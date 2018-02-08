#include "ST.h"

link NEW(Item item, link l, link r)   /* cria um novo no */
{
    link x = (link)malloc(sizeof(struct STnode));
    x->item = item;
    x->l = l;
    x->r = r;
    x->height=1;
    return x; 
}



void STinit(link*head)   /* Inicializa a arvore vazia */
{
	*head = NULL;
}



int height(link h){
    if (h == NULL) return 0;
    return h->height;
}

link rotL(link h)
{
    int height_left, height_right;
    link x = h->r;
    h->r = x->l;
    x->l = h;
    height_left = height(h->l); height_right = height(h->r);
    h->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    height_left = height(x->l); height_right = height(x->r);
    x->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    return x;
   }

  
link rotR(link h)
{
    int height_left, height_right;
    link x = h->l;
    h->l = x->r;
    x->r = h;
    height_left = height(h->l); height_right = height(h->r);
    h->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    height_left = height(x->l); height_right = height(x->r);
    x->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    return x; 
}


link rotLR(link h) /*rotação dupla esquerda direita*/
{
    if (h==NULL) return h;
    h->l=rotL(h->l);
    return rotR(h);
}


link rotRL(link h) /*rotação dupla direita esquerda*/
{
    if (h==NULL) return h;
    h->r=rotR(h->r);
    return rotL(h);
}

int Balance(link h)   /*Balance factor*/
{
    if(h == NULL) return 0;
    return height(h->l)-height(h->r);
}

link AVLbalance(link h)    /* balanceia a arvore binaria */
{
    int balanceFactor;
    if (h==NULL) return h;
    balanceFactor= Balance(h);
    if(balanceFactor>1) {
        if (Balance(h->l)>=0) h=rotR(h);
        else h=rotLR(h);
    }
    else if(balanceFactor<-1){
        
        if (Balance(h->r)<=0) 
            h = rotL(h);
        else 
            h = rotRL(h);
    }
    else {
        int height_left = height(h->l); 
        int height_right = height(h->r);
        h->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    }
    return h; 
}

link insertR(link h, Item item)   /* Insere um novo no na arvore */
{
    if (h == NULL)
        return NEW(item, NULL, NULL);
        
    if (less(key(item), key(h->item)))
        h->l = insertR(h->l, item);
    
    else
        h->r = insertR(h->r, item);
        
    h = AVLbalance(h);
    return h;
}


void STinsert(link*head, Item item)
{
    *head = insertR(*head, item);
}


Item searchR(link h, Key v) 
{
    if (h == NULL)
        return NULL;
    if (eq(v, key(h->item)))
        return h->item;
    if (less(v, key(h->item)))
        return searchR(h->l, v);
    else
        return searchR(h->r, v);
}

Item STsearch(link head, Key v)   /* Procura por um Item na arvore */
{
    return searchR(head, v);
} 


link max(link h) {
  if (h==NULL || h->r==NULL) 
    return h;
  else 
    return max(h->r);
}


link min(link h) { 
  if (h==NULL || h->l==NULL) 
    return h;
  else 
    return min(h->l);
}


link deleteR(link h, Key k) /* apaga o elemento k da arvore h */
{
    if (h==NULL) return h;
    else if (less(k, key(h->item))) h->l=deleteR(h->l,k);
    else if (less(key(h->item), k)) h->r=deleteR(h->r,k) ;
    else {
    	if (h->l !=NULL && h->r !=NULL){
    	link aux = max(h->l);
    	{Item x; x=h->item; h->item=aux->item; aux->item=x; }
    	h->l= deleteR(h->l, key(aux->item));
    	}
    	else {
    	link aux=h;
    	if ( h->l == NULL && h->r == NULL ) h=NULL;
    	else if (h->l==NULL) h=h->r;
    	else h=h->l;
    	deleteItem(aux->item);
    	free(aux);
    	} 
    }
    h=AVLbalance(h);
	return h;
}

int count(link h){
    if (h==NULL) return 0;
    else return count(h->r)+count(h->l)+1;
}


int STcount(link head){
    return count(head);
}


void STdelete(link*head, Key k){
    *head = deleteR(*head, k);
}


void sortR(link h, void (*visit)(Item)) /* apaga o elemento k da arvore h */
{
    if (h == NULL) return;
    sortR(h->l, visit);
    visit(h->item);
    sortR(h->r, visit);
}


void STsort(link head, void (*visit)(Item)) /* Imprime a Arvore Head */
{
    sortR(head, visit);
}

link freeR(link h)
{
    if (h==NULL)
        return h;
    h->l=freeR(h->l);
    h->r=freeR(h->r);
    return deleteR(h,key(h->item));
}


void STfree(link*head) /* Liberta o espaco de memoria ocupado pela arvore head */
{
    *head=freeR(*head);
}

void copy_tree(link h, Item *vec, int *i) /* copia os elementos da de H para o vetor vec */
{
  if (h == NULL) 
    return;
  
  copy_tree(h->l, vec, i);
  
  vec[*i] = h->item;
  ++(*i);
  
  copy_tree(h->r, vec, i);
}