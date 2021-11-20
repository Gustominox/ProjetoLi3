#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpretador.h"
#include "paginacao.h"
#include "auxiliares.h"
#include "sgr.h"
#include <time.h>


#define EXIT_CODE 0
#define ERRO_IO 1
#define COMANDO_INEXISTENTE 2
#define MEM_FULL 3
#define BUF_SIZE 1024


struct var{
    TABLE table;       // output de uma query
    char* nome;         // nome da variável
};


void show (TABLE table){
    clearScreen();
    int r = 0;
    setNumLin(table,0);

    while(!r){
        int pagTotal = (getNumLinTotal(table)/10)+1;
        int pagAtual = (getNumLin(table)/10)+1;
        printf("\n   Pag %d out of %d\n\n",pagAtual,pagTotal);
        printPagina(table);
        
        r = acao(table);
    }
}

void toCSV(TABLE table, char delim, char path[]){

    FILE *fd = fopen(path, "a");

    if (fd == NULL){
        printf("Error opening file\n");
        return;
    }
    
    char ***aux = getVariaveis(table);

    int j = 0;
    while(j < getNumLinTotal(table)){

        for(int i = 0; aux[j][i] != NULL; i++){
            if (i != 0) fputc(delim, fd);
            fprintf(fd, "%s", aux[j][i]);
        }
        j++;
   }
   fclose(fd);
}

TABLE fromCSV(char filepath[] ,char *delim){

    TABLE table = init_table();

    FILE *fd = fopen(filepath, "r");
    if (fd == NULL){
        printf ("Error opening file\n");
        return NULL;
    }

    char *buffer;
    char **linha;
    buffer = malloc(sizeof(char)*180000);
    int j=0, i;
    
    while(fgets(buffer,180000,fd)){//para cada linha

        char *temp = strdup(buffer);
        
        linha = init_linha();
        for(i = 0; temp != NULL; i++){
            linha = add_palavra(linha,strsep(&temp, delim));
        }
        add_linha(table,linha);
    }
    free(buffer);
    fclose(fd);

    return table;
}


TABLE filter(TABLE table, char columName[], char* value, OPERATOR oper){

    int i, linhas = 1, j = 1, flag = 0, col;

    TABLE novaTable = init_table();
    char **linha;

    char ***variaveis = getVariaveis(table);
    linha = init_linha();

    //escrever cabeçalho
    for(int i = 0; variaveis[0][i] != NULL; i++){
        if(strcmp(variaveis[0][i], columName) == 0) col = i;
        linha = add_palavra(linha,variaveis[0][i]);
    }
    add_linha(novaTable,linha);

    while(j < getNumLinTotal(table)){
        
        if(compare(variaveis[j][col], value, oper) == 0) flag = 1;

        if(flag){
            linha = init_linha();
            for(i = 0; variaveis[j][i] != NULL; i++){
                linha = add_palavra(linha, variaveis[j][i]);
            }
            add_linha(novaTable,linha);
        }
        flag = 0;
        j++;
    }
    return novaTable;
}


TABLE proj(TABLE table, int cols){

    TABLE novaTable = init_table();

    char ***variaveis = getVariaveis(table);

    char **linha;

    int j = 0, i;

    while(j < getNumLinTotal(table)){
        linha = init_linha();
        for(i = 0; variaveis[j][i] != NULL && i < cols; i++){
            linha = add_palavra(linha, variaveis[j][i]);
        }
        j++;
        linha = add_palavra(linha,"\n");
        add_linha(novaTable, linha);
    }
    return novaTable;
}


TABLE indexa (TABLE table, int lin, int col){

    TABLE resultado = init_table();
    char ***variaveis = getVariaveis(table);
    
    char **linha = init_linha();

    linha = add_palavra(linha, variaveis[0][col]);
    linha = add_palavra(linha,"\n");
    add_linha(resultado, linha);

    linha = init_linha();
    linha = add_palavra(linha,variaveis[lin][col]);
    linha = add_palavra(linha,"\n");
    add_linha(resultado,linha);

    return resultado;
}


void maxOrMin(TABLE table, char columName[], OPERATOR op){

    int col;
    char ***variaveis = getVariaveis(table);

    for(int i = 0; variaveis[0][i] != NULL; i++)
        if(strcmp(variaveis[0][i], columName) == 0){
            col = i;
            printf("%s: ", variaveis[0][i]);
            break;
        }

    char* extremo = malloc(sizeof(char*));
    extremo = variaveis[1][col];

    for(int j = 1; j < getNumLinTotal(table); j++){
        if(compare(variaveis[j][col], extremo, op) == 0){
            extremo = variaveis[j][col];
        }
    }

    printf("%s\n", extremo);
}

int isAssignment(char *linha){

    if(strchr(linha,'=') != NULL) return 1;
    else return 0;    
}

int verificaVar(VAR vars, int N, char* var){
    int j = 0, posicao = 0;
    while(j<N && strcmp(vars[j].nome, var) != 0){
        j++;
    }
    posicao = j;
    if(posicao<N) return posicao;
    else return posicao = -1;
}

void prompt (){
    printf ("\n# ");
    printf ("> ");
}

