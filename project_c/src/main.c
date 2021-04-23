#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>
#include "sgr.h"
#include "interpretador.h"

void 
transStructToTable( GHashTable* hash,void**arrStr,int tmhArr,char* (*funcao) (void* bus) ){
    
    for(int i=0; i < tmhArr; i++){
    
        char *id = funcao(arrStr[i]); 
        //free(temp);
        printf("[%d] hash: %s\n",i,id);
        
        GSList *head = NULL;
        
        if(head = g_hash_table_lookup(hash,id)){
            head = g_slist_prepend (head, arrStr[i]);
            g_hash_table_insert(hash,id,head);
        }else{
            GSList *list = NULL;
            list = g_slist_prepend (list, arrStr[i]);
    
            g_hash_table_insert(hash,id,list);
        
        }
    }
 

}

int main(int argc, char *argv[]) {


char linha[1024];

int tmh,tmhs;
char **info;
char **info1;
char **info2;

info = lerFichCsv(&tmh,"input/business_full.csv");
info1 = lerFichCsv(&tmhs,"input/users_full.csv");
info2 = lerFichCsv(&tmhs,"input/reviews_1M.csv");
//printf("Espera\n");
//fgets(linha, 1024, stdin);
//USER *bus = NULL;
//bus = transStrToUsers(info,&tmhs,bus);
for (int j = 0; j < tmh; j++)
        free (info[j]);
free(info);
//printf("%s\n",info[0]);
//GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
//GHashTable* hash1 = g_hash_table_new(g_str_hash, g_str_equal);
//GHashTable* hash2 = g_hash_table_new(g_str_hash, g_str_equal);

//transStructToTable(hash,bus,tmhs,getUserId);
//transStructToTable(hash1,bus,tmh,getBusCity);
//transStructToTable(hash2,bus,tmh,getBusName);

//printf("There are %d keys in the hash table\n",
//        g_hash_table_size(hash));
//printf("There are %d keys in the hash table\n",
//        g_hash_table_size(hash1));

//GSList* list = g_hash_table_lookup(hash,"ufCxltuh56FF4-ZFZ6cVhg");
//printf ("%s\n",getBusCity( list->data));

fgets(linha, 1024, stdin);
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