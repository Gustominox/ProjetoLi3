#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>
#include "sgr.h"
#include "interpretador.h"

BUSINESS* transStrToBus(char **info,int *tmh,BUSINESS *business){

    int tmhBus = 0;
    for (int i = 0; info[i]; i++){
        business = realloc(business,sizeof(BUSINESS)*(tmhBus+1));
        business[tmhBus] = addBusiness( info[i]);
        if(business[tmhBus] == NULL) {
            free(business[tmhBus]);
            tmhBus--; 
        }
        tmhBus++;
        printf("[%d]\n", tmhBus);
        //printf("%s\n",businessToString(business[tmhBus-1]));

    }
    
    for (int j = 0; j < *tmh; j++)
        free (info[j]);

    *tmh = tmhBus;
    return business; 
}

int main(int argc, char *argv[]) {
int tmh;
char **info;
info = lerFichCsv(&tmh,"input/business_full.csv");
//interpretador();

//free_sgr(sgr);    
//printf("LOADING...\n");
//SGR sgr = load_sgr(NULL,NULL,NULL);
//printf("FINISHED!\n");
//business_info(sgr,"pCFTvC1v0B9Wilm8XixKDw");
//businesses_reviewed(sgr,"HWzMPRalNgsGEnfBwiSf9Q");
//businesses_with_stars_and_city(sgr,3.0,"Melrose");
//int tmh = g_slist_length(g_hash_table_lookup(sgr->review,"S8pM1QQGTZGgXJZ4MgR8UQ" ));
//printf("Id: %d\n", tmh);//getReviewId( arr->data ));//g_hash_table_lookup(sgr->review,"K9Qs10WdPusc1OVQKc5hbg" )));
    return 0;
}