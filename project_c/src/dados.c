#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "auxiliares.h"


char *getBusId(BUSINESS bus){
  return strdup(bus->business_id);
}
void setBusId(BUSINESS bus, char newId[]){
  strcpy(bus->business_id,newId);
}

char *getName(BUSINESS bus){
  return strdup(bus->name);
}
void setName(BUSINESS bus, char newName[]){
  strcpy(bus->name,newName);
}

char *getCity(BUSINESS bus){
  return strdup(bus->city);
}
void setCity(BUSINESS bus, char newCity[]){
  strcpy(bus->city,newCity);
}

char* getState(BUSINESS bus){
  return strdup(bus->state);
}
void setState(BUSINESS bus, char newState[]){
  bus->state = newState;
}

char** getCategories(BUSINESS bus){
    char** categ = NULL;
    int i;
    for( i = 0; bus->categories[i] != NULL; i++){
       categ = realloc(categ,sizeof(char*)*(i+1));
       categ[i] = strdup(bus->categories[i]);
    }
    categ[i] = NULL;
  return categ;
}
void setCategories(BUSINESS bus, char** newCategories){
  bus->categories = newCategories;
}

char *getUserId (USER user){
    return strdup(user->id);
}
void setUserId(USER user, char newId[]){
    strcpy (user->id, newId);
}

char *getUserName (USER user){
    return strdup(user->name);
}
void setUserName(USER user, char newName[]){
    strcpy (user->name, newName);
}

char **getUserFriends (USER user){
    char** friends = NULL;
    int i;
    for( i = 0; user->friends[i] != NULL; i++){
       friends = realloc(friends,sizeof(char*)*(i+1));
       friends[i] = strdup(user->friends[i]);
    }
    friends[i] = NULL;
  return friends;
}
void setUserFriends(USER user, char **newFriends){
    user->friends = newFriends;
}

char *getReviewId (REVIEW review){
    return strdup(review->review_id);
}
void setReviewId(REVIEW review, char newId[]){
    strcpy (review->review_id, newId);
}

char *getReviewUser (REVIEW review){
    return strdup(review->user_id);
}
void setReviewUser(REVIEW review, char newUser[]){
    strcpy (review->user_id, newUser);
}

char *getReviewBus (REVIEW review){
    return strdup(review->business_id);
}
void setReviewBus(REVIEW review, char newBus[]){
    strcpy (review->business_id, newBus);
}

float getReviewStars (REVIEW review){
    float stars = review->stars;
    char starsToStr[5];
    sprintf(starsToStr, "%g", stars);
    return atof(strdup(starsToStr));
}
void setReviewStars(REVIEW review, float newStars){
    review->stars = newStars;
}

int getReviewUseful (REVIEW review){
    int useful = review->useful;
    char usefulToStr[5];
    sprintf(usefulToStr, "%d", useful);
    return atoi(strdup(usefulToStr));
}
void setReviewUseful(REVIEW review, int newUseful){
    review->useful = newUseful;
}

int getReviewFunny (REVIEW review){
    int funny = review->funny;
    char funnyToStr[5];
    sprintf(funnyToStr, "%d", funny);
    return atoi(strdup(funnyToStr));
}
void setReviewFunny(REVIEW review, int newFunny){
    review->funny = newFunny;
}

int getReviewCool (REVIEW review){
    int cool = review->cool;
    char coolToStr[5];
    sprintf(coolToStr, "%d", cool);
    return atoi(strdup(coolToStr));
}
void setReviewCool(REVIEW review, int newCool){
    review->cool = newCool;
}

char *getReviewDate (REVIEW review){
    return strdup(review->date);
}
void setReviewDate(REVIEW review, char newDate[]){
    strcpy (review->date, newDate);
}

char *getReviewText (REVIEW review){
    return strdup(review->text);
}
void setReviewText(REVIEW review, char newText[]){
    strcpy (review->text, newText);
}


