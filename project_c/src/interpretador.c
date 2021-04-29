#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpretador.h"


#define EXIT_CODE 0
#define ERRO_IO 1
#define COMANDO_INEXISTENTE 2
#define MEM_FULL 3
#define BUF_SIZE 1024


struct var{
    TABLE* table;       // output de uma query
    char** nome;         // nome da variável
};


char **doRegex (const gchar *string){
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


int show (TABLE table){

    int r;

    printf("|");
    for(int i = 0; i < 100 ; i++){
        printf("-");
    } 
    printf("\n");

    printPagina(table);

    printf("\n");

    if((getNumLinTotal(table) - 10) > 0){
        r = acao(table);
        if(r != 0) return r;
        //r = show (table);
        //return r;
    }
}

void toCSV(TABLE table, char delim, char path[]){

    FILE *fd = fopen(path, "a");
    if (fd == NULL){
        printf("Error opening file\n");
        return;
    } 
    int j = 0;
    while(j < getNumLinTotal(table)){

        for(int i = 0; table->variaveis[j][i] != NULL; i++){
            if (i != 0) fputc(delim, fd);
            fprintf(fd, "%s", table->variaveis[j][i]);
        }
        fputc('\n', fd);
        j++;
   }
   fclose(fd);
}

TABLE fromCSV(char filepath[] ,char *delim){

    TABLE table = malloc(sizeof(struct table));

    FILE *fd = fopen(filepath, "r");
    if (fd == NULL){
        printf ("Error opening file\n");
        return NULL;
    }

    char *buffer;
    buffer = malloc(sizeof(char)*180000);
    int j=0, i;

    table->variaveis = NULL;

    while(fgets(buffer,180000,fd)){

        char *temp = strdup(buffer);
        
        table->variaveis = realloc(table->variaveis,sizeof(char**)*(j+1));
        table->variaveis[j] = NULL;
        
        for(i = 0; temp != NULL; i++){
            table->variaveis[j]= realloc(table->variaveis[j],sizeof(char*)*(i+1));
            table->variaveis[j][i]= strdup(strsep(&temp, delim));
        }
        table->variaveis[j][i-1] = strsep(&table->variaveis[j][i-1], "\n");
        table->variaveis[j] = realloc(table->variaveis[j],sizeof(char*)*(i+1));
        table->variaveis[j][i] = NULL;
        j++;
    }
    setNumLinTotal(table,j);
    setNumLin(table,0);

    free(buffer);
    fclose(fd);

    return table;
}

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

    int i, linhas = 1, j = 1, flag = 0, col;
    
    novaTable->variaveis = NULL;
    novaTable->variaveis = realloc(novaTable->variaveis, sizeof(char**)*(linhas+1));

    novaTable->variaveis[0] = NULL;
    for(int i = 0; table->variaveis[0][i] != NULL; i++){
        if(strcmp(table->variaveis[0][i], columName) == 0) col = i;
        novaTable->variaveis[0] = realloc(novaTable->variaveis[0], sizeof(char*)*(i+1));
        novaTable->variaveis[0][i] = strdup(table->variaveis[0][i]);
    }
    while(j < getNumLinTotal(table)){
        
        novaTable->variaveis = realloc(novaTable->variaveis, sizeof(char**)*(linhas+1));

        if(compare(table->variaveis[j][col], value, oper) == 0) flag = 1;

        novaTable->variaveis[linhas] = NULL;
        if(flag){
            for(i = 0; table->variaveis[j][i] != NULL; i++){
                novaTable->variaveis[linhas] = realloc(novaTable->variaveis[linhas], sizeof(char*)*(i+1));
                novaTable->variaveis[linhas][i] = strdup(table->variaveis[j][i]);
            }
            novaTable->variaveis[linhas] = realloc(novaTable->variaveis[linhas], sizeof(char*)*(i+1));
            novaTable->variaveis[linhas][i] = NULL;
            linhas++;
        }
        flag = 0; j++;
    }
    setNumLinTotal(novaTable, linhas);
    setNumLin(table, 0);
    return novaTable;
}

