#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "dados.h"
#include "sgr.h"



SGR init_sgr(){

	SGR sgr = malloc(sizeof(SGR));
	sgr->business = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->review = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->user = g_hash_table_new(g_str_hash, g_str_equal);
	
	return sgr;
}

SGR load_sgr(char *users, char *businesses, char *reviews){
    SGR sgr = init_sgr();
	
	//DEFAULT VALUES DE FICH INPUT
	if (business == NULL) strcpy (businesses,"input/business_full.csv");
	
	if (reviews == NULL) strcpy (reviews,"input/reviews_1M.csv");
	
	if (users == NULL) strcpy (users,"input/users_full.csv");
	
	//LER OS FICH E CRIAR AS TABELAS DE HASH
	char **infoBusinesses = lerFichCsv(info,&tmh,businesses);
	transStrToTable(infoBusinesses,sgr->business,addBusiness);

	char **infoReviews = lerFichCsv(info,&tmh,reviews);
	transStrToTable(infoReviews,sgr->review,addReview);

	char **infoUsers = lerFichCsv(info,&tmh,users);
	transStrToTable(infoUsers,sgr->user,addUser);

	return sgr;
}


void free_sgr(SGR sgr){

	g_hash_table_destroy(sgr->business);
	g_hash_table_destroy(sgr->review);
	g_hash_table_destroy(sgr->user;
	
	free(sgr);
	}