char *userToString(USER user){

    char *userStr = malloc(sizeof(char)*1000);
    strcat(userStr,"User [");
    strcat(userStr,getUserId(user));
    strcat(userStr,getUserName(user));
    strcat(userStr,getUserFriends(user));
    strcat(userStr,"]");    
    printf("%s\n", userStr);

    return userStr;
}

char *reviewToString(REVIEW rev){

    float stars = getReviewStars(rev);
    char starsToStr[5];
    sprintf(starsToStr, "%f", stars);

    int useful = getReviewUseful(rev);
    char usefulToStr[3];
    sprintf(usefulToStr, "%d", useful);

    int funny = getReviewFunny(rev);
    char funnyToStr[3];
    sprintf(funnyToStr, "%d", funny);

    int cool = getReviewCool(rev);
    char coolToStr[3];
    sprintf(coolToStr, "%d", cool);

    //char *reviewStr[9] = {rev->review_id, rev->user_id, rev->business_id, starsToStr, usefulToStr, funnyToStr, coolToStr, rev->date, rev->text};
    char *reviewStr =  malloc(sizeof(char)*1000);
    strcat(reviewStr,"Review [");
    strcat(reviewStr,getReviewId(rev));
    strcat(reviewStr,getReviewUser(rev));
    strcat(reviewStr,getReviewBus(rev));
    strcat(reviewStr,starsToStr);
    strcat(reviewStr,usefulToStr);
    strcat(reviewStr,funnyToStr);
    strcat(reviewStr,coolToStr);
    strcat(reviewStr,getReviewDate(rev));
    strcat(reviewStr,getReviewText(rev));
    strcat(reviewStr,"]");
    
    return reviewStr;
}

char *businessToString(BUSINESS bus){

    char *businessStr = malloc(sizeof(char)*1024);
    // {bus->business_id, bus->name, bus->city, bus->state, *bus->categories};
    strcat(businessStr,"Business [");
    strcat(businessStr,getBusId(bus));
    strcat(businessStr,"; ");
    strcat(businessStr,getName(bus));
    strcat(businessStr,"; ");
    strcat(businessStr,getCity(bus));
    strcat(businessStr,"; ");
    strcat(businessStr,getState(bus));
    strcat(businessStr,"; ");
    char **temp = getCategories(bus);
    for (int i = 0; temp[i] != NULL; i++){
        strcat(businessStr, temp[i]);
        strcat(businessStr," ");

    }
    strcat(businessStr,"]");

    return businessStr;
}


char** lerFichCsv ( int* tmh, char path[]){
    
    char **info = NULL;
    FILE *fp = fopen(path, "r");
    if (fp == NULL){
        printf ("Error opening file\n");
        return NULL;
    }
    int auxTmh;
    auxTmh = 0;
    char buff[180000];
    while(fgets(buff,180000,fp)){
        info = realloc(info, sizeof(char*)*(auxTmh+1));
	    info[auxTmh] = strdup(buff); // malloc + strcpy.
	    auxTmh++;
    }
//	for (int j = 0; j < auxTmh; j++)
//      		printf("%s", info[j]);	
   
    *tmh = auxTmh;
    fclose (fp);
	return info;
} 

void transStrToTable(char **info, GHashTable* hash, void* (*funcao) (char info[]) ){

    for (int i = 0; i<5; i++){
	    char *temp = strdup(info[i]);
        char *id =  strdup (strsep(&temp,";"));
        //free(temp);
        printf("OBJETO [%d]\n",i);
    
        void* obj = funcao(info[i]);
        if(obj){
            g_hash_table_insert(hash,id,obj);
        }else{
            free(obj);            
        }
        //free(temp);
//free(id);
    }

}

