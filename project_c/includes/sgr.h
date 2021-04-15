#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "paginacao.h"
// #include <glib-2.0/glib.h>

/*!
* @typedef GHashTable
*/
// typedef char *TABLE;


/*!
* @typedef sgr
*
* @field   user        Utilizador
* @field   business    Negócio
* @field   review      Review
*/
typedef struct sgr{
	GHashTable* business;
	GHashTable* businessByCity;
	GHashTable* review;
	GHashTable* reviewByBusid;
	GHashTable* user;
} *SGR;

typedef struct sthread{

	char *file;
	SGR sgr;
	void* (*funcao) (char info[]);
}*STHREAD;



SGR init_sgr();

void free_sgr(SGR sgr);
/* query 1 */
SGR load_sgr(char *users, char *businesses, char *reviews);
/* query 2 */
TABLE businesses_started_by_letter(SGR sgr, char letter);
/* 	QUERY 3
	Dado um id de negócio, determinar a sua informação:
 	nome, cidade, estado, stars, e número total reviews.
 
 ******/
TABLE business_info(SGR sgr, char *business_id);
/* query 4 */
TABLE businesses_reviewed(SGR sgr, char *user_id);
/* query 5 */
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city);
/* query 6 */
TABLE top_businesses_by_city(SGR sgr, int top);
/* query 7 */
TABLE international_users(SGR sgr);
/* query 8 */
TABLE top_businesses_with_category(SGR sgr, int top, char *category);
/* query 9 */
TABLE reviews_with_word(SGR sgr, int top, char *word);
