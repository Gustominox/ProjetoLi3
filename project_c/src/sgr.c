#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>
#include <pthread.h>
#include "sgr.h"
#include "auxiliares.h"

struct sgr{
	
	BUSINESS *bus;
	REVIEW *rev;
	USER *use;

	GHashTable* business;
	GHashTable* businessByCity;
	GHashTable* businessByInicial;
	GHashTable* businessByCategory;

	GHashTable* reviewByText;
	GHashTable* reviewByBusId;
	GHashTable* reviewByUserId;
};

SGR init_sgr(){

	SGR sgr = malloc(sizeof(struct sgr));
	
	sgr->bus = NULL;
	sgr->rev = NULL;
	sgr->use = NULL;


	sgr->business 			= g_hash_table_new(g_str_hash, g_str_equal);
	sgr->businessByCity 	= g_hash_table_new(g_str_hash, g_str_equal);
	sgr->businessByInicial  = g_hash_table_new(g_str_hash, g_str_equal);
	sgr->businessByCategory = g_hash_table_new(g_str_hash, g_str_equal);
	
	sgr->reviewByText 	= g_hash_table_new(g_str_hash, g_str_equal);
	sgr->reviewByBusId 	= g_hash_table_new(g_str_hash, g_str_equal);
	sgr->reviewByUserId = g_hash_table_new(g_str_hash, g_str_equal);
	
	return sgr;
}

// todo: INCOMPLETA
void free_sgr(SGR sgr){
	
	int i = 0;
	while(sgr->bus[i]){
		freeBusiness (sgr->bus[i]);
		i++;
	}
	i = 0;
	while(sgr->rev[i]){
		freeReview (sgr->rev[i]);
		i++;
	}
	i = 0;
	while(sgr->use[i]){
		freeUser (sgr->use[i]);
		i++;
	}

	g_hash_table_destroy(sgr->business);
	g_hash_table_destroy(sgr->businessByCity);
	g_hash_table_destroy(sgr->businessByInicial);
	g_hash_table_destroy(sgr->businessByCategory);

	g_hash_table_destroy(sgr->reviewByText);
	g_hash_table_destroy(sgr->reviewByBusId);
	g_hash_table_destroy(sgr->reviewByUserId);
	
	free(sgr);
}	


void *threadQuery9(void* value){
	
	SGR sgr = (SGR) value;
	printf("LOADING Table Reviews by Words...\nThis may take a while but only occurs once\n\n");
	transStructToTableCate(sgr->reviewByText ,sgr->rev,getReviewWords );
	printf("FINISHED Table Reviews by Words!!!\n\n");
	return NULL;
}


void *threadBusiness(void* value){
	
	SGR sgr = (SGR) value;
	printf("LOADING Table Business...\n");
	transStructToTable(sgr->business,sgr->bus,getBusId);
	printf("FINISHED Table Business.\n\n");

	printf("LOADING Table Business por Cidade...\n");
	transStructToTable(sgr->businessByCity,sgr->bus,getBusCity);
	printf("FINISHED Table Business por Cidade.\n\n");

	printf("LOADING Table Business por letra inicial...\n");
	transStructToTable(sgr->businessByInicial,sgr->bus,getBusNameInicial);
	printf("FINISHED Table Business por letra inicial.\n\n");

	printf("LOADING Table Business por categoria...\n");
	transStructToTableCate(sgr->businessByCategory,sgr->bus,getBusCategories);
	printf("FINISHED Table Business por categoria.\n\n");
	return NULL;
}


void *threadReviews(void* value){
	
	SGR sgr = (SGR) value;
	
	printf("LOADING Table Reviews by User...\n");
	transStructToTable(sgr->reviewByUserId,sgr->rev,getReviewUser);
	printf("FINISHED Table Business by User.\n\n");

	printf("LOADING Table Reviews by Business...\n");
	transStructToTable(sgr->reviewByBusId,sgr->rev,getReviewBus);	
	printf("FINISHED Table Business by Business.\n\n");
	
	return NULL;
}

/** QUERY 1 */

