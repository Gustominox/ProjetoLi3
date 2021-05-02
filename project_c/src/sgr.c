#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "sgr.h"
#include <pthread.h>

struct sgr{
	
	BUSINESS *bus;
	REVIEW *rev;
	USER *use;
	GHashTable* business;
	GHashTable* businessByCity;
	GHashTable* businessByInicial;
	GHashTable* review;
	GHashTable* reviewByBusId;
	GHashTable* reviewByUserId;
	GHashTable* user;
};

SGR init_sgr(){

	SGR sgr = malloc(sizeof(struct sgr));
	
	sgr->bus  = NULL;
	sgr->rev  = NULL;
	sgr->use = NULL;


	sgr->business = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->businessByCity = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->businessByInicial = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->review = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->reviewByBusId = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->reviewByUserId = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->user = g_hash_table_new(g_str_hash, g_str_equal);
	
	return sgr;
}

// todo: INCOMPLETA
void free_sgr(SGR sgr){

	freeBusiness (sgr->bus[0]);
	g_hash_table_destroy(sgr->business);
	g_hash_table_destroy(sgr->businessByCity);
	g_hash_table_destroy(sgr->businessByInicial);
	g_hash_table_destroy(sgr->review);
	g_hash_table_destroy(sgr->reviewByBusId);
	g_hash_table_destroy(sgr->reviewByUserId);
	g_hash_table_destroy(sgr->user);
	
	free(sgr);
}	


void *threadUsers(void* value){
	
	SGR sgr = (SGR) value;
	transStructToTable(sgr->user,sgr->use,getUserId);

	return NULL;
}


void *threadBusiness(void* value){
	
	SGR sgr = (SGR) value;
	
	transStructToTable(sgr->business,sgr->bus,getBusId);

	transStructToTable(sgr->businessByCity,sgr->bus,getBusCity);

	transStructToTable(sgr->businessByInicial,sgr->bus,getBusNameInicial);


	return NULL;
}


void *threadReviews(void* value){
	
	SGR sgr = (SGR) value;
	
	transStructToTable(sgr->review,sgr->rev,getReviewId);

	transStructToTable(sgr->reviewByUserId,sgr->rev,getReviewUser);

	transStructToTable(sgr->reviewByBusId,sgr->rev,getReviewBus);

	return NULL;
}

/** QUERY 1 */

SGR load_sgr(char *fileBus, char *fileReviews, char *fileUsers){
    // init struct sgr
	SGR sgr = init_sgr();
	
	//DEFAULT VALUES DE FICH INPUT
	if (fileBus == NULL) fileBus = strdup("input/business_full.csv"); 

	if (fileReviews == NULL) fileReviews = strdup("input/reviews_1M.csv"); 
	
	if (fileUsers == NULL) fileUsers = strdup("input/users_full.csv"); 
	
	//LER OS FICH E CRIAR AS TABELAS DE HASH
	
	
	int tmh;
	char **info;

	info = lerFichCsv(&tmh,fileBus);
	sgr->bus = transStrToBus(info,&tmh,sgr->bus);
	
	info = lerFichCsv(&tmh,fileReviews);
	sgr->rev = transStrToRev(info,&tmh,sgr->rev);
	
	
	info = lerFichCsv(&tmh,fileUsers);
	sgr->use = transStrToUsers(info,&tmh,sgr->use);
	
	pthread_t thread1,thread2,thread3;

	//inicio da thread relativa ao fich com users
	pthread_create(&thread1,NULL,threadUsers,sgr);
	
	//inicio da thread relativa ao fich com businesses
	pthread_create(&thread2,NULL,threadBusiness,sgr);
	
	//inicio da thread relativa ao fich com reviews
	pthread_create(&thread3,NULL,threadReviews,sgr);
	
    // espera pela thread1
	pthread_join(thread1,NULL);
    // espera pela thread2
	pthread_join(thread2,NULL);
    // espera pela thread3
	pthread_join(thread3,NULL);
	
	// *DEBUG*
	//
	printf("There are %d keys in the hash table\n",
        g_hash_table_size(sgr->businessByInicial));
	//
	//printf("There are %d keys in the hash table\n",
    //    g_hash_table_size(sgr->review));
	//
	//printf("There are %d keys in the hash table\n",
    //    g_hash_table_size(sgr->reviewByBusId));
	//
	//printf("There are %d keys in the hash table\n",
    //    g_hash_table_size(sgr->user));

	return sgr;

}
/** QUERY 2 
 * 
 * Determinar a lista de nomes de negócios e o número total de negócios cujo 
 * nome inicia por uma dada letra. Note que a procura não deverá ser case sensitive
 * 
*/

