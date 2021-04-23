#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpretador.h"
#include "paginacao.h"
#include "auxiliares.h"
#include "sgr.h"

#define ERRO_IO 1
#define COMANDO_INEXISTENTE 2
#define BUF_SIZE 1024

typedef enum{
    LT,
    EQ,
    GT
} OPERATOR;

/*
struct var{
    TABLE tabela;       // output de uma query
    char* nome;         // nome da variável
};
*/

char **
doRegex (const gchar *string)
{
  // Print all uppercase-only words.
  GRegex *regex;
  GMatchInfo *match_info;
  char **info = NULL;
  int i = 0;
  regex = g_regex_new ("[A-z0-9/;.=]+", 0, 0, NULL);//[A-z]+ = [A-z]+[(][a-z]+, '[A-z]'[)];
  g_regex_match (regex, string, 0, &match_info);


  while (g_match_info_matches (match_info)){

    gchar *word = g_match_info_fetch (match_info, 0);
      
    info = realloc(info,sizeof(char*)*(i+1));
    info[i] = strdup(word);

    i++;

    //g_print ("%s\n", word);
    
    g_free (word);
    g_match_info_next (match_info, NULL);
    }
    info = realloc(info,sizeof(char*)*(i+1));
    info[i] = NULL;
  g_match_info_free (match_info);
  g_regex_unref (regex);
  return info;
//	print_uppercase_words("x = businesses_started_by_letter(sgr, 'T');");
}


void show (TABLE table){

    int linha;

    printf("|");
    for(int i = 0; i < 100 ; i++){
        printf("-");
    } 
    printf("|\n");

    for(linha = 0; table->variaveis[linha] != NULL; linha++){
        printLinha(table->variaveis[linha]);
        printf("|");
        for(int i = 0; i < 100; i++){
            printf("-");
        } 
        printf("\n");
    }
}

void toCSV(TABLE table, char delim, char path[]){

    FILE *fd = fopen(path, "a");
    if (fd == NULL){
        printf("Error opening file\n");
        return;
    } 
    int j = 0;
    while(j < table->numLinTotal){

        for(int i = 0; table->variaveis[j][i] != NULL; i++){
            fprintf(fd, "%s", table->variaveis[j][i]);
            fputc(delim, fd);
            // printf("%s",table->variaveis[j][i]);
            // putchar(delim);
        }
        fputc('\n', fd);
        // printf("\n");
        j++;
   }
   fclose(fd);
}

// esta função retorna zero (isValid = 0) em caso de sucesso, 1 em caso de insucesso
int compare(char* content, char* value, OPERATOR oper){
    int isValid = 1;
    
    switch(oper){

        case LT:
            if(isInteger(value)){
                if(atoi(content) < atoi(value)) isValid = 0;
            }
            else if(isFloat(value)){
                if(atof(content) < atof(value)) isValid = 0;
            } else {
                for(int k = 0; k < strlen(value) || k < strlen(content); k++){
                    if(content[k] > value[k]) isValid = 0;
                    break;
                }
            }
            break;
        
        case EQ:
            if(isInteger(value)){
                if(atoi(content) == atoi(value)) isValid = 0;
            }
            else if(isFloat(value)){
                if(atof(content) == atof(value)) isValid = 0;
            } else {
                for(int k = 0; k < strlen(value) || k < strlen(content); k++){
                    if(content[k] == value[k]) isValid = 0;
                    break;
                }
            }
            break;

        case GT:
            if(isInteger(value)){
                if(atoi(content) > atoi(value)) isValid = 0;
            }
            else if(isFloat(value)){
                if(atof(content) > atof(value)) isValid = 0;
            } else { 
                for(int k = 0; k < strlen(value) || k < strlen(content); k++){
                    if(content[k] < value[k] || content[k] == '\n') isValid = 0;
                    break;
                }
            }
            break;
    }
    return isValid;
}

