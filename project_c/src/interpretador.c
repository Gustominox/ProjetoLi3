#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpretador.h"
#include "paginacao.h"

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
  regex = g_regex_new ("[A-z/;.=]+", 0, 0, NULL);//[A-z]+ = [A-z]+[(][a-z]+, '[A-z]'[)];
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
        for(int i = 0; i < 100 ; i++){
        printf("-");
        } 
    }        
}

void toCSV(TABLE var, char delim, char path[]){
    
    char **info = NULL;
    FILE *fd = fopen(path, "a");
    if (fd == NULL) printf ("Error opening freq file");
    
    int j;
    for(j = 0; var->variaveis[j] != NULL; j++){
        for(int i = 0; var->variaveis[j][i] != NULL; i++){
            fprintf(fd, var->variaveis[j][i]);
            fputc(delim, fd);
        }
        fputc('\n', fd);
    }
    free(fd);
}

int compare(char* qqcena, char* value, OPERATOR oper){
    
    int r = 1;
    if(oper == LT)
        if(qqcena < value) r = 0;
    if(oper == EQ)
        if(qqcena == value) r = 0;
    if(oper == GT)
        if(qqcena > value) r = 0;

    return r;
}

TABLE filter(TABLE var, char columName[], char* value, OPERATOR oper){

    TABLE nova = malloc(sizeof(struct table));
    setNumLinTotal(nova, 0);

    int linha = 0, flag = 0;

    for(int j = 0; var->variaveis[j] != NULL; j++){

        for(int i = 0; var->variaveis[j][i] != NULL; i++){

            if(strcmp(var->variaveis[j][i], columName) == 0)
                if(compare(var->variaveis[j][i], value, oper) == 0)
                    flag = 1;
        }
        if (flag){
            char **arr = NULL;
            int i = 0;
            for(i = 0; var->variaveis[j][i] != NULL; i++){
                arr = realloc(arr, sizeof(char*)*(i+1));
                arr[i] = strdup(var->variaveis[i]);
            }
            arr = realloc(arr, sizeof(char*)*(i+1));
            arr[i] = NULL;
            linha++;
        }
    }
    flag = 0;
    setNumLinTotal(nova, linha);
    nova->variaveis[linha] = arr;

    return nova;
}

TABLE proj(TABLE var, int cols){

    TABLE nova = malloc(sizeof(struct table));
    setNumLinTotal(nova, getNumLinTotal(var));
    setNumLin(nova, getNumLin(var));

    int i = 0, j = 0;
    char ***arr = NULL;

    for(int j = 0; var->variaveis[j] != NULL; j++){
        arr = realloc(arr, sizeof(char*)*(i+1));
        for(i = 0; i < cols; i++){
            arr[j] = realloc(arr, sizeof(char*)*(i+1));
            arr[j][i] = strdup(var->variaveis[j][i]);
        }   
    }
    nova->variaveis = arr;
    return nova;
}

TABLE fromCSV(char filepath[] ,char delim){

    TABLE table = malloc(sizeof(struct table));

    FILE *fp = fopen(filepath, "r"); 
    if (fp == NULL){
        printf ("Error opening file\n");
        return NULL;
    }

    char buffer[180000];
    int j=0; //linha

    while(fgets(buffer,180000,fp)){

        table->variaveis[j] = NULL;
        int i; //todos os caracteres ate encontrar uma virgula / coluna
        for( i = 0; buffer != NULL; i++){
            table->variaveis[j] = realloc(table->variaveis,sizeof(char)*(i+1));
            table->variaveis[j][i] = strdup(strsep(&buffer, ","));
        }
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
    char* funcao;
    // char col[2], lin[2];
    // char cmdname[BUF_SIZE];
    // char filename[BUF_SIZE];


     

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return ERRO_IO;

    info = doRegex(linha);
    
    
    if(isAssignment(linha)) funcao = info[2];
    else funcao = info[0];
    
    if (strcmp("businesses_started_by_letter",funcao == 0))
    {   
        printf("HELLOOOOOOOOO \n");
        //businesses_started_by_letter(sgr, letter);     
    }   
    else if (strcmp("business_info",funcao == 0))
    {
        //business_info(sgr, business_id);
    }
    else if (strcmp("businesses_reviewed",funcao == 0))
    {
        //businesses_reviewed(sgr, user_id);
    }    
    else if (strcmp("international_users",funcao == 0))
    {
        //international_users(sgr);
    }    
    else if (strcmp("top_businesses_with_category",funcao == 0))
    {
        //top_businesses_with_category(sgr, top, categories);
    }           
    else if (strcmp("reviews_with_word",funcao == 0))
    {
        //reviews_with_word(sgr, top, word);
    }    
    else{
        printf("comando inexistente");
    }
    
    

    
}

