#include <stdio.h>
#include "dados.h"


int main(){
	char **users;
	users = NULL;
	int tmh = lerFichCsv(users,"users.csv");
	for (int j = 0; j < tmh; j++)
      		printf("%s\n", users[j]);	
	for (int j = 0; j < tmh; j++)
      		free (users[j]);
}
