#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paginacao.h"
// #include <glib.h>


struct table{
    char **paginas;        // Array de páginas
    int *numPag;          // Número da página atual
    int *numPagTotal;     // Número de páginas totais
};


// numPag++ :: Avançar na página
// numPag-- :: Recuar na página


int getNumPag(TABLE table){
    return *table->numPag;
}
void setNumPag(TABLE table, int newNumPag){
    table->numPag = newNumPag;
}

char** getPaginas(TABLE table){
    char **paginas = NULL;
    int i = 0;
    for(i = 0; table->paginas[i] != NULL; i++){
        paginas = realloc(paginas, sizeof(char*)*(i+1));
        paginas[i] = strdup(table->paginas[i]);
    }
    paginas[i] = NULL;
    return paginas;
}
void setPaginas(TABLE table, char **newPaginas){
    table->paginas = newPaginas;
}

void nextPage(TABLE table, int numPagAtual){
    setNumPag(table, numPagAtual++);
}

void previousPage(TABLE table, int numPagAtual){
    setNumPag(table, numPagAtual--);    
}

void acao(TABLE table, char tecla){
    
    int numPagATual = getNumPag(table);
    
    switch(tecla){

        case (tecla == 'k'): // Avança na página
            nextPage(table, numPagAtual);
            break;
        
        case (tecla == 'j'): // Recua na página 
            previousPage(table, numPagAtual);
            break;

        default:
            printf("comanddo inesxixtente \n");
        
    }
}


