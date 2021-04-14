#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>
#include "sgr.h"

int main(int argc, char *argv[]) {

SGR sgr = load_sgr(NULL,NULL,NULL);

business_info(sgr,"S8pM1QQGTZGgXJZ4MgR8UQ");
//int tmh = g_slist_length(g_hash_table_lookup(sgr->review,"S8pM1QQGTZGgXJZ4MgR8UQ" ));
//printf("Id: %d\n", tmh);//getReviewId( arr->data ));//g_hash_table_lookup(sgr->review,"K9Qs10WdPusc1OVQKc5hbg" )));

/*

arr = realloc(arr,sizeof(REVIEW) * 2);	
arr[1] = g_hash_table_lookup(sgr->review,"qIiRyyR9vk9LffiTrMDXwQ" );
printf("Id: %s\n", getReviewId( arr[0]));//g_hash_table_lookup(sgr->review,"K9Qs10WdPusc1OVQKc5hbg" )));
printf("Id: %s\n", getReviewId( arr[1]));//g_hash_table_lookup(sgr->review,"K9Qs10WdPusc1OVQKc5hbg" )));
*/
free_sgr(sgr);    

/*
	char **info = NULL;

	print_uppercase_words("x = businesses_started_by_letter(sgr, 'T');");
	
	print_uppercase_words("toCSV(x,';',\"tascos.txt\");");
	
	int tmh ;


	char path[] = "input/reviews_1M.csv";
 
	//info = lerFichCsv(&tmh,path);
	
		
    //GHashTable* hash = sgr->business;
	GHashTable* business = g_hash_table_new(g_str_hash, g_str_equal);
	


	transStrToTable(path,business,addReview);

    printf("There are %d keys in the hash table\n",
        g_hash_table_size(business));

    printf("BUSID: %s\n", getReviewText( g_hash_table_lookup(business,"ABmhd3xJM_mup1h4OqpNuQ" )));
    printf("STATE: %s\n",getReviewId( g_hash_table_lookup(business,"iGZNuiT_hKXSvGf22LPQ6A" )));

	g_hash_table_destroy(business);
*/
    return 0;
}