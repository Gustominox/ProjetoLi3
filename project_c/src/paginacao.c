#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paginacao.h"
// #include <glib.h>

void setNumLin(TABLE table, int newNumLin){
    table->numLin = newNumLin;
}
int getNumLin(TABLE table){
    return table->numLin;
}
/*
char** getVariaveis(TABLE table){
    char ***variaveis = NULL;
    int i = 0;
    for(i = 0; table->variaveis[i] != NULL; i++){
        variaveis = realloc(variaveis, sizeof(char*)*(i+1));
        variaveis[i] = strdup(table->variaveis[i]);
    }
    variaveis = realloc(variaveis, sizeof(char*)*(i+1));
    variaveis[i] = NULL;
    return variaveis;
}*/


void setVariaveis(TABLE table, char ***newVariaveis){
    table->variaveis = newVariaveis;
}


int getNumLinTotal(TABLE table){
    return table->numLinTotal;
}


void setNumLinTotal(TABLE table, int newNumLinTotal){
    table->numLinTotal = newNumLinTotal;
}


void nextLine(TABLE table, int numLinAtual){
    setNumLin(table, numLinAtual++);
}


void previousLine(TABLE table, int numLinAtual){
    setNumLin(table, numLinAtual--);    
}


void printLinha (char **variaveis){

    for(int i = 0; variaveis[i] != NULL; i++){
        printf("| %s", variaveis[i]);
    } 

    //printf("|\n");
}


void acao(TABLE table, char tecla){
    
    int numLinAtual = getNumLin(table);
    
    switch(tecla){

        case ('k'): // Avança na página
            nextLine(table, numLinAtual);
            break;
        
        case ('j'): // Recua na página 
            previousLine(table, numLinAtual);
            break;

        default:
            printf("comando inesxixtente \n");
        
    }
}

