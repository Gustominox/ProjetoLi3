#include <stdio.h>
#include <stdlib.h>

/*
typedef struct cidade{
	char **referencias;
} *CIDADE; 
*/
typedef struct business *BUSINESS; 
// estou a criar um tipo de dados de business e este business já é um apontador.


typedef struct user *USER;
// estou a criar um tipo de dados de user e este user já é um apontador.

typedef struct reviews *REVIEWS;
// estou a criar um tipo de dados de reviews e este reviews já é um apontador.

char** lerFichCsv (char **info, int* tmh, char path[]);

BUSINESS* transStrToBus(char **info,BUSINESS *business);

REVIEWS* transStrToRev(char **info,REVIEWS *reviews);

USER* transStrToUsers(char **info,USER *users);

void addUser (USER user, char info[]);

void addBusiness (BUSINESS bus, char info[]);

void addReviews (REVIEWS rev, char info[]);