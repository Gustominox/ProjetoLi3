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


typedef struct review{
	char *review_id;
	char *user_id;
	char *business_id;
	float stars;
	int useful;
	int funny;
	int cool;
	//char *date; ////////////////// char ?????????????????????
	//char *text;
} *REVIEW;
// estou a criar um tipo de dados de review e este review já é um apontador.

char** lerFichCsv (char **info, int* tmh, char path[]);

BUSINESS* transStrToBus(char **info,int tmh,BUSINESS *business);

REVIEW* transStrToRev(char **info,int tmh,REVIEW *review);

USER* transStrToUsers(char **info,int tmh,USER *users);

void addUser (USER user, char info[]);

void addBusiness (BUSINESS bus, char info[]);

REVIEW addReview (REVIEW rev, char info[]);