SGR load_sgr(char *fileBus, char *fileReviews, char *fileUsers){
    
	clock_t Ticks[2];
    Ticks[0] = clock();
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
	
	pthread_t thread1,thread2;

	//inicio da thread relativa ao fich com businesses
	pthread_create(&thread1,NULL,threadBusiness,sgr);
	
	//inicio da thread relativa ao fich com reviews
	pthread_create(&thread2,NULL,threadReviews,sgr);
	
    // espera pela thread1
	pthread_join(thread1,NULL);
    // espera pela thread2
	pthread_join(thread2,NULL);
    
	Ticks[1] = clock();
    double time = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
    printf("\nTempo de execucao da QUERY (segundos): %g\n",time);
    
	return sgr;

}
/** QUERY 2 */

TABLE businesses_started_by_letter(SGR sgr, char letter){

	clock_t Ticks[2];
    Ticks[0] = clock();
                
	char str[2] = "\0";// str[] = {'\0','\0'}
    str[0] = toupper(letter);// str[] = {letter,'\0'}
	
	GSList* list =  g_hash_table_lookup(sgr->businessByInicial,str);

	if (list == NULL) {
		printf("BUSINESS WHIT THAT INICIAL LETTER DOES NOT EXIST\n");
		return NULL;
	}

 	int nBus = g_slist_length(list);	
	
	TABLE table = init_table();
	char **linha = init_linha();
	
	//cabecalho
	linha = add_palavra(linha,"BUS ID");
	linha = add_palavra(linha,"NAME");
	linha = add_palavra(linha,"\n");
	add_linha(table,linha);

	while (list) {// enq houver elems na lista
		linha = init_linha();

		linha = add_palavra(linha, getBusId(list->data));
		linha = add_palavra(linha, getBusName(list->data));
		linha = add_palavra(linha, "\n");
		add_linha(table,linha);

		list = g_slist_next(list);
	}
	Ticks[1] = clock();
    double time = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
    printf("\nTempo de execucao da QUERY (segundos): %g\n",time);
                
	return table;
}

/** QUERY 3 */
TABLE business_info(SGR sgr, char *business_id){

	clock_t Ticks[2];
    Ticks[0] = clock();

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

	char **linha = init_linha();
	TABLE table = init_table();
	char buf[15];

	linha = add_palavra(linha,"NAME");
	linha = add_palavra(linha,"CITY");
	linha = add_palavra(linha,"STATE");
	linha = add_palavra(linha,"STARS");								  
	linha = add_palavra(linha,"Num Reviews");
	linha = add_palavra(linha,"\n");	
	add_linha(table,linha);
	
	linha = init_linha();
	linha = add_palavra(linha,getBusName(bus));
	linha = add_palavra(linha,getBusCity(bus));
	linha = add_palavra(linha,getBusState(bus));
	sprintf(buf,"%f",sumStars);
	linha = add_palavra(linha,buf);
	sprintf(buf,"%d",nRev);
	linha = add_palavra(linha,buf);
	linha = add_palavra(linha,"\n");	
	add_linha(table,linha);

	Ticks[1] = clock();
    double time = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
    printf("\nTempo de execucao da QUERY (segundos): %g\n",time);

	return table;
}


/** QUERY 4 */
TABLE businesses_reviewed(SGR sgr, char *user_id){

	clock_t Ticks[2];
    Ticks[0] = clock();

	if (g_hash_table_contains(sgr->reviewByUserId,user_id)){

		GSList* list = g_hash_table_lookup(sgr->reviewByUserId,user_id );
	
		TABLE table = init_table();
		char **linha = init_linha();

		//cabecalho
		linha = add_palavra(linha,"BUS ID");
		linha = add_palavra(linha,"NAME");
		linha = add_palavra(linha,"\n");	
		add_linha(table,linha);

		GSList *list2;

		while (list) {
			list2 =  g_hash_table_lookup(sgr->business,getReviewBus(list->data));
		
			linha = init_linha();

			linha = add_palavra(linha, getBusId(list2->data));
			linha = add_palavra(linha, getBusName(list2->data));
			linha = add_palavra(linha, "\n");
			add_linha(table,linha);

			list = g_slist_next(list);
		}
		Ticks[1] = clock();
		double time = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
    	("\nTempo de execucao da QUERY (segundos): %g\n",time);

		return table;
	}else{
		printf("NAO EXISTE REVIEWS\n");
		return NULL;
	}
}


