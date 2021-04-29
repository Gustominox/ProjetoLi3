#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paginacao.h"
// #include <glib.h>


struct table{
    char ***variaveis;        
    int numLin;               
    int numLinTotal;         
};


void setNumLin(TABLE table, int newNumLin){
    table->numLin = newNumLin;
}
int getNumLin(TABLE table){
    return table->numLin;
}

int getNumLinTotal(TABLE table){
    return table->numLinTotal;
}
void setNumLinTotal(TABLE table, int newNumLinTotal){
    table->numLinTotal = newNumLinTotal;
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


void printLinha (char **variaveis){

    for(int i = 0; variaveis[i] != NULL; i++){
        printf("| %s", variaveis[i]);
    }
    printf("\n");
}

void acao(TABLE table){
    
    int numLinAtual = getNumLin(table);

    printf("Que página pretende ver a seguir?\n");

    while(1){
        char tecla = getchar();

        if (tecla == 'k' || tecla == 'K'){ // Avança na página
            setNumLin(table, numLinAtual++);
            break;
        }
        else if (tecla == 'j' || tecla == 'J'){ // Recua na página 
            setNumLin(table, numLinAtual-20);
            break;
        }
        else if (tecla == 'q'){
            exit(0);
        }
        else
            if(tecla != 0x0A) printf("comando inexistente \n");
    }
}

