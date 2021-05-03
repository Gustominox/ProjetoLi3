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


int getNumLin(TABLE table){
    return table->numLin;
}


void setNumLin(TABLE table, int newNumLin){
    table->numLin = newNumLin;
}


int getNumLinTotal(TABLE table){
    return table->numLinTotal;
}


void setNumLinTotal(TABLE table, int newNumLinTotal){
    table->numLinTotal = newNumLinTotal;
}

char*** getVariaveis(TABLE table){

    char ***variaveis = malloc(sizeof(char**));
    variaveis = NULL;

    int i = 0, j = 0;
    
    while(j < getNumLinTotal(table)){
        
        variaveis = realloc(variaveis, sizeof(char**)*(j+1));
        variaveis[j] = NULL;

        for(i = 0; table->variaveis[j][i] != NULL; i++){
            variaveis[j] = realloc(variaveis[j], sizeof(char*)*(i+1));
            variaveis[j][i] = strdup(table->variaveis[j][i]);
        }
        variaveis[j] = realloc(variaveis[j], sizeof(char*)*(i+1));
        variaveis[j][i] = NULL;

        j++;
    }
    return variaveis;
}
void setVariaveis(TABLE table, char*** newVariaveis){
    table->variaveis = newVariaveis;
}


TABLE init_table(){

	TABLE table = malloc(sizeof(struct table));
	
	table->variaveis = malloc(sizeof(char**));
    table->variaveis[0] = NULL;
	table->numLin  = 0;
	table->numLinTotal = 0;
	
	return table;
}

void add_linha(TABLE table, char** linha){
    int nLinhas = getNumLinTotal(table);
    table->variaveis[nLinhas] = linha;
    nLinhas++;
    table->variaveis = realloc(table->variaveis, sizeof(char**)*(nLinhas+1));
    table->variaveis[nLinhas] = NULL;
    setNumLinTotal(table, nLinhas);
}


char** init_linha(){
    char ** linha = malloc(sizeof(char*));
    linha[0]=NULL;
    return linha;
}

char** add_palavra(char **linha, char* palavra){
    int nPalavras =0;
    while(linha[nPalavras]) nPalavras++;
    
    linha[nPalavras] = strdup(palavra);
    nPalavras ++;
    linha = realloc(linha, sizeof(char*)*(nPalavras+1));
    linha[nPalavras] = NULL;
    return linha;
}

TABLE load_table(char ***info){

    TABLE table = init_table();

    int j = 0, i;

    while(info){
        table->variaveis = realloc(table->variaveis, sizeof(char**)*(j+1));

        table->variaveis[j] = NULL;

        for(i = 0; info[j]; i++){
            table->variaveis[j] = realloc(table->variaveis[j], sizeof(char*)*(i+1));
            table->variaveis[j][i] = strdup(info[j][i]);
        }
        table->variaveis[j] = realloc(table->variaveis[j], sizeof(char*)*(i+1));
        table->variaveis[j][i] = NULL;

        table->numLin = j;
        j++;
    }

    table->numLinTotal = j;

    return table;
}


void printLinha (char **variaveis){

    for(int i = 0; variaveis[i] != NULL; i++){
        printf("| %s", variaveis[i]);
    }
    //printf("\n");
}


void printPagina (TABLE table){
    
    int linha, maxPorPag;
    
    printf("|");
    for(int i = 0; i < 100 ; i++){
        printf("-");
    } 
    printf("\n");
    
    for(linha = getNumLin(table), maxPorPag = 0; linha < getNumLinTotal(table) && maxPorPag < 10; linha++, maxPorPag++){
        printLinha(table->variaveis[linha]);
        printf("|");
        for(int i = 0; i < 100; i++){
            printf("-");
        }
        printf("\n");
    }
    setNumLin(table, linha);
}


int acao(TABLE table){
    
    int r = 0;

    printf("Que página pretende ver a seguir?\n");

    while(r == 0){
        char tecla = getchar();

        int numLinAtual = getNumLin(table);

        if (tecla == 'k' || tecla == 'K'){ // Avança na página
            setNumLin(table, numLinAtual++);
            printPagina(table);
        }
        else if (tecla == 'j' || tecla == 'J'){ // Recua na página 
            setNumLin(table, numLinAtual-20);
            printPagina(table);
        }
        else if (tecla == 'q'){
            r = 1;
        }
        else
            if(tecla != 0x0A) printf("comando inexistente \n");
    }
    return r;
}