/** QUERY 5 */
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city){
	
	clock_t Ticks[2];
    Ticks[0] = clock();

	GSList* list = g_hash_table_lookup(sgr->businessByCity,city );

	GSList* list2; 

	TABLE table = init_table();
	char **linha = init_linha();
	char buf[15];

	//cabecalho
	linha = add_palavra(linha,"BUS ID");
	linha = add_palavra(linha,"NAME");
	linha = add_palavra(linha,"STARS");	
	linha = add_palavra(linha,"\n");		
	add_linha(table,linha);

	while (list) {
	

		list2 = g_hash_table_lookup(sgr->reviewByBusId, getBusId( list->data ));

		int nRev = g_slist_length(list2);	

		if (nRev > 0){
			float sumStars = getReviewStars (list2->data);
			while (list2 = g_slist_next(list2)) sumStars +=  getReviewStars (list2->data);
			float nRevF = nRev/1.0;
			sumStars = sumStars/nRevF;

			if(sumStars > stars) {
				linha = init_linha();

				linha = add_palavra(linha, getBusId(list->data));
				linha = add_palavra(linha, getBusName(list->data));
				sprintf(buf,"%f",sumStars);
				linha = add_palavra(linha,buf);
				linha = add_palavra(linha, "\n");
				
				add_linha(table,linha);
			}
		}
		 list = g_slist_next(list);
	}
	Ticks[1] = clock();
    double time = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
    printf("\nTempo de execucao da QUERY (segundos): %g\n",time);

	return table;
}


/** QUERY 6 */
TABLE top_businesses_by_city(SGR sgr, int top){

	clock_t Ticks[2];
    Ticks[0] = clock();

    GSList* list = g_hash_table_get_values(sgr->businessByCity);

	TABLE table = init_table();
	GSList* list2;
	char **linha;
	char buf[15];

    while (list){ // Dentro de uma só cidade

        GSList* head = list->data; // lista de business da cidade iterada

		list2 = g_hash_table_lookup(sgr->reviewByBusId, getReviewBus(head->data)); // reviews de um busioness

        GSList* temp = list2;

		linha = init_linha();
		linha = add_palavra(linha,"CITY: ");
		linha = add_palavra(linha, getBusCity(head->data));
		linha = add_palavra(linha,"\n");
		add_linha(table,linha);
		printLinha(linha);
		linha = init_linha();
		linha = add_palavra(linha,"BUS ID");
		linha = add_palavra(linha,"NAME");
		linha = add_palavra(linha,"STARS");	
		linha = add_palavra(linha,"\n");		
		add_linha(table,linha);

        char ***listBus = NULL; // array que vai guardar os negócios de uma cidade

        int j = 0;
		double sumStars ;
		while(head){ // Iterar negócio a negócio

            int nRev = g_slist_length(temp);	
		    if (nRev > 0){
			    sumStars = getReviewStars (temp->data);
			    while (temp = g_slist_next(temp)) sumStars +=  getReviewStars(temp->data);
			    double nRevF = nRev/1.0;
			    sumStars = sumStars/nRevF;
            }

            listBus = realloc(listBus, sizeof(char**)*(j+1));
			listBus[j] = NULL;

            listBus[j] = realloc(listBus[j], sizeof(char*)*3);

            listBus[j][0] = getBusId(head->data);
            listBus[j][1] = getBusName(head->data);
            sprintf(buf, "%g", sumStars);
            listBus[j][2] = buf;

            // printf("%s %s %s\n", listBus[j][0], listBus[j][1], listBus[j][2]);
            j++;
            head = g_slist_next(head);

        }
        ordenaDecresc(listBus, j);
		int k =0;
        while(k < top && k < j){
            
			linha = init_linha();
			for(int i = 0; i < 3; i++){
				linha = add_palavra(linha,listBus[k][i]);
			}
			linha = add_palavra(linha,"\n");
			add_linha(table, linha);
			k++;
        }
        list = g_slist_next(list);
    }
	Ticks[1] = clock();
    double time = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
    printf("\nTempo de execucao da QUERY (segundos): %g\n",time);

	return table;
}

