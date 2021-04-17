#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paginacao.h"
// #include <glib.h>


struct table{
    char **variaveis;         // Array de páginas
    int *numLin;           // Número da linha atual
    int *numLinTotal;     // Número de linhas totais
};

//printf("-----------------------------------------");

// char **variaveis;
// variaveis[0] = nomeBus;
// printf("|%s",variaveis[i]);

//printf("|\n");

//printf("-----------------------------------------");


// numPag++ :: Avançar na página
// numPag-- :: Recuar na página


int getNumPag(TABLE table){
    return *table->numPag;
}
void setNumPag(TABLE table, int newNumPag){
    table->numPag = newNumPag;
}

char** getVariaveis(TABLE table){
    char **variaveis = NULL;
    int i = 0;
    for(i = 0; table->variaveis[i] != NULL; i++){
        variaveis = realloc(variaveis, sizeof(char*)*(i+1));
        variaveis[i] = strdup(table->variaveis[i]);
    }
    variaveis = realloc(variaveis, sizeof(char*)*(i+1));
    variaveis[i] = NULL;
    return variaveis;
}
void setVariaveis(TABLE table, char **newVariaveis){
    table->variaveis = newVariaveis;
}

void nextPage(TABLE table, int numPagAtual){
    setNumPag(table, numPagAtual++);
}

void previousPage(TABLE table, int numPagAtual){
    setNumPag(table, numPagAtual--);    
}

void printLinha (char **variaveis){

    for(int i = 0; variaveis != NULL; i++){
        printf("| %s ", variaveis[i]);
    } 

    printf("|\n");
}

void acao(TABLE table, char tecla){
    
    int numPagAtual = getNumPag(table);
    
    switch(tecla){

        case ('k'): // Avança na página
            nextPage(table, numPagAtual);
            break;
        
        case ('j'): // Recua na página 
            previousPage(table, numPagAtual);
            break;

        default:
            printf("comando inesxixtente \n");
        
    }
}


