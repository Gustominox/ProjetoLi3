#include <stdio.h>
#include "dados.h"


int main(){

/*	
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
*/
	//reviewToString(rev);
	
	
	char **info = NULL;
	//BUSINESS *business = NULL;
	USER *user = NULL;
	int tmh ;
	info = lerFichCsv(info,&tmh,"input/users_full.csv");
	user = transStrToUsers(info,tmh,user);
	/*
	info = lerFichCsv(info,&tmh,"input/business_full.csv");
	business = transStrToUsers(info,tmh,business);
	*/

	//for (int j = 0; j < tmh; j++)
   //   		free (business[j]);

return 0;

}

