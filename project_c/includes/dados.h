#include <stdio.h>
#include <stdlib.h>

/*
typedef struct cidade{
	char **referencias;
} *CIDADE; 
*/
typedef struct business{
	char *business_id;
	char *name;
	char *city;
	float state;
	int categories;
} *BUSINESS; 
// estou a criar um tipo de dados de business e este business já é um apontador.


typedef struct user{
	char *id;
	char *name;
	char *friends;
} *USER;
// estou a criar um tipo de dados de user e este user já é um apontador.


typedef struct reviews{
	char *review_id;
	char *user_id;
	char *business_id;
	float stars;
	int useful;
	int funny;
	int cool;
	//char *date; ////////////////// char ?????????????????????
	//char *text;
} *REVIEWS;
// estou a criar um tipo de dados de reviews e este reviews já é um apontador.

char** lerFichCsv (char **info, int* tmh, char path[]);

BUSINESS* transStrToBus(char **info,int tmh,BUSINESS *business);

REVIEWS* transStrToRev(char **info,int tmh,REVIEWS *reviews);

USER* transStrToUsers(char **info,int tmh,USER *users);

void addUser (USER user, char info[]);

void addBusiness (BUSINESS bus, char info[]);

REVIEWS addReviews (REVIEWS rev, char info[]);