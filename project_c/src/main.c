#include <stdio.h>
#include "dados.h"


int main(){

	
	REVIEWS rev = malloc(sizeof(struct reviews));
    char info[] = "cCsTIh3GrDnCwP5hLbFrGg;5fydAR8d7Umj2gh0uWyklg;HXYJIJ7lDhOUjaOvjVpZTw;5.0;4;3;1";
    addReviews(rev,info);
	printf("%s\n",rev->review_id);
	
	
	char **info = NULL;
	int tmh ;
	info = lerFichCsv(users,&tmh,"users.csv");
	for (int j = 0; j < tmh; j++)
      		printf("%s", users[j]);	
	for (int j = 0; j < tmh; j++)
      		free (users[j]);

return 0;

}
