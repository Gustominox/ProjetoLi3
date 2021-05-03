#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>
#include "sgr.h"
#include "interpretador.h"
#include "paginacao.h"
#include <ctype.h>

int main(int argc, char *argv[]) {

/*
char linha[1024];

int tmh;
char **info;
info = lerFichCsv(&tmh,"input/users_full.csv");
printf("Espera\n");
fgets(linha, 1024, stdin);
USER *bus = NULL;
bus = transStrToUsers(info,&tmh,bus);

//printf("%s\n",info[0]);
GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
GHashTable* hash1 = g_hash_table_new(g_str_hash, g_str_equal);
GHashTable* hash2 = g_hash_table_new(g_str_hash, g_str_equal);

transStructToTable(hash,bus,getUserId);
transStructToTable(hash1,bus,getUserId);
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
/*
int *id ;
*id=65;
GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
g_hash_table_insert(hash,'A',"head");
printf ("%s\n",g_hash_table_lookup(hash,id));
*/


SGR sgr = init_sgr();
sgr = load_sgr(NULL,NULL,NULL);
//printf("FINISHED!\n");

//TABLE table = business_info(sgr,"pCFTvC1v0B9Wilm8XixKDw");

TABLE table = businesses_started_by_letter(sgr, '4');
//international_users(sgr);
char buffer[1024];
fgets(buffer, 1024, stdin);
//businesses_reviewed(sgr,"HWzMPRalNgsGEnfBwiSf9Q");
//businesses_with_stars_and_city(sgr,3.0,"Melrose");
//show(table);
free_sgr(sgr);    

    return 0;
}