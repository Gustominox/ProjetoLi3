#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "dados.h"
#include "sgr.h"
#include <pthread.h>


SGR init_sgr(){

	SGR sgr = malloc(sizeof(struct sgr));
	sgr->business = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->businessByCity = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->review = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->reviewByBusid = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->user = g_hash_table_new(g_str_hash, g_str_equal);
	
	return sgr;
}


void free_sgr(SGR sgr){

	g_hash_table_destroy(sgr->business);
	g_hash_table_destroy(sgr->businessByCity);
	g_hash_table_destroy(sgr->review);
	g_hash_table_destroy(sgr->reviewByBusid);
	g_hash_table_destroy(sgr->user);
	
	free(sgr);
}	


void *threadUsers(void* value){
	
	STHREAD help = (STHREAD) value;
	transStrToTable(help->file,help->sgr->user,help->funcao,0);

	return NULL;
}

void *threadBusiness(void* value){
	
	STHREAD help = (STHREAD) value;
	
	transStrToTable(help->file,help->sgr->business,help->funcao,0);
	
	transStrToTable(help->file,help->sgr->businessByCity,help->funcao,2);

	return NULL;
}

void *threadReviews(void* value){
	
	STHREAD help = (STHREAD) value;
	
	transStrToTable(help->file,help->sgr->review,help->funcao,0);
	
	transStrToTable(help->file,help->sgr->reviewByBusid,help->funcao,2);

	return NULL;
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

	STHREAD helpUsers = malloc(sizeof(struct sthread));
	helpUsers->file =fileUsers;
	helpUsers->sgr = sgr;
	helpUsers->funcao = addUser;


	STHREAD helpBusiness = malloc(sizeof(struct sthread));
	helpBusiness->file =fileBus;
	helpBusiness->sgr = sgr;
	helpBusiness->funcao = addBusiness;

	STHREAD helpReviews = malloc(sizeof(struct sthread));
	helpReviews->file =fileReviews;
	helpReviews->sgr = sgr;
	helpReviews->funcao = addReview;	
	//LER OS FICH E CRIAR AS TABELAS DE HASH

	pthread_t thread1,thread2,thread3;


	pthread_create(&thread1,NULL,threadUsers,helpUsers);
	
	//help->file = fileBus;
	//help->sgr = sgr;
	//help->funcao = addBusiness;
//	help->mode = 0;

	pthread_create(&thread3,NULL,threadReviews,helpReviews);

	pthread_create(&thread2,NULL,threadBusiness,helpBusiness);



	

	//transStrToTable(fileUsers,sgr->user,help->funcao,0);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	/*
	printf("There are %d keys in the hash table\n",
        g_hash_table_size(sgr->business));

	printf("There are %d keys in the hash table\n",
        g_hash_table_size(sgr->review));

	printf("There are %d keys in the hash table\n",
        g_hash_table_size(sgr->reviewByBusid));
*/
	//printf("There are %d keys in the hash table\n",
      //  g_hash_table_size(sgr->user));
	return sgr;

}
/* 	QUERY 3
	Dado um id de negócio, determinar a sua informação:
 	nome, cidade, estado, stars, e número total reviews.
 
 ******/ 


TABLE business_info(SGR sgr, char *business_id){

	GSList* list =  g_hash_table_lookup(sgr->business,business_id);

	BUSINESS bus = list->data;

	list = g_hash_table_lookup(sgr->reviewByBusid,business_id );

	int nRev = g_slist_length(list);	
	
	float sumStars = getReviewStars (list->data);
	while (list = g_slist_next(list)) sumStars +=  getReviewStars (list->data);
	
	float nRevF = nRev/1.0;
	sumStars = sumStars/nRevF;
	printf("NAME: %s\n", getBusName(bus));
	printf("CITY: %s\n", getBusCity(bus));
	printf("STATE: %s\n", getBusState(bus));
	printf("STARS: %f\n", sumStars);
	
	printf("nRev: %d\n", nRev);											  
}

