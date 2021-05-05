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


char** init_linha(){
    char ** linha = malloc(sizeof(char*));
    linha[0] = NULL;
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


void add_linha(TABLE table, char** linha){
    int nLinhas = getNumLinTotal(table);
    table->variaveis[nLinhas] = linha;
    nLinhas++;
    table->variaveis = realloc(table->variaveis, sizeof(char**)*(nLinhas+1));
    table->variaveis[nLinhas] = NULL;
    setNumLinTotal(table, nLinhas);
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
    
}
void promptPag (){
    printf ("\n# ");
    printf (">> ");
}

int acao(TABLE table){
    
    int r = 0;
    int numLinAnterior = 0;
    
    printf("\nINSTRUCTIONS\n");
    printf("k or K to go DOWN\n");
    printf("j or J to go UP\n");
    printf("q or Q to QUIT\n");
    promptPag();
        char str[1028];
        fgets(str,1028,stdin);
        char tecla = str[0];

        int numLinAtual = getNumLin(table);
        int numLinTotal = getNumLinTotal(table);
        int pagTotal = (getNumLinTotal(table)/10)+1;
        int pagAtual = (getNumLin(table)/10)+1;
    
    
  
        if (tecla == 'k' || tecla == 'K'){ // Avança na página
           
            if(numLinAtual+10 < numLinTotal)
                setNumLin(table, numLinAtual+10);
            clearScreen();
            
        }
        else if (tecla == 'j' || tecla == 'J'){ // Recua na página 
        
            if(0 <= numLinAtual-10)
                setNumLin(table, numLinAtual-10);
            clearScreen();
        }
        else if (tecla == 'q' || tecla == 'Q'){
            r = 1;
        }
        else {
            
            clearScreen();
            promptPag();
            printf("        !COMANDO INEXISTENTE! \n");//if(tecla != 0x0A)
        }
    return r;
}

void clearScreen(){
    printf("\e[1;1H\e[2J");
}