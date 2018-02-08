/* ============================================================================================== */
/* ================================= Instituto Superior Tecnico ================================= */
/* ================================= PROJETO 2 - IAED 2015/2016 ================================= */
/* ======================= Mariana Mendes, 83521 | Miguel Regouga, 83530 ======================== */
/* ======================================== GRUPO AL009 ========================================= */
/* ============================================================================================== */


/* ============================================================================================== */
/* ========================================= BILBIOTECAS ======================================== */
/* ============================================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#include "Item.h"
#include "ST.h"



/* ============================================================================================== */
/* ========================================= PROTOTIPOS ========================================= */
/* ============================================================================================== */

void most_popular(Item x);                    /* avalia se o Item x ocorre mais vezes que o maior */
int compare (const void *a, const void *b);                  /* funcao de comparacao para o qsort */



/* ============================================================================================== */
/* ========================================= CONSTANTES ========================================= */
/* ============================================================================================== */

#define MAX 140



/* ============================================================================================== */
/* ===================================== VARIAVEIS GLOBAIS ====================================== */
/* ============================================================================================== */

int n_total = 0;                                          /* contador do numero total de hashtags */
int n_diferente = 0;                           /* contador do numero total de hashtags diferentes */
Item maior;                                             /* Hashtag com maior numero de repetiçoes */



/* ============================================================================================== */
/* ============================================== MAIN ========================================== */
/* ============================================================================================== */

int main () {

    int c, i, j;
    Item *vetor;
    char message[MAX + 1];
    char *p;
    link hashtags;
    STinit(&hashtags);
    maior = NULL;
    
    while ((c = getchar())) {
        
        switch (c) {
         
            case 'a':
            
            /* o comando a recebe uma mensagem e processa-a adicionando uma nova hashtag 
            ou incrementando o contador dependendo se a hashtag já existe ou nao*/
            
                fgets(message, MAX + 1, stdin);
                Item novo;
                for (i = 0; i < strlen(message); i++) message[i] = tolower(message[i]);
                p = &message[0];
                static const char separators[] = {' ','\t',',',';','.','?','!','"','\n',':','\0'};
                char *token = strtok(p, separators);
                while(token != NULL) {
                    
                    if ( *token == '#'){

                        Item x = (STsearch(hashtags, token));
                        if( x == NULL){ /* caso a hashtag nao exista no sistema */
                            n_diferente++;
                            novo = newItem(token);
                            STinsert(&hashtags, novo); /* inserecao na arvore */

                            if(n_total == 0)
                                maior = novo;
                            else if(maior->count == 1)
                                /* o maior e o alfabeticamente primeiro */
                                maior = ((strcmp(key(novo), key(maior))) < 0) ? novo : maior;
                
                        }
                        
                        else { /* caso a hashtag ja exista no sistema */
                            (x->count)++; /* incremento do contador respetivo a hashtag */
                            if (x->count > maior->count) 
                                maior = x;
                            else if (x->count == maior->count)
                                /* caso o atual 'maior' tenha o mesmo numero de hashtags que a
                                recentemente introduzidam, o novo 'maior' passa a ser cujo texto 
                                seja alfabeticamente primeiro */
                                maior = ((strcmp(key(x), key(maior))) < 0) ? x : maior;
                
                        }
                        
                        n_total++; /* incremento do numero total de hashtags */
                    }
   
                    token = strtok(NULL, separators);
                }
                    
                break;
         
            case 's':
            /* o comando s imprime o numero de hashtags distintas inseridas 
            ate entao e a soma do tota de ocorrencias de todas as hashtags */

                printf("%d %d\n", n_diferente, n_total);
                break;
           
            case 'm':
            /* o comando m imprime a hashtag com o maior numero de ocorrencias  */
            	
                if(n_total != 0) printf("%s %d\n", maior->text, maior->count);
                break;
           
            case 'l':
            /*  lista todas hashtags referidas nas mensagens por ordem decrescente segundo o 
            numero de ocorrencias N. Em caso de igualdade, devera seguir a ordem lexicografica */
                
                j=0;
                vetor = malloc(sizeof(struct hashtag)*n_diferente);
                copy_tree(hashtags, vetor, &j); /* copia da arvore para um vetor de pointers */
                qsort(vetor, (size_t) n_diferente, (size_t) sizeof(hashtags), compare);
                
                for(i=0; i < n_diferente; i++)
                    printf("%s %d\n", vetor[i]->text, vetor[i]->count);
                
                break;
           
            case 'x':
            /* O comando x termina o programa */
                STfree(&hashtags);
                exit(0);
        }
    }
    return 0;
}



/* ============================================================================================== */
/* ===================================== FUNCOES AUXILIARES ===================================== */
/* ============================================================================================== */

/* funcao utilizada no qsort para ordenar o vetor de ponteiros pela ordem desejada */
int compare (const void *a, const void *b) {
    Item ia = *(Item*) a;
    Item ib = *(Item*) b;
    int comp = ib->count - ia->count;
    if (comp != 0)
        return comp;
    return strcmp(ia->text, ib->text);
}