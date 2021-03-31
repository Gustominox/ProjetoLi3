#include <stdio.h>
#include "dados.h"


int main(){

	
	REVIEW rev = NULL;
    char info[] = "lWC-xP3rd6obsecCYsGZRg;ak0TdVmGKo4pwqdJSTLwWw;buF9druCkbuXLX526sGELQ;4.0;3;1;1";
    rev = addReview(rev,info);
	reviewToString(rev);
	
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
