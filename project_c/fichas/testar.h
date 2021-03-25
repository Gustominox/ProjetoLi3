#include <stdio.h>
#include <stdlib.h>

typedef struct business{
	char *business_id;
	char *name;
	char *city;
	float stars;
	int review_count;
} *BUSINESS; 
// estou a criar um tipo de dados de business e este business já é um apontador.


typedef struct user{
	char *id;
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
} *REVIEWS;
// estou a criar um tipo de dados de reviews e este reviews já é um apontador.

/*
typedef struct city{
	char *name;
} *CITY;
*/