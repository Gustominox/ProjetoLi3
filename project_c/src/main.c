#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>
#include "sgr.h"
#include "paginacao.h"
#include <ctype.h>
#include "auxiliares.h"

int main(int argc, char *argv[]) {

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


//interpretador();

//printf("LOADING...\n");


SGR sgr = load_sgr(NULL,NULL,NULL);

//printf("FINISHED!\n");

//TABLE table = business_info(sgr,"pCFTvC1v0B9Wilm8XixKDw");

//TABLE table = businesses_started_by_letter(sgr, '4');
//TABLE table= businesses_with_stars_and_city(sgr,3.0,"Melrose");
//printPagina(table);

//TABLE table = international_users(sgr);
//table = fromCSV("input/business_full.csv",";");
//TABLE table = businesses_reviewed(sgr,"GwEUFjgs2WnsRINLEhkViQ");

//printPagina(table);
//top_businesses_by_city(sgr, 10);

//char buffer[1024];
//fgets(buffer, 1024, stdin);
//show(table);
//free_sgr(sgr);    

    return 0;
}