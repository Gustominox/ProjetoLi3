#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "auxiliares.h"


char *getBusId(BUSINESS bus){
  return bus->business_id;
}
void setBusId(BUSINESS bus, char newId[]){
  strcpy(bus->business_id,newId);
}

char *getName(BUSINESS bus){
  return bus->name;
}
void setName(BUSINESS bus, char newName[]){
  strcpy(bus->name,newName);
}

char *getCity(BUSINESS bus){
  return bus->city;
}
void setCity(BUSINESS bus, char newCity[]){
  strcpy(bus->city,newCity);
}

char* getState(BUSINESS bus){
  return bus->state;
}
void setState(BUSINESS bus, char newState[]){
  bus->state = newState;
}

char** getCategories(BUSINESS bus){
  return bus->categories;
}
void setCategories(BUSINESS bus, char** newCategories){
  bus->categories = newCategories;
}

char *getUserId (USER user){
    return user->id;
}
void setUserId(USER user, char newId[]){
    strcpy (user->id, newId);
}

char *getUserName (USER user){
    return user->name;
}
void setUserName(USER user, char newName[]){
    strcpy (user->name, newName);
}

char *getUserFriends (USER user){
    return user->friends;
}
void setUserFriends(USER user, char newFriends[]){
    strcpy (user->friends, newFriends);
}

char *getReviewId (REVIEW review){
    return review->review_id;
}
void setReviewId(REVIEW review, char newId[]){
    strcpy (review->review_id, newId);
}

char *getReviewUser (REVIEW review){
    return review->user_id;
}
void setReviewUser(REVIEW review, char newUser[]){
    strcpy (review->user_id, newUser);
}

char *getReviewBus (REVIEW review){
    return review->business_id;
}
void setReviewBus(REVIEW review, char newBus[]){
    strcpy (review->business_id, newBus);
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

char *getReviewDate (REVIEW review){
    return review->date;
}
void setReviewDate(REVIEW review, char newDate[]){
    strcpy (review->date, newDate);
}

char *getReviewText (REVIEW review){
    return review->text;
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

    char *userStr[3] = {user->id, user->name, user->friends};
    return *userStr;
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

    char *reviewStr[9] = {rev->review_id, rev->user_id, rev->business_id, starsToStr, usefulToStr, funnyToStr, coolToStr, rev->date, rev->text};
    return *reviewStr;
}

char *businessToString(BUSINESS bus){

    char *businessStr[5] = {bus->business_id, bus->name, bus->city, bus->state, *bus->categories};
    return *businessStr;
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

    char** categ;                               // Guardará todas as strings referentes às categorias.
    char* temp = strdup(strsep(&info, ";"));    // Guardará o conteúdo do array info até encontrar um ";"
    for(int i = 0; temp != NULL; i++)
        categ[i] = strdup(strsep(&temp, ","));  // Na primeira posição do array aux, será guardado a primeira categoria (separadas por ",").
    strcpy(*bus->categories, *categ);

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
