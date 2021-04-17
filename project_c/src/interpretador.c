#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpretador.h"
#include "paginacao.h"

#define ERRO_IO 1
#define COMANDO_INEXISTENTE 2
#define BUF_SIZE 1024

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

