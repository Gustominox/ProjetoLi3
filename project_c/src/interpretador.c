#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpretador.h"

#define ERRO_IO 1
#define COMANDO_INEXISTENTE 2
#define BUF_SIZE 1024
void
print_uppercase_words (const gchar *string)
{
  // Print all uppercase-only words.
  GRegex *regex;
  GMatchInfo *match_info;
 
  regex = g_regex_new ("[A-z/;.]+", 0, 0, NULL);//[A-z]+ = [A-z]+[(][a-z]+, '[A-z]'[)];
  g_regex_match (regex, string, 0, &match_info);
  while (g_match_info_matches (match_info))
    {
      gchar *word = g_match_info_fetch (match_info, 0);
      g_print ("%s\n", word);
      g_free (word);
      g_match_info_next (match_info, NULL);
    }
  g_match_info_free (match_info);
  g_regex_unref (regex);

//	print_uppercase_words("x = businesses_started_by_letter(sgr, 'T');");
}

/*
void show(TABLE table){
    int colunas, linhas;
    printf("----------------------------------------------------------");
    printf();
    printf("|      business_id   |    name        |");
}
*/

typedef struct var{
    TABLE tabela;       // output de uma query
    char* nome;         // nome da variável
} *VAR;

/*
int interpretador(SGR sgr){
    char linha[BUF_SIZE];
    char **temp = NULL;
    // char col[2], lin[2];
    // char cmdname[BUF_SIZE];
    // char filename[BUF_SIZE];

    char letter;
    TABLE x;

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return ERRO_IO;

    int i;
    for(i = 0; linha != NULL; i++){
        temp = realloc(temp,sizeof(char*)*(i+1));
        temp[i] = strsep(&temp, ";");
    }

    temp[i] = NULL;
    // nomeFuncao =  businesses_started_by_letter
    int k = 0;
    while (temp != NULL){
        
        switch(temp){

            case (strcmp(temp[k],"businesses_started_by_letter")==0):
                x = businesses_started_by_letter(sgr, letter); // cria uma hash table em que a key é o nome/primeira letra? do bussiness
                break;

            case (strcmp(temp[k],"query3")==0):
                x = business_info(sgr, business_id);
                break;
        
            case (strcmp(temp[k],"query4")==0):
                x = businesses_reviewed(sgr, user_id);
                break;
               
            case (strcmp(temp[k],"query5")==0):           
                x = businesses_with_stars_and_city(sgr, stars, city);
                break;
        
            case (strcmp(temp[k],"query6")==0):
                x = top_businesses_by_city(sgr, top);
                break;  
        
            case (strcmp(temp[k],"query7")==0):
                x = international_users(sgr);
                break;
        
            case (strcmp(temp[k],"query8")==0):   
                x = top_businesses_with_category(sgr, top, categories);
                break;
        
            case (strcmp(temp[k],"query9")==0):
                x = reviews_with_word(sgr, top, word);
                break;
            
            case "quit":
                exit(0);

            default:    
                // s = COMANDO_INEXISTENTE;
                printf("comando inexistente");
        }
        k++;
    }
    
    for (int j = 0; j < tmh; j++)
        free (temp[j]);
}
*/
