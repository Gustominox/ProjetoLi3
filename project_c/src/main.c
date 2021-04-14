#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>
#include "sgr.h"

int main(int argc, char *argv[]) {

	char **info = NULL;

	print_uppercase_words("x = businesses_started_by_letter(sgr, 'T');");
	
	print_uppercase_words("toCSV(x,';',\"tascos.txt\");");
	
	int tmh ;


	char path[] = "input/users_full.csv";
 
	info = lerFichCsv(&tmh,path);
	
	//SGR sgr = init_sgr();	
    //GHashTable* hash = sgr->business;
	GHashTable* business = g_hash_table_new(g_str_hash, g_str_equal);
	


	transStrToTable(info,business,addUser);

    printf("There are %d keys in the hash table\n",
        g_hash_table_size(business));

    printf("BUSID: %s\n", getBusId( g_hash_table_lookup(business,"rYs_1pNB_RMtn5WQh55QDA" )));
    printf("STATE: %s\n",getState( g_hash_table_lookup(business,"HPA_qyMEddpAEtFof02ixg" )));

	g_hash_table_destroy(business);
    return 0;
}