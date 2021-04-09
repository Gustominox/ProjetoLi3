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
  return strdup(bus->categories);
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

char *getUserFriends (USER user){
    return strdup(user->friends);
}
void setUserFriends(USER user, char newFriends[]){
    strcpy (user->friends, newFriends);
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
    return strdup(review->stars);
}
void setReviewStars(REVIEW review, float newStars){
    review->stars = newStars;
}

int getReviewUseful (REVIEW review){
    return strdup(review->useful);
}
void setReviewUseful(REVIEW review, int newUseful){
    review->useful = newUseful;
}

int getReviewFunny (REVIEW review){
    return strdup(review->funny);
}
void setReviewFunny(REVIEW review, int newFunny){
    review->funny = newFunny;
}

int getReviewCool (REVIEW review){
    return strdup(review->cool);
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


char** lerFichCsv (char **info, int* tmh, char path[]){
    
    FILE *fp = fopen(path, "r");
    if (fp == NULL){
        printf ("Error opening file\n");
        return NULL;
    }
    int auxTmh = *tmh;
    auxTmh = 0;
    char buff[1024];
    while(fgets(buff,1024,fp)){
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

BUSINESS* transStrToBus(char **info,int tmh,BUSINESS *business){

    business = realloc(business,sizeof(struct business*)*(tmh));
    int tmhBus = 0;
    for (int i = 0; info[i]; i++){
        business[tmhBus] = addBusiness(business[tmhBus], info[i]);
        if(business[tmhBus] == NULL) tmhBus--;
        tmhBus++;
        //printf("[%d]\n", i);
    }
    
    
    for (int j = 0; j < tmh; j++)
        free (info[j]);

    return business; 
}


REVIEW* transStrToRev(char **info,int tmh,REVIEW *review){
    review = realloc(review,sizeof(struct review*)*(tmh));
    int tmhRev = 0;
    for (int i = 0; info[i]; i++){
        review[tmhRev] = addReview(review[tmhRev], info[i]);
        if(review[tmhRev] == NULL) tmhRev--;
        tmhRev++;
    }
    for (int j = 0; j < tmh; j++)
        free (info[j]);

    return review;
}


USER* transStrToUsers(char **info,int tmh,USER *users){
    users = realloc(users,sizeof(struct user*)*(tmh));
    int tmhUser = 0;
    for (int i = 0; info[i]; i++){
        users[tmhUser] = addUser(users[tmhUser], info[i]);
        if(users[tmhUser] == NULL) tmhUser--;
        tmhUser++;
    }
    for (int j = 0; j < tmh; j++)
        free (info[j]);

    return users;
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
    sprintf(starsToStr, "%g", stars);

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

    char *businessStr = malloc(sizeof(char)*1000);
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

USER addUser (USER user, char info[]){

    user = malloc(sizeof(struct user));
	  
    user->id = strdup(strsep(&info,";"));
    if(strlen(getUserId(user)) != 22) return NULL;
    
    user->name = strdup(strsep(&info,";"));
    if(strlen(getUserName(user)) == 0) return NULL;
    
    user->friends = strdup(strsep(&info,";"));

    return user;
}

BUSINESS addBusiness (BUSINESS bus, char info[]){

    bus = malloc(sizeof(struct business));
    
    bus->business_id = strdup(strsep(&info,";"));
	if(strlen(getBusId(bus)) != 22) return NULL;
    
    bus->name = strdup(strsep(&info, ";"));
    if(strlen(getName(bus)) == 0) return NULL;
    
    bus->city = strdup(strsep(&info, ";"));
    if(strlen(getCity(bus)) == 0) return NULL;
	
    char* st = strdup(strsep(&info, ";"));      // O state é um código de DUAS letras MAIÚSCULAS.
    if(strlen(st) != 2) return NULL;            // Verifica, então, se são apenas dois.
    for(int i = 0; i < 2; i++)                  
        if(isUpper(st[i]) != 1) return NULL;    // Verifica se são letras maiúsculas.
    strcpy(bus->state, st);

    char* temp = strdup(strsep(&info, "\n"));    // Guardará o conteúdo do array info até encontrar um ";"
    //printf("%s", temp);
    bus->categories=NULL;
    int i;
    for( i = 0; temp != NULL; i++){
       bus->categories = realloc(bus->categories,sizeof(char*)*(i+1));
       bus->categories[i] = strdup(strsep(&temp, ","));  // Na primeira posição do array aux, será guardado a primeira categoria (separadas por ",").
    }
    bus->categories[i] = NULL;
    printf("%s\n",businessToString(bus));
    return bus;
}

REVIEW addReview (REVIEW rev, char info[]){
	
    rev = malloc(sizeof(struct review));
    
    rev->review_id = strdup(strsep(&info, ";"));
    if(strlen(getReviewId(rev)) != 22) return NULL;
	  
    rev->user_id = strdup(strsep(&info, ";"));
    if(strlen(getReviewUser(rev)) != 22) return NULL;
    
    rev->business_id = strdup(strsep(&info, ";"));
    if(strlen(getReviewBus(rev)) != 22) return NULL;
	  
    rev->stars = atof(strsep(&info, ";"));
    if(getReviewStars(rev) > 5.0 && getReviewStars(rev) <= 0.0) return NULL;
	
    char* strUseful = strdup(strsep(&info, ";"));
    for (int i = 0; i < strlen(strUseful); i++)               // Este ciclo vai verificar se a string que recebe do ficheiro são
        if (isDigit(strUseful[i]) != 1) return NULL;          // efetivamente dígitos. Se forem letras, os dados são inválidos.
    rev->useful = atoi(strUseful);                            // Testamos assim se, quando a atoi retorna 0, houve algum erro de conversão ou se é mesmo 0.
    if(getReviewUseful(rev) < 0) return NULL;                 // Se for um valor negativo, é inválido.
    
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