/** QUERY 7 */
TABLE international_users(SGR sgr){

	clock_t Ticks[2];
    Ticks[0] = clock();

	int nUsers = 0;
	GSList* list = g_hash_table_get_values (sgr->reviewByUserId);
	
	TABLE table = init_table();
	char **linha = init_linha();
	
	//cabecalho
	linha = add_palavra(linha,"USER ID");
	linha = add_palavra(linha,"\n");	
	add_linha(table,linha);

	while (list) {
		int flag=0;
		
		GSList* reviews = list->data ;
		GSList* aux = g_hash_table_lookup(sgr->business,getReviewBus(reviews->data));
		char *state;
		if(aux)	state = getBusState(aux->data);

		while (reviews){
			
			GSList* head = g_hash_table_lookup(sgr->business,getReviewBus(reviews->data));
			if (head) {
				if (strcmp(state,getBusState(head->data))!=0){
					flag = 1;
					break;
				}
			}
			reviews = g_slist_next(reviews);
		}
		GSList* user = list->data ;
		if (flag){
			nUsers++;
			linha = init_linha();
			linha = add_palavra(linha,getReviewUser(user->data));
			linha = add_palavra(linha,"\n");
			add_linha(table,linha);

		} 

 		list = g_slist_next(list);
	}
	Ticks[1] = clock();
    double time = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
    printf("\nTempo de execucao da QUERY (segundos): %g\n",time);

	return table;
}


/** QUERY 8 */
TABLE top_businesses_with_category(SGR sgr, int top, char *category){  

	clock_t Ticks[2];
    Ticks[0] = clock();

    GSList* list =  g_hash_table_lookup(sgr->businessByCategory, category);
    // list de negocios que tem na categoria

    if (list == NULL) {
    printf("CATEGORY DOES NOT EXIST\n");    
    return NULL;
    }
    

    TABLE table = init_table();
    char **linha = init_linha();
    

    //cabecalho
    linha = add_palavra(linha,"BUS ID");
    linha = add_palavra(linha,"NAME");
    linha = add_palavra(linha,"STARS");    
    linha = add_palavra(linha,"\n");        
    add_linha(table,linha);

    char ***listBus = NULL;
    int j = 0;
    while(list){ // Iterar de negócio em negócio da categoria dada como arg
        GSList* temp = g_hash_table_lookup(sgr->reviewByBusId, getBusId(list->data));
        // list de reviews do negocio atual
        
        int nRev = g_slist_length(temp);
        float sumStars = 0.0;
        if (nRev > 0){    // as stars médias do negocio
            sumStars = getReviewStars(temp->data);
            while (temp = g_slist_next(temp)) sumStars +=  getReviewStars(temp->data);
            float nRevF = nRev/1.0;
            sumStars = sumStars/nRevF;
        }

        listBus = realloc(listBus, sizeof(char**)*(j+1));
        listBus[j] = NULL;

        listBus[j] = realloc(listBus[j], sizeof(char*)*3);

        listBus[j][0] = getBusId(list->data);
        listBus[j][1] = getBusName(list->data);
		
		char buf[15];
        sprintf(buf, "%f", sumStars);
        listBus[j][2] = strdup(buf);
		
        j++;
		
        list = g_slist_next(list);
    }

    ordenaDecresc(listBus, j);
	
	
	
    int k = 0;
    while(k < top && k < j){

        linha = init_linha();
        for(int i = 0; i < 3; i++){
            linha = add_palavra(linha, listBus[k][i]);
        }
        linha = add_palavra(linha, "\n");
        add_linha(table, linha);
        k++;
    }
	Ticks[1] = clock();
    double time = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
    printf("\nTempo de execucao da QUERY (segundos): %g\n",time);

    return table;
}


/** QUERY 9 */
TABLE reviews_with_word(SGR sgr, int top, char *word){

	
	GSList* list =  g_hash_table_lookup(sgr->reviewByText, word);
    
	if (list == NULL) {
		printf("WORD DOES NOT EXIST\n");
		return NULL;
	}

	TABLE table = init_table();
	char **linha = init_linha();
	
	//cabecalho
	linha = add_palavra(linha,"REVIEW ID");
	linha = add_palavra(linha,"\n");	
	add_linha(table,linha);
	
	while (list){
		linha = init_linha();
		
		linha = add_palavra(linha, getReviewId(list->data));
		linha = add_palavra(linha, "\n");	
		
		add_linha(table,linha);
		

		list = g_slist_next(list);
	}
	
	return table;
}