int interpretador(SGR sgr){
    char linha[BUF_SIZE];
    char **info;
    char funcao[100];
    struct var vars[10];

    int i = 0;
    int flagQuery9 = 1;
    while(linha){
        prompt();
        if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return ERRO_IO;
        //printf("%s\n",strchr(linha,'['));
        info = doRegex(linha,"[A-z0-9/;.=]+");
        int length = len(info);
        
        

        if(isAssignment(linha)) strcpy(funcao, info[2]);
        else strcpy(funcao, info[0]);

        if(isAssignment(linha) && i == 10){
            return MEM_FULL;
        }

        if(!(strcmp("load_sgr", funcao))&&(length==5))
        {
            if (!strcmp(info[1],"NULL")) info[1] = NULL;
            if (!strcmp(info[2],"NULL")) info[2] = NULL;
            if (!strcmp(info[3],"NULL")) info[3] = NULL;
            free_sgr(sgr);
            flagQuery9 =1;
            sgr = load_sgr(NULL,NULL,NULL);
        }
        else if (!(strcmp("businesses_started_by_letter",funcao))&&(length==6))
        {   
                vars[i].nome = info[0];

                vars[i].table = businesses_started_by_letter(sgr, info[4][0]);     
                
                
                i++;
        }   
        else if ((!strcmp("business_info",funcao))&&(length==6))
        {
                vars[i].nome= info[0];
                vars[i].table = business_info(sgr, info[4]);
                i++;
        }
        else if (!(strcmp("businesses_reviewed",funcao))&&(length==6))
        {
                vars[i].nome = info[0];
                vars[i].table = businesses_reviewed(sgr, info[4]);
                i++;
        }
        else if ((!strcmp("businesses_with_stars_and_city",funcao))&&(length==7))
        {
                vars[i].nome = info[0];
                vars[i].table =businesses_with_stars_and_city(sgr, atof(info [4]), info[5]);
                i++;
        }
        else if ((!(strcmp("top_businesses_by_city",funcao)))&&(length==6))
        {
                vars[i].nome = info[0];
                vars[i].table = top_businesses_by_city(sgr, atoi(info [4]));
                i++;
        }
        else if ((!(strcmp("international_users",funcao)))&&(length==5))
        {
                vars[i].nome = info[0];
                vars[i].table = international_users(sgr);
                i++;
        }    
        else if ((!(strcmp("top_businesses_with_category",funcao)))&&(length==7))
        {
                vars[i].nome = info[0];
                vars[i].table = top_businesses_with_category(sgr, atoi(info[4]), info[5]);
                i++;
        }           
        else if ((!(strcmp("reviews_with_word",funcao)))&&(length==7))
        {
                clock_t Ticks[2];
                Ticks[0] = clock();
	
                if (flagQuery9) {
                    threadQuery9(sgr);
                    flagQuery9 = 0;
                }
                vars[i].nome = info[0];
                vars[i].table = reviews_with_word(sgr, atoi(info[4]), info[5]);
                Ticks[1] = clock();
                double time = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
                printf("\nTempo de execucao da QUERY (segundos): %g\n",time);
    
                i++;
        }
        else if ((!(strcmp("show",funcao)))&&(length==3)) 
        {
                int posicao = verificaVar(vars, i, info[1]);
                if(posicao != -1) show(vars[posicao].table);
                else printf("A TABLE nao existe\n");
                printf("SHOW TERMINOU\n");
        }         
        else if ((!(strcmp("toCSV",funcao)))&&(length==5)) 
        {
                int posicao = verificaVar(vars, i, info[1]);
                if(posicao != -1) toCSV(vars[posicao].table, info[2][0], info[3]);
                else printf("A TABLE nao existe\n");
        } 
        else if ((!(strcmp("fromCSV",funcao)))&&(length==6)) 
        {
                vars[i].nome = info[0];
                vars[i].table = fromCSV(info[3], info[4]);
                i++;
        } 
        else if ((!(strcmp("filter",funcao)))&&(length==8)) 
        {
                int posicao = verificaVar(vars, i, info[3]);
                if(posicao != -1){
                    vars[i].nome = info[0];
                    vars[i].table = filter(vars[posicao].table, info[4], info[5], stringToOperator(info[6]));
                    i++;
                }
        } 
        else if ((!(strcmp("proj",funcao)))&&(length==5)) 
        {
                int posicao = verificaVar(vars, i, info[3]);
                if(posicao != -1){
                    vars[i].nome = info[0];
                    vars[i].table = proj(vars[posicao].table, atoi(info[4]));
                    i++;
                }
        } 
        else if ((!(strcmp("indexa", funcao)))&&(length==7))
        {
                int posicao = verificaVar(vars, i, info[3]);
                if(posicao != -1){
                    vars[i].nome = info[0];
                    vars[i].table = indexa(vars[posicao].table, atoi(info[4]), atoi(info[5]));
                    i++;
                }
        } 
        else if ((!(strcmp("max",funcao)))&&(length==5)) 
        {
                int posicao = verificaVar(vars, i, info[1]);
                if(posicao != -1){
                    maxOrMin(vars[posicao].table, info[2], stringToOperator(info[3]));
                }
        } 
        else if ((!(strcmp("min",funcao)))&&(length==5))
        {
                int posicao = verificaVar(vars, i, info[1]);
                if(posicao != -1){
                    maxOrMin(vars[posicao].table, info[2], stringToOperator(info[3]));
                }
        }
        else if (strcmp("quit",funcao) == 0)
        {
            free_sgr(sgr);
            return EXIT_CODE;
        }
        else{
             
            printf("Sintaxe errada, tente novamente. \n");
        }
        
    }
}
