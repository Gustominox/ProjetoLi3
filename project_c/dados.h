#include <stdio.h>
#include <stdlib.h>


typedef struct business{
	char *business_id;
	char *name;
	char *city;
	char *state;
	char *categories;
} *Business; 
// estou a criar um tipo de dados de business e este business já é um apontador.


typedef struct user{
	char *id;
	char *name;
	char *friends;
} *User;
// estou a criar um tipo de dados de user e este user já é um apontador.


typedef struct reviews{
	char *review_id;
	char *user_id;
	char *business_id;
	float stars;
	int useful;
	int funny;
	int cool;
	char *date; ////////////////// char ?????????????????????
	char *text;
} *Reviews;
// estou a criar um tipo de dados de reviews e este reviews já é um apontador.