TABLE filter(TABLE table, char columName[], char* value, OPERATOR oper){

    TABLE novaTable = malloc(sizeof(struct table));
    setNumLinTotal(novaTable, 0);

    int linhas = 0, flag = 0, j = 0;

    int col; // col é o índice da coluna cujos valores serão comparados com value

    for(int i = 0; table->variaveis[0][i] != NULL; i++)
        if(strcmp(table->variaveis[0][i], columName) == 0) col = i;

    novaTable->variaveis = NULL;
    while(j < table->numLinTotal){
        
        novaTable->variaveis = realloc(novaTable->variaveis, sizeof(char**)*(linhas+1));
        novaTable->variaveis[linhas] = NULL;

        if(compare(table->variaveis[j][col], value, oper) == 0)
            flag = 1;

        if(flag){
            for(int i = 0; table->variaveis[j][i] != NULL; i++){
                novaTable->variaveis[linhas] = realloc(novaTable->variaveis, sizeof(char*)*(i+1));
                novaTable->variaveis[linhas][i] = strdup(table->variaveis[j][i]);
                printf("%s ", novaTable->variaveis[linhas][i]);
            }
            linhas++;
        }
        flag = 0;
    }
    setNumLinTotal(novaTable, linhas);

    return novaTable;
}

TABLE proj(TABLE table, int cols){

    TABLE novaTable = malloc(sizeof(struct table));
    setNumLinTotal(novaTable, getNumLinTotal(table));
    setNumLin(novaTable, getNumLin(table));

    for(int j = 0; table->variaveis[j] != NULL; j++){
        novaTable->variaveis = realloc(novaTable->variaveis, sizeof(char*)*(j+1));
        for(int i = 0; i < cols; i++){
            novaTable->variaveis[j] = realloc(novaTable->variaveis, sizeof(char*)*(i+1));
            novaTable->variaveis[j][i] = strdup(table->variaveis[j][i]);
        }   
    }
    return novaTable;
}
 
TABLE fromCSV(char filepath[] ,char *delim){

    TABLE table = malloc(sizeof(struct table));

    FILE *fp = fopen(filepath, "r"); 
    if (fp == NULL){
        printf ("Error opening file\n");
        return NULL;
    }

    char *buffer;
    buffer =  malloc(sizeof(char)*180000);
    int j=0; //linha

    table->variaveis = NULL;// string **variaveis
    while(fgets(buffer,180000,fp)){
        char *temp = strdup(buffer);
        table->variaveis = realloc(table->variaveis,sizeof(char**)*(j+1));
        table->variaveis[j] = NULL;
        int i; //todos os caracteres ate encontrar uma virgula / coluna
        //printf("%s", temp);
        for( i = 0; temp != NULL; i++){
            table->variaveis[j]= realloc(table->variaveis[j],sizeof(char*)*(i+1));
            table->variaveis[j][i]= strdup(strsep(&temp, delim));
            //printf("%s\n", table->variaveis[j][i]);
        }
        table->variaveis[j]= realloc(table->variaveis[j],sizeof(char*)*(i+1));
        table->variaveis[j][i] = NULL;
        j++;
    }
    setNumLinTotal(table,j);
    setNumLin(table,0);

    free(buffer);

    return table;
}

int isAssignment(char *linha){

    if(strchr(linha,'=') != NULL) return 1;
    else return 0;    

}

int interpretador(){
    char linha[BUF_SIZE];
    char **info;
    char funcao[100];
    // char col[2], lin[2];
    // char cmdname[BUF_SIZE];
    // char filename[BUF_SIZE];

    printf("LOADING...\n");
    SGR sgr = load_sgr(NULL,NULL,NULL);
    printf("FINISHED!\n");

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return ERRO_IO;

    info = doRegex(linha);
    printLinha(info);

    if(isAssignment(linha)) strcpy(funcao, info[2]);
    else strcpy(funcao, info[0]);
    
    if (strcmp("businesses_started_by_letter",funcao) == 0)
    {   
        //businesses_started_by_letter(sgr, info[4][0]);     
    }   
    else if (strcmp("business_info",funcao) == 0)
    {
        business_info(sgr, info[2]);
    }
    else if (strcmp("businesses_reviewed",funcao) == 0)
    {
        //businesses_reviewed(sgr, user_id);
    }    
    else if (strcmp("international_users",funcao) == 0)
    {
        //international_users(sgr);
    }    
    else if (strcmp("top_businesses_with_category",funcao) == 0)
    {
        //top_businesses_with_category(sgr, top, categories);
    }           
    else if (strcmp("reviews_with_word",funcao) == 0)
    {
        //reviews_with_word(sgr, top, word);
    }    
    else{
        free_sgr(sgr);
        fgets(linha, BUF_SIZE, stdin);  
        printf("Sintaxe errada, tente novamente. \n");
    }
     
}