BUSINESS addBusiness ( char info[]){

    BUSINESS bus = (BUSINESS) malloc( sizeof(struct business));
    
    bus->business_id = strdup(strsep(&info,";"));
	if(strlen(getBusId(bus)) != 22) return NULL;
    
    bus->name = strdup(strsep(&info, ";"));
    if(strlen(getName(bus)) == 0) return NULL;
    
    bus->city = strdup(strsep(&info, ";"));
    if(strlen(getCity(bus)) == 0) return NULL;

     
    bus->state = strdup(strsep(&info, ";"));     
    if(strlen(getState(bus)) != 2) return NULL;           
    for(int i = 0; i < 2; i++)                  
        if(isUpper(bus->state[i]) != 1) return NULL;   

    char* temp = strdup(strsep(&info, "\n"));   
    //printf("TEMP: %s\n",temp);
    bus->categories=NULL;
    int i;
    for( i = 0; temp != NULL; i++){
        bus->categories = realloc(bus->categories,sizeof(char*)*(i+1));
        bus->categories[i] = strdup(strsep(&temp, ","));  // Na primeira posição do array aux, será guardado a primeira categoria (separadas por ",").
        //printf("%s\n",bus->categories[i]);
    }
    bus->categories = realloc(bus->categories,sizeof(char*)*(i+1));
    bus->categories[i] = NULL;
    //printf("TEMP: %s\n",temp);
    free(temp);
    //printf("%s\n",getBusId(bus));
    return bus;
}

USER addUser ( char info[]){

    USER user = (USER) malloc(sizeof(struct user));
	//printf("INFO: %s\n", info);
    
    user->id = strdup(strsep(&info,";"));
    printf("ID: %s\n", user->id);
    if(strlen(getUserId(user)) != 22) return NULL;
    
    user->name = strdup(strsep(&info,";"));
    printf("NAME: %s\n", user->name);
    if(strcmp(getUserName(user),"") == 0) return NULL;
    
    char* temp = strdup(strsep(&info, "\n"));   
    //printf("TEMP: %s\n",temp);
    user->friends=NULL;
    int i;
    for( i = 0; temp != NULL; i++){
        user->friends = realloc(user->friends,sizeof(char*)*(i+1));
        user->friends[i] = strdup(strsep(&temp, ","));  // Na primeira posição do array aux, será guardado a primeira categoria (separadas por ",").
        //printf("%s\n",bus->categories[i]);
    }
    user->friends = realloc(user->friends,sizeof(char*)*(i+1));
    user->friends[i] = NULL;
    //printf("TEMP: %s\n",temp);
    free(temp);
    printf("FRIENDS:\n");
    for (int i = 0; user->friends[i] != NULL; i++){
        printf("%s\n", user->friends[i]);
    }
    
    return user;
}


REVIEW addReview ( char info[]){
	
    REVIEW rev = malloc(sizeof(struct review));
    
    rev->review_id = strdup(strsep(&info, ";"));
    if(strlen(getReviewId(rev)) != 22) return NULL;
	  
    rev->user_id = strdup(strsep(&info, ";"));
    if(strlen(getReviewUser(rev)) != 22) return NULL;
    
    rev->business_id = strdup(strsep(&info, ";"));
    if(strlen(getReviewBus(rev)) != 22) return NULL;
	  
    rev->stars = atof(strsep(&info, ";"));
    if(getReviewStars(rev) > 5.0 && getReviewStars(rev) <= 0.0) return NULL;
	
    char* strUseful = strdup(strsep(&info, ";"));
    for (int i = 0; i < strlen(strUseful); i++)              
        if (isDigit(strUseful[i]) != 1) return NULL;          
    rev->useful = atoi(strUseful);                           
    if(getReviewUseful(rev) < 0) return NULL;                
    
    char* strFunny = strdup(strsep(&info, ";"));
    for (int i = 0; i < strlen(strFunny); i++)                           
        if (isDigit(strFunny[i]) != 1) return NULL;   
    rev->funny = atoi(strFunny);
    if(getReviewFunny(rev) < 0) return NULL;
    
    char* strCool = strdup(strsep(&info, ";"));
    for (int i = 0; i < strlen(strCool); i++)                           
        if (isDigit(strCool[i]) != 1) return NULL;   
    rev->cool = atoi(strCool);
    if(getReviewCool(rev) < 0) return NULL;

    rev->date = strdup(strsep(&info, ";"));
    if(strlen(getReviewDate(rev)) != 19) return NULL; // YYYY-MM-DD HH:MM:SS

    rev->text = strdup(strsep(&info, ";"));
  
  return rev;   
}
