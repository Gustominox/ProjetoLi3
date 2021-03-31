#include <stdio.h>
#include "dados.h"


int main(){

	
	BUSINESS bus = NULL;
    char info[] = "zYMjNc-Q7-T238SHylKgKA;Chinatown Restaurant & Lucky Bistro;Tigard;3.5;44";
    bus = addBusiness(bus,info);
	if(bus)
    printf("%s", bus->business_id);	
	//reviewToString(rev);
	
	/*
	char **info = NULL;
	BUSINESS *business;
	int tmh ;
	info = lerFichCsv(info,&tmh,"business.csv");
	business = transStrToBus(info,tmh,business);
	for (int j = 0; j < tmh; j++)
      		printf("%s", business[j]->business_id);	
	for (int j = 0; j < tmh; j++)
      		free (business[j]);
*/
return 0;

}