TABLE proj(TABLE table, int cols){

    TABLE novaTable = malloc(sizeof(struct table));

    int j = 0, i;
    novaTable->variaveis = NULL;

    while(j < getNumLinTotal(table)){

        novaTable->variaveis = realloc(novaTable->variaveis, sizeof(char**)*(j+1));
        novaTable->variaveis[j] = NULL;

        for(i = 0; table->variaveis[j][i] != NULL && i < cols; i++){
            novaTable->variaveis[j] = realloc(novaTable->variaveis[j], sizeof(char*)*(i+1));
            novaTable->variaveis[j][i] = strdup(table->variaveis[j][i]);
        }
        novaTable->variaveis[j] = realloc(novaTable->variaveis[j],sizeof(char*)*(i+1));
        novaTable->variaveis[j][i] = NULL;
        j++;
    }
    setNumLinTotal(novaTable, getNumLinTotal(table));
    setNumLin(novaTable, getNumLin(table));
    return novaTable;
}

TABLE indexa (TABLE table, int linha, int coluna){

    TABLE resultado = malloc(sizeof(struct table));
    
    resultado->variaveis = NULL;
    resultado->variaveis = realloc(table->variaveis,sizeof(char**)*2);

    resultado->variaveis[0] = NULL;
    resultado->variaveis[0]= realloc(table->variaveis[0],sizeof(char*)*2);

    resultado->variaveis[0][0]= strdup(table->variaveis[0][coluna]);
    resultado->variaveis[0][1] = NULL;
    
    resultado->variaveis[1][0]= strdup(table->variaveis[linha][coluna]);
    resultado->variaveis[1][1] = NULL;

    setNumLinTotal(resultado, 2);
    return resultado;
}

TABLE max(TABLE table, char columName[]){

    TABLE novaTable = malloc(sizeof(struct table));

    int col;

    for(int i = 0; table->variaveis[0][i] != NULL; i++)
        if(strcmp(table->variaveis[0][i], columName) == 0) col = i;

    char* maximo = malloc(sizeof(char*));
    maximo = table->variaveis[1][col];

    novaTable->variaveis = NULL;
    novaTable->variaveis = realloc(novaTable->variaveis, sizeof(char**)*2);

    novaTable->variaveis[0] = NULL;
    novaTable->variaveis[0] = realloc(novaTable->variaveis[0], sizeof(char*));

    novaTable->variaveis[0][0] = strdup(table->variaveis[0][col]);
    novaTable->variaveis[0][1] = NULL;

    novaTable->variaveis[1] = NULL;
    novaTable->variaveis[1] = realloc(novaTable->variaveis[1], sizeof(char*));

    for(int j = 1; j < getNumLinTotal(table); j++)
        if(compare(table->variaveis[j][col], maximo, GT) == 0)
            maximo = strdup(table->variaveis[j][col]);

    novaTable->variaveis[1][0] = maximo;
    novaTable->variaveis[0][1] = NULL;

    setNumLinTotal(novaTable, 2);
    return novaTable;
}

TABLE min(TABLE table, char columName[]){

    TABLE novaTable = malloc(sizeof(struct table));

    int col;

    for(int i = 0; table->variaveis[0][i] != NULL; i++)
        if(strcmp(table->variaveis[0][i], columName) == 0) col = i;

    char* minimo = malloc(sizeof(char*));
    minimo = table->variaveis[1][col];

    novaTable->variaveis = NULL;
    novaTable->variaveis = realloc(novaTable->variaveis, sizeof(char**)*2);

    novaTable->variaveis[0] = NULL;
    novaTable->variaveis[0] = realloc(novaTable->variaveis[0], sizeof(char*));

    novaTable->variaveis[0][0] = strdup(table->variaveis[0][col]);
    novaTable->variaveis[0][1] = NULL;

    novaTable->variaveis[1] = NULL;
    novaTable->variaveis[1] = realloc(novaTable->variaveis[1], sizeof(char*));

    for(int j = 1; j < getNumLinTotal(table); j++)
        if(compare(table->variaveis[j][col], minimo, LT) == 0)
            minimo = strdup(table->variaveis[j][col]);

    novaTable->variaveis[1][0] = minimo;
    novaTable->variaveis[1][1] = NULL;

    setNumLinTotal(novaTable, 2);
    return novaTable;
}

