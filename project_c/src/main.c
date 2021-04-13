#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	char **info = NULL;

	int "var";
	
	int tmh ;


	
 
	info = lerFichCsv(info,&tmh,"input/business_full.csv");
	

    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
	//transStrToTable(info,hash,addBusiness);

 //   printf("There are %d keys in the hash table\n",
   //     g_hash_table_size(hash));

    printf("BUSID: %s\n", getBusId( g_hash_table_lookup(hash,"rYs_1pNB_RMtn5WQh55QDA" )));
    printf("STATE: %s\n",getState( g_hash_table_lookup(hash,"hCABMnKtwo4Y9alQDxh2kw" )));

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
