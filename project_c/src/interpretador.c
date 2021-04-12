#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpretador.h"
#include "sgr.h"

#define ERRO_IO 1
#define COMANDO_INEXISTENTE 2
#define BUF_SIZE 1024

/**void show(TABLE table){
    int colunas, linhas;
    
    printf();
    printf("|      business_id   |    name        |");


}

void show(TABLE x){
    printf("----------------------------------------------------------");
    ...
    int i = 0;
    while(i < tsize)
}*/
/*
int interpretador(SGR sgr){
    char linha[BUF_SIZE];
    char **temp = NULL;
    // char col[2], lin[2];
    // char cmdname[BUF_SIZE];
    // char filename[BUF_SIZE];
    char letter;
    TABLE x;
    // SINAL s = OK;

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return ERRO_IO;

    for(int i = 0; linha != NULL; i++){
        temp = realloc(temp,sizeof(char*)*(i+1));
        temp[i] = strsep(&temp, ";");
    }
    temp[i] = NULL;

    int k = 0;
    while (linha != NULL){
        
        switch(linha){

        case (strcmp(temp[k],"query2")==0):
            printf("Qual e a letra com que comeca o nome do negocio?");
            scanf("%c", &letter);
            x = businesses_started_by_letter(sgr, letter);
            // break;

        case (strcmp(temp[k],"query3")==0):
            x = business_info(sgr, business_id);
            // break;
        
        case (strcmp(temp[k],"query4")==0):
            x = businesses_reviewed(sgr, user_id);
            // break;
               
        case (strcmp(temp[k],"query5")==0):           
            x = businesses_with_stars_and_city(sgr, stars, city);
            // break;
        
        case (strcmp(temp[k],"query6")==0):
            x = top_businesses_by_city(sgr, top);
            // break;  
        
        case (strcmp(temp[k],"query7")==0):
            x = international_users(sgr);
            // break;
        
        case (strcmp(temp[k],"query8")==0):   
            x = top_businesses_with_category(sgr, top, categories);
            // break;
        
        case (strcmp(temp[k],"query9")==0):
            x = reviews_with_word(sgr, top, word);
            // break;
        
        case "quit":
            exit(0);

        default:    
          // s = COMANDO_INEXISTENTE;
          printf("comando inexistente");
    }
}
*/