int isAssignment(char *linha){

    if(strchr(linha,'=') != NULL) return 1;
    else return 0;    
}

int interpretador(){
    char linha[BUF_SIZE];
    char **info;
    char funcao[100];
    struct var vars[10];
    

    printf("LOADING...\n");
    SGR sgr = load_sgr(NULL,NULL,NULL);
    printf("FINISHED!\n");

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return ERRO_IO;

    int i = 0;

    while(linha){

        info = doRegex(linha);
        printLinha(info);

        if(isAssignment(linha)) strcpy(funcao, info[2]);
        else strcpy(funcao, info[0]);

        table->variaveis[0] = realloc(table->variaveis[0], sizeof(char*)*(i+1));

        if (strcmp("businesses_started_by_letter",funcao) == 0)
        {   
            vars[i]->nome = info[0];
            vars[i]->table = businesses_started_by_letter(sgr, info[4][0]);     
            i++;
        }   
        else if (strcmp("business_info",funcao) == 0)
        {
            vars[i]->nome= info[0];
            vars[i]->table = business_info(sgr, info[4]);
            i++;
        }
        else if (strcmp("businesses_reviewed",funcao) == 0)
        {
            vars[i]->nome = info[0];
            vars[i]->table = businesses_reviewed(sgr, info[4]);
            i++;
        }
        else if (strcmp("businesses_with_stars_and_city",funcao) == 0)
        {
            vars[i]->nome = info[0];
            vars[i]->table =businesses_with_stars_and_city(sgr, atof(info [4]), info[5]);
            i++;
        }
        else if (strcmp("top_businesses_by_city",funcao) == 0)
        {
            vars[i]->nome = info[0];
            vars[i]->table = top_businesses_by_city(sgr, atoi(info [4]));
            i++;
        }
        else if (strcmp("international_users",funcao) == 0)
        {
            vars[i]->nome = info[0];
            vars[i]->table = international_users(sgr);
            i++;
        }    
        else if (strcmp("top_businesses_with_category",funcao) == 0)
        {
            vars[i]->nome = info[0];
            vars[i]->table = top_businesses_with_category(sgr, atoi(info[4]), info[5]);
            i++;
        }           
        else if (strcmp("reviews_with_word",funcao) == 0)
        {
            vars[i]->nome = info[0];
            vars[i]->table = reviews_with_word(sgr, atoi(info[4]), info[5]);
            i++;
        }
        else if (strcmp("show",funcao) == 0) {
                int j = 0, posicao = 0;
                while(j<10 && strcmp(var[j]->nome,info[1]) != 0){
                    posicao = j;
                    j++;
                }
                    //ou sai do ciclo porque j>=10 ou porque encontrou a variavel
                if(posicao<10) show(var[posicao]->table);
                else printf("A TABLE PEDIDA NAO EXISTE");
        } 
        else if (strcmp("toCSV",funcao) == 0)
        {
            
        } 
        else if (strcmp("fromCSV",funcao) == 0)
        {

        } 
        else if (strcmp("filter",funcao) == 0)
        {

        } 
        else if (strcmp("proj",funcao) == 0)
        {

        } 
        else if (strcmp("indexa",funcao) == 0)
        {

        } 
        else if (strcmp("max",funcao) == 0)
        {

        } 
        else if (strcmp("min",funcao) == 0)
        {

        } 
        else{
            free_sgr(sgr);
            fgets(linha, BUF_SIZE, stdin);  
            printf("Sintaxe errada, tente novamente. \n");
        }
    }
}


