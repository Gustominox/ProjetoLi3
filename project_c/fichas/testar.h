#include <stdio.h>
#include <stdlib.h>

typedef struct business{
	char *id;
	char *name;
	float stars;
	int nr_ratings;
} *BUSINESS; 
// estou a criar um tipo de dados de business e este business já é um apontador.


typedef struct user{
	char *id;
} *USER;
// estou a criar um tipo de dados de user e este user já é um apontador.

typedef struct reviews{
	char *id1;
	char *id2;
	char *id3;
	float stars;
	int rev1;
	int rev2;
	int rev3;
} *REVIEWS;
// estou a criar um tipo de dados de reviews e este reviews já é um apontador.