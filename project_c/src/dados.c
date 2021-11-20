/**
@file dados.c
Construção do código correspondente às funções que modificam e criam as 
estruturas de dados.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dados.h"
#include "auxiliares.h"
/*
* \brief users do fich
*/
struct user{
	char *id;
	char *name;
	char *friends;
};

struct business{
	char *business_id;
	char *name;
	char *city;
	char *state;
	char **categories;
};

struct review{
	char *review_id;
	char *user_id;
	char *business_id;
	float stars;
	int useful;
	int funny;
	int cool;
	char *date;
	char *text;
};


char* getBusId(BUSINESS bus){
  return strdup(bus->business_id);
}
void setBusId(BUSINESS bus, char newId[]){
  strcpy(bus->business_id,newId);
}


char* getBusName(BUSINESS bus){
  return strdup(bus->name);
}
void setBusName(BUSINESS bus, char newName[]){
  strcpy(bus->name,newName);
}

char* getBusNameInicial(BUSINESS bus){
    char str[2] = "\0";
    str[0] = toupper(bus->name[0]);

    return strdup(str);
}


char* getBusCity(BUSINESS bus){
  return strdup(bus->city);
}
void setBusCity(BUSINESS bus, char newCity[]){
  strcpy(bus->city,newCity);
}


char* getBusState(BUSINESS bus){
  return strdup(bus->state);
}
void setBusState(BUSINESS bus, char newState[]){
  bus->state = newState;
}


char** getBusCategories(BUSINESS bus){
    char** categ = NULL;
    int i;
    for( i = 0; bus->categories[i] != NULL; i++){
       categ = realloc(categ,sizeof(char*)*(i+1));
       categ[i] = strdup(bus->categories[i]);
    }
    categ = realloc(categ,sizeof(char*)*(i+1));
    categ[i] = NULL;
  return categ;
}
void setBusCategories(BUSINESS bus, char** newCategories){
  bus->categories = newCategories;
}

char* getUserId (USER user){
    return strdup(user->id);
}
void setUserId(USER user, char newId[]){
    strcpy (user->id, newId);
}


char* getUserName (USER user){
    return strdup(user->name);
}
void setUserName(USER user, char newName[]){
    strcpy (user->name, newName);
}

/*
char** getUserFriends (USER user){
    char** friends = NULL;
    int i;
    for( i = 0; user->friends[i] != NULL; i++){
       friends = realloc(friends,sizeof(char*)*(i+1));
       friends[i] = strdup(user->friends[i]);
    }
    friends = realloc(friends,sizeof(char*)*(i+1));
    friends[i] = NULL;
  return friends;
}
void setUserFriends(USER user, char **newFriends){
    user->friends = newFriends;
}
*/

char* getReviewId (REVIEW review){
    return strdup(review->review_id);
}
void setReviewId(REVIEW review, char newRevId[]){
    strcpy(review->review_id, newRevId);
}


char* getReviewUser (REVIEW review){
    return strdup(review->user_id);
}
void setReviewUser(REVIEW review, char newUser[]){
    strcpy(review->user_id, newUser);
}


char* getReviewBus (REVIEW review){
    return strdup(review->business_id);
}
void setReviewBus(REVIEW review, char newBus[]){
    strcpy(review->business_id, newBus);
}


float getReviewStars (REVIEW review){
    return review->stars;
}
void setReviewStars(REVIEW review, float newStars){
    review->stars = newStars;
}


int getReviewUseful (REVIEW review){
    return review->useful;
}
void setReviewUseful(REVIEW review, int newUseful){
    review->useful = newUseful;
}


int getReviewFunny (REVIEW review){
    return review->funny;
}
void setReviewFunny(REVIEW review, int newFunny){
    review->funny = newFunny;
}


int getReviewCool (REVIEW review){
    return review->cool;
}
void setReviewCool(REVIEW review, int newCool){
    review->cool = newCool;
}


char* getReviewDate (REVIEW review){
    return strdup(review->date);
}
void setReviewDate(REVIEW review, char newDate[]){
    strcpy(review->date, newDate);
}


char* getReviewText (REVIEW review){
    return strdup(review->text);
}
char **getReviewWords (REVIEW review){
    char** r = doRegexSingular(review->text,"[A-z0-9]+");
    return r;
}
void setReviewText(REVIEW review, char newText[]){
    strcpy(review->text, newText);
}


char** lerFichCsv (int* tmh, char path[]){
    
    char **info = NULL;
    // open file
    FILE *fp = fopen(path, "r");
    // if file is null termina a func
    if (fp == NULL){
        printf ("\nERROR OPENING FILE\n");
        return NULL;
    }
    
    int auxTmh = 0;    // indice de linha
    char buff[180000];

    // estratégia: read file linha por linha
    while(fgets(buff,180000,fp)){
        // alocar memoria para o array info
        info = realloc(info, sizeof(char*)*(auxTmh+1));
	    info[auxTmh] = strdup(buff); // malloc + strcpy.
	    auxTmh++;
    }
    *tmh = auxTmh;
    // close file
    fclose (fp);
	return info;
} 

BUSINESS* transStrToBus(char **info,int *tmh,BUSINESS *business){
// cada linha do ficheiro é um business; daí criarmos um array de business com tantas posições quantas linhas
    int tmhBus = 0;
    for (int i = 0; i<*tmh; i++){
        
        business = realloc(business,sizeof(BUSINESS)*(tmhBus+1));
        business[tmhBus] = addBusiness( info[i]);
        
        if(business[tmhBus] == NULL) {
            
            free(business[tmhBus]);
            tmhBus--; 
        }
        
        tmhBus++;
    }
    
    business = realloc(business,sizeof(BUSINESS)*(tmhBus+1));
    business[tmhBus] = NULL ;
        
    for (int j = 0; j < *tmh; j++)
        free (info[j]);

    *tmh = tmhBus;
    return business; 
}

