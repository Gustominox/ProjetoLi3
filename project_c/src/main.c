#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

	char **info = NULL;
	BUSINESS *business = NULL;
	//USER *user = NULL;
	int tmh ;
//	info = lerFichCsv(info,&tmh,"input/users_full.csv");
//	user = transStrToUsers(info,tmh,user);
	
	info = lerFichCsv(info,&tmh,"input/business_full.csv");
	//business = transStrToBus(info,&tmh,business);

    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
	BUSINESS bus = addBusiness(info[0]);

    g_hash_table_insert(hash,"gusto",bus);
    g_hash_table_insert(hash,"Mr Darcy","Treats");

    printf("There are %d keys in the hash table\n",
        g_hash_table_size(hash));

    printf("Jazzy likes %s\n",businessToString( g_hash_table_lookup(hash,"gusto" )));

	//for (int j = 0; j < tmh; j++)
    // 		free (business[j]);
    g_hash_table_destroy(hash);
    return 0;
}
/*
int main(){


	BUSINESS bus = NULL;
    char info[] = "zYMjNc-Q7-T238SHylKgKA;Chinatown Restaurant & Lucky Bistro;Tigard;3.5;44";
    bus = addBusiness(bus,info);
	if(bus)
    printf("%s", bus->business_id);	
	
	
	hash paula henriques -> Qrb
	aaa
	aab
	abb- > k«jioa fran sjn sjhds
	Qrb -> gusto, filipa, paula henriques
	yyy
	zzz
	ZZZ
addHash(table ,hash )
procHash(table,hash)

	//reviewToString(rev);
	
	
	char **info = NULL;
	//BUSINESS *business = NULL;
	USER *user = NULL;
	int tmh ;
	info = lerFichCsv(info,&tmh,"input/users_full.csv");
	user = transStrToUsers(info,tmh,user);
	
	info = lerFichCsv(info,&tmh,"input/business_full.csv");
	business = transStrToUsers(info,tmh,business);
	

	//for (int j = 0; j < tmh; j++)
   //   		free (business[j]);

return 0;

}
*/
