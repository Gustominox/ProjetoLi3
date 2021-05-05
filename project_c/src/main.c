/**
@file main.c
Função que controla o progama.
*/
/**
@mainpage Projeto Li3

*/
#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>
#include "sgr.h"
#include "paginacao.h"
#include <ctype.h>
#include "auxiliares.h"
#include "interpretador.h"

int main(int argc, char *argv[]) {

int r = 0;

clearScreen();
printf("STARTED LOADING SGR...\n");
SGR sgr = load_sgr(NULL,NULL,NULL);
printf("FINISHED LOADING SGR!\n");
clearScreen();

r = interpretador(sgr);



/*
char linha[1024];

int tmh;
char **info;
info = lerFichCsv(&tmh,"input/users_full.csv");
printf("Espera\n");
fgets(linha, 1024, stdin);
USER *bus = NULL;
transStructToTable(hash2,bus,getUserName);

printf("There are %d keys in the hash table\n",
        g_hash_table_size(hash));
printf("There are %d keys in the hash table\n",
        g_hash_table_size(hash1));
GSList* list = g_hash_table_lookup(hash1,"cojecOwQJpsYDxnjtgzteQ");
printf ("%x\n",getUserName( list->data));

fgets(linha, 1024, stdin);
*/



//printf("LOADING...\n");


//sgr = load_sgr(NULL,NULL,NULL);
//threadQuery9(sgr);
//printf("FINISHED!\n");
//TABLE b = reviews_with_word(sgr, 10, "bad");
//TABLE table = business_info(sgr,"pCFTvC1v0B9Wilm8XixKDw");
//TABLE table = top_businesses_by_city(sgr, 10);
//TABLE y = businesses_with_stars_and_city(sgr,4.5,"Columbus");

//printPagina(table);

//TABLE table = international_users(sgr);
//table = fromCSV("input/business_full.csv",";");
//TABLE table = businesses_reviewed(sgr,"GwEUFjgs2WnsRINLEhkViQ");

/*

SGR sgr = load_sgr(NULL,NULL,NULL);
TABLE table = top_businesses_with_category(sgr, 100, "Food");

char * str = strdup("ola");
char * str1 = strdup("mundo");
swap(str,str1);
printf("%s %s\n",str,str1);
show(table);
*/

//top_businesses_by_city(sgr, 10);

//char buffer[1024];
//fgets(buffer, 1024, stdin);
//show(table);
//free_sgr(sgr);    

return r;
}