TABLE businesses_started_by_letter(SGR sgr, char letter){

	
	char str[2] = "\0";
    str[0] = toupper(letter);

	GSList* list =  g_hash_table_lookup(sgr->businessByInicial,str);

	printf("There are %d keys in the hash table\n",
        g_hash_table_size(sgr->businessByInicial));

	if (list == NULL) {
		printf("BUSINESS WHIT THAT INICIAL LETTER DOES NOT EXIST\n");
		return NULL;
	}

 	int nBus = g_slist_length(list);	

	//printf("%s %s\n", getBusId(list->data),getBusName(list->data));
	while (list = g_slist_next(list)) {
	printf("%s %s\n", getBusId(list->data),getBusName(list->data));	
	}

}

/** QUERY 3 */
TABLE business_info(SGR sgr, char *business_id){

	GSList* list =  g_hash_table_lookup(sgr->business,business_id);
	if (list == NULL) {
		printf("BUSINESS DOES NOT EXIST\n");
		return NULL;
	}
	BUSINESS bus = list->data;

	list = g_hash_table_lookup(sgr->reviewByBusId,business_id );

	int nRev = g_slist_length(list);	
	float sumStars = 0;
	if (nRev > 0){
		sumStars = getReviewStars (list->data);
		while (list = g_slist_next(list)) sumStars +=  getReviewStars (list->data);
	
		float nRevF = nRev/1.0;
		sumStars = sumStars/nRevF;
	}
	//printf("LETRA: %d\n\n",getBusNameInicial(bus));
	printf("NAME: %s\n", getBusName(bus));
	printf("CITY: %s\n", getBusCity(bus));
	printf("STATE: %s\n", getBusState(bus));
	printf("STARS: %f\n", sumStars);
	
	printf("nRev: %d\n", nRev);											  
}


/** QUERY 4 */
TABLE businesses_reviewed(SGR sgr, char *user_id){


	if (g_hash_table_contains(sgr->reviewByUserId,user_id)){
		printf("EXISTE\n");

		GSList* list = g_hash_table_lookup(sgr->reviewByUserId,user_id );
		printf("%s",getReviewUser(list->data));




		GSList* list2 =  g_hash_table_lookup(sgr->business,getReviewBus(list->data));

		printf("%s %s\n", getBusId(list2->data),getBusName(list2->data));
		while (list = g_slist_next(list)) {
		
			list2 =  g_hash_table_lookup(sgr->business,getReviewBus(list->data));
			printf("%s %s\n", getBusId(list2->data),getBusName(list2->data));
		}

	}else{
		printf("NAO EXISTE\n");
	}
}


/** QUERY 5 */
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city){
	
	//printf("\n\n\n\n\n");
	GSList* list = g_hash_table_lookup(sgr->businessByCity,city );

	//printf("%s\n", getBusId( list->data ));
	GSList* list2 = g_hash_table_lookup(sgr->reviewByBusId, getBusId( list->data ));

	int nRev = g_slist_length(list2);	
	if (nRev > 0){
		printf("nRev: %d\n", nRev);
		float sumStars = getReviewStars (list2->data);
		while (list2 = g_slist_next(list2)) sumStars +=  getReviewStars (list->data);
		float nRevF = nRev/1.0;
		sumStars = sumStars/nRevF;

		if(sumStars > stars) printf("%s %s %f\n", getBusId(list->data),getBusName(list->data),sumStars);
		
	}
	while (list = g_slist_next(list)) {
	

		list2 = g_hash_table_lookup(sgr->reviewByBusId, getBusId( list->data ));

		int nRev = g_slist_length(list2);	

		if (nRev > 0){
			float sumStars = getReviewStars (list2->data);
			while (list2 = g_slist_next(list2)) sumStars +=  getReviewStars (list2->data);
			float nRevF = nRev/1.0;
			sumStars = sumStars/nRevF;

			if(sumStars > stars) printf("%s %s %f\n", getBusId(list->data),getBusName(list->data),sumStars);
		}
	}
}


/** query 7 
 * \brief  Determinar a lista de ids de utilizadores e o número total de utilizadores que tenham visitado mais de um estado
 * @param sgr sgr
*/
TABLE international_users(SGR sgr){

	GSList* list = g_hash_table_get_values (sgr->reviewByUserId);
	
	while (list) {
		int flag=0;
		GSList* reviews = list->data ;
		while (reviews)
		{
			
			printf("Business: %s\n",getReviewBus(reviews->data));
			
			reviews = g_slist_next(reviews);
		}
		

 		list = g_slist_next(list);
	}

}



