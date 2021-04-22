#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>
#include "sgr.h"
#include "interpretador.h"


int main(int argc, char *argv[]) {

//interpretador();

//free_sgr(sgr);    
printf("LOADING...\n");
SGR sgr = load_sgr(NULL,NULL,NULL);
printf("FINISHED!\n");
//business_info(sgr,"pCFTvC1v0B9Wilm8XixKDw");
//businesses_reviewed(sgr,"HWzMPRalNgsGEnfBwiSf9Q");
//businesses_with_stars_and_city(sgr,3.0,"Melrose");
//int tmh = g_slist_length(g_hash_table_lookup(sgr->review,"S8pM1QQGTZGgXJZ4MgR8UQ" ));
//printf("Id: %d\n", tmh);//getReviewId( arr->data ));//g_hash_table_lookup(sgr->review,"K9Qs10WdPusc1OVQKc5hbg" )));
    return 0;
}