REVIEW* transStrToRev(char **info,int *tmh,REVIEW *reviews){

    int tmhRev = 0;
    for (int i = 0; i<*tmh; i++){
        reviews = realloc(reviews,sizeof(REVIEW)*(tmhRev+1));
        reviews[tmhRev] = addReview( info[i]);
    
        if(reviews[tmhRev] == NULL) {
            
            free(reviews[tmhRev]);
            tmhRev--; 
        }
        
        tmhRev++;
    }
    reviews = realloc(reviews,sizeof(REVIEW)*(tmhRev+1));
    reviews[tmhRev] = NULL ;
        
    for (int j = 0; j < *tmh; j++)
        free (info[j]);

    *tmh = tmhRev;
    return reviews; 
}


USER* transStrToUsers(char **info,int *tmh,USER *users){

    int tmhUser = 0;
    for (int i = 0; i<*tmh; i++){
        users = realloc(users,sizeof(USER)*(tmhUser+1));
        users[tmhUser] = addUser( info[i]);

        if(users[tmhUser] == NULL) {
            free(users[tmhUser]);
            tmhUser--; 
        }
        
        tmhUser++;
    
    }
    users = realloc(users,sizeof(USER)*(tmhUser+1));
    users[tmhUser] = NULL;
    
    for (int j = 0; j < *tmh; j++)
        free (info[j]);

    *tmh = tmhUser;
    return users; 
}


void transStructToTable( GHashTable* hash,void**arrStr,char* (*funcao) (void* bus) ){
// usa estes arrays dinamicos (das outras funções transStrTo...) para a criacao
// das hash tables que facilitam o processamento das query’s.

    for(int i=0; arrStr[i] != NULL; i++){
    
        char *id = funcao(arrStr[i]); 
       
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


void transStructToTableCate( GHashTable* hash,void**arrStr,char** (*funcao) (void* bus) ){
    
    for(int i=0; arrStr[i] != NULL; i++){
    
        char **id = funcao(arrStr[i]); 
        
        int j=0;
        while(id[j]){
            
            GSList *head = NULL;

            if(head = g_hash_table_lookup(hash,id[j])){
                head = g_slist_prepend (head, arrStr[i]);
                g_hash_table_insert(hash,id[j],head);
            }else{
                GSList *list = NULL;
                list = g_slist_prepend (list, arrStr[i]);

                g_hash_table_insert(hash,id[j],list);
            }
        j++;
        }
    }
}


BUSINESS addBusiness ( char info[]){

    BUSINESS bus = (BUSINESS) malloc( sizeof(struct business));
    
    bus->business_id = strdup(strsep(&info,";"));
	if(strlen(getBusId(bus)) != 22) return NULL;
    
    bus->name = strdup(strsep(&info, ";"));
    if(strlen(getBusName(bus)) == 0) return NULL;
    
    bus->city = strdup(strsep(&info, ";"));
    if(strlen(getBusCity(bus)) == 0) return NULL;

    bus->state = strdup(strsep(&info, ";"));     

    char* temp = strdup(strsep(&info, "\n"));
    bus->categories = NULL;
    int i;
    for( i = 0; temp != NULL; i++){
        bus->categories = realloc(bus->categories,sizeof(char*)*(i+1));
        bus->categories[i] = strdup(strsep(&temp, ","));
    }
    bus->categories = realloc(bus->categories,sizeof(char*)*(i+1));
    bus->categories[i] = NULL;
    
    free(temp);

    return bus;
}


void freeBusiness(BUSINESS bus){

    free(bus->business_id);
    free(bus->name);
    free(bus->city);
    free(bus->state);

    for (size_t i = 0; bus->categories[i] != NULL; i++){
        free(bus->categories[i]);
    }
    free(bus);
}


USER addUser ( char info[]){

    USER user = (USER) malloc(sizeof(struct user));

    user->id = strdup(strsep(&info,";"));
    if(strlen(user->id) != 22) return NULL;
    
    user->name = strdup(strsep(&info,";"));
    if(strcmp(user->name,"") == 0) return NULL;
    
    //user->friends = strdup(strsep(&info, "\n"));;

    return user;
}

void freeUser(USER user){

    free(user->id);
    free(user->name);
    //free(user->friends);
     
    free(user);
}

REVIEW addReview (char info[]){
	
    REVIEW rev = malloc(sizeof(struct review));
    
    rev->review_id = strdup(strsep(&info, ";"));
    if(strlen(rev->review_id) != 22) return NULL;
    
    rev->user_id = strdup(strsep(&info, ";"));
    if(strlen(rev->user_id) != 22) return NULL;

    rev->business_id = strdup(strsep(&info, ";"));
    if(strlen(rev->business_id) != 22) return NULL;

    rev->stars = atof(strsep(&info, ";"));
    if((rev->stars > 5.0) || (rev->stars <= 0.0)) return NULL;
	
    rev->useful = atoi(strsep(&info, ";"));

    rev->funny = atoi(strsep(&info, ";"));
    
    rev->cool = atoi(strsep(&info, ";"));

    rev->date = strdup(strsep(&info, ";"));
    if(strlen(rev->date) != 19) return NULL; // YYYY-MM-DD HH:MM:SS
    
    rev->text = strdup(strsep(&info, ";"));
    
    return rev;
}

void freeReview (REVIEW rev){

    free(rev->review_id);
    free(rev->user_id);
    free(rev->business_id);
    
    free(rev->date);
    free(rev->text);
    
    free(rev);
}