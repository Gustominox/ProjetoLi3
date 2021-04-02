#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"


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
void setCategories(BUSINESS bus, int newCategories[][]){
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
      
      // estender espaço do users, do espaço que já temos (segundo tmh) + uma linha.
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

    char *businessStr[5] = {bus->business_id, bus->name, bus->city, bus->state, bus->state};
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
	  
    bus->state = strdup(strsep(&info, ";"));
    if(strlen(getState(bus)) != 2) return NULL;
    for (int i = 0; i < 2; i++)
        if (bus[i]->state < 'A' && bus[i]->state > 'Z')
            return NULL;
	  
    bus->categories = strdup(strsep(&info, ";"));
    // Todas as categorias são válidas, até mesmo a falta delas.

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
	  
    rev->useful = atoi(strsep(&info, ";"));
    if(getReviewUseful(rev) < 0) return NULL;
    
    rev->funny = atoi(strsep(&info, ";"));
    if(getReviewUseful(rev) < 0) return NULL;
    
    rev->cool = atoi(strsep(&info, ";"));
    if(getReviewUseful(rev) < 0) return NULL;

    rev->date = strdup(strsep(&info, ";"));
    if(strlen(getReviewDate(rev)) != 19) return NULL; // YYYY-MM-DD HH:MM:SS

    rev->text = strdup(strsep(&info, ";"));
  
  return rev;   
}
