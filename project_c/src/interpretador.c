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
    TABLE table;       // output de uma query
    char* nome;         // nome da variável
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
                int k = 0;
                while(k < strlen(value) && k < strlen(content)){
                    if(content[k] == value[k])
                        k++;
                    else if(content[k] < value[k]){
                        break;
                    }
                    else if(content[k] > value[k]){
                        isValid = 0;
                        break;
                    }
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
                int k = 0;
                while(k < strlen(value) && k < strlen(content)){
                    if(content[k] == value[k]){
                        isValid = 0;
                        k++;
                    }
                    else{
                        isValid = 1;
                        break;
                    }
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
                int k = 0;
                while(k < strlen(value) && k < strlen(content)){
                    if(content[k] == value[k])
                        k++;
                    else if(content[k] > value[k]){
                        break;
                    }
                    else if(content[k] < value[k] || content[k] == '\n'){
                        isValid = 0;
                        break;
                    }
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
    novaTable->variaveis = realloc(novaTable->variaveis, sizeof(char**));

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
        flag = 0;
        j++;
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

void maxOrMin(TABLE table, char columName[], OPERATOR op){

    int col;

    for(int i = 0; table->variaveis[0][i] != NULL; i++)
        if(strcmp(table->variaveis[0][i], columName) == 0){
            col = i;
            printf("%s: ", table->variaveis[0][i]);
            break;
        }

    char* extremo = malloc(sizeof(char*));
    extremo = table->variaveis[1][col];

    for(int j = 1; j < getNumLinTotal(table); j++){
        if(compare(table->variaveis[j][col], extremo, op) == 0){
            extremo = strdup(table->variaveis[j][col]);
        }
    }

    printf("%s\n", extremo);
}

int isAssignment(char *linha){

    if(strchr(linha,'=') != NULL) return 1;
    else return 0;    
}

int verificaVar(struct var vars[], char* var){
    int j = 0, posicao = 0;
    while(j<10 && strcmp(vars[j]->nome, var) != 0){
        j++;
    }
    posicao = j;
    if(posicao<10) return posicao;
    else return -1;
}

OPERATOR stringToOperator(char* oper){
        OPERATOR operador;

        if(strcmp("LT",oper) == 0){
                operador = LT;
        }

        if(strcmp("EQ",oper) == 0){
                operador = EQ;
        }

        if(strcmp("GT",oper) == 0){
                operador = QT;
        }

        return operador;
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
        //printLinha(info);

        if(isAssignment(linha)) strcpy(funcao, info[2]);
        else strcpy(funcao, info[0]);

        if(isAssignment(linha) && i == 10){
            return MEM_FULL;
        }

        //table->variaveis[0] = realloc(table->variaveis[0], sizeof(char*)*(i+1));

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
        else if (strcmp("show",funcao) == 0) 
        {
                int posicao = verificaVar(vars, info[1]);
                if(posicao != -1) show(vars[posicao]->table);
                else printf("A TABLE nao existe");
        }         
        else if (strcmp("toCSV",funcao) == 0)
        {
                int posicao = verificaVar(vars, info[1]);
                if(posicao != -1) toCSV(vars[posicao]->table, info[2][0], info[3]);
                else printf("A TABLE nao existe");
        } 
        else if (strcmp("fromCSV",funcao) == 0)
        {
                vars[i]->nome = info[0];
                vars[i]->table = fromCSV(info[3], info[4]);
                i++;
        } 
        else if (strcmp("filter",funcao) == 0)
        {
                int posicao = verificaVar(vars, info[3]);
                if(posicao != -1){
                    vars[i]->nome = info[0];
                    vars[i]->table = filter(vars[posicao]->table, info[4], info[5], info[6]);
                    i++;
                }
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
        else if (strcmp("quit",funcao) == 0)
        {
                return EXIT_CODE;
        }
        else{
            free_sgr(sgr);
            fgets(linha, BUF_SIZE, stdin);  
            printf("Sintaxe errada, tente novamente. \n");
        }
    }
}


