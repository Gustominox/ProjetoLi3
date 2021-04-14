#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "dados.h"
#include "sgr.h"



SGR init_sgr(){

	SGR sgr = malloc(sizeof(SGR));
	sgr->business = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->review = g_hash_table_new_full(g_str_hash, g_str_equal,NULL,NULL);
	sgr->user = g_hash_table_new(g_str_hash, g_str_equal);
	
	return sgr;
}


void free_sgr(SGR sgr){

	g_hash_table_destroy(sgr->business);
	g_hash_table_destroy(sgr->review);
	g_hash_table_destroy(sgr->user);
	
	free(sgr);
}



SGR load_sgr(char *fileBus, char *fileReviews, char *fileUsers){
    // init struct sgr
	SGR sgr = init_sgr();
	
	//DEFAULT VALUES DE FICH INPUT
	//printf("FILE: %s\n",fileBus);
	if (fileBus == NULL) fileBus = strdup("input/business_full.csv"); // strcpy (fileBus,"input/business_full.csv");
	//printf("FILE: %d\n",(fileBus == NULL));
	if (fileReviews == NULL) fileReviews = strdup("input/reviews_1M.csv"); //strcpy (fileReviews,"input/reviews_1M.csv");
	
	if (fileUsers == NULL) fileUsers = strdup("input/users_full.csv"); // strcpy (fileUsers,"input/users_full.csv");
	


	//LER OS FICH E CRIAR AS TABELAS DE HASH

	//transStrToTable(fileBus,sgr->business,addBusiness,0);
	
	transStrToTable(fileReviews,sgr->review,addReview,2);

	//transStrToTable(fileUsers,sgr->user,addUser,0);
	
	printf("There are %d keys in the hash table\n",
        g_hash_table_size(sgr->business));

	printf("There are %d keys in the hash table\n",
        g_hash_table_size(sgr->review));

	printf("There are %d keys in the hash table\n",
        g_hash_table_size(sgr->user));
	return sgr;

}
/* 	QUERY 3
	Dado um id de negócio, determinar a sua informação:
 	nome, cidade, estado, stars, e número total reviews.
 
 ******/ 

TABLE business_info(SGR sgr, char *business_id){

}

