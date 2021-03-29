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

float getState(BUSINESS bus){
  return bus->state;
}
void setState(BUSINESS bus, float newState){
  bus->state = newState;
}

int getCategories(BUSINESS bus){
  return bus->categories;
}
void setCategories(BUSINESS bus, int newCategories){
  bus->categories = newCategories;
}

char *getUserId (USER user){
    return user->id;
}

void setUserId(USER user, char newId[]{
    strcpy (user->id, newId);
}

char *getUserName (USER user){
    return user->name;
}

void setUserName(USER user, char newName[]{
    strcpy (user->name, newName);
}

char *getUserFriends (USER user){
    return user->friends;
}

void setUserName(USER user, char newFriends[]{
    strcpy (user->friends, newFriends);
}

char *getReviewsId (REVIEWS reviews){
    return reviews->review_id;
}

void setReviewsId(REVIEWS reviews, char newId[]{
    strcpy (reviews->review_id, newId);
}

char *getReviewsUser (REVIEWS reviews){
    return reviews->user_id;
}

void setReviewsUser(REVIEWS reviews, char newUser[]{
    strcpy (reviews->user_id, newUser);
}

char *getReviewsBus (REVIEWS reviews){
    return reviews->business_id;
}

void setReviewsBus(REVIEWS reviews, char newBus[]{
    strcpy (reviews->business_id, newBus);
}

float *getReviewsStars (REVIEWS reviews){
    return reviews->stars;
}

void setReviewsStars(REVIEWS reviews, float newStars){
    reviews->stars = newStars;
}

int *getReviewsUseful (REVIEWS reviews){
    return reviews->useful;
}

void setReviewsUseful(REVIEWS reviews, int newUseful){
    reviews->useful = newUseful;
}

int *getReviewsFunny (REVIEWS reviews){
    return reviews->funny;
}

void setReviewsFunny(REVIEWS reviews, int newFunny){
    reviews->funny = newFunny;
}

int *getReviewsCool (REVIEWS reviews){
    return reviews->cool;
}

void setReviewsCool(REVIEWS reviews, int newCool){
    reviews->cool = newCool;
}

char *getReviewsDate (REVIEWS reviews){
    return reviews->date;
}

void setReviewsDate(REVIEWS reviews, char newDate[]{
    strcpy (reviews->date, newDate);
}

char *getReviewsText (REVIEWS reviews){
    return reviews->text;
}

void setReviewsText(REVIEWS reviews, char newText[]{
    strcpy (reviews->text, newText);
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

BUSINESS* transStrToBus(char **info,int tmh,BUSINESS business[]){

    business = malloc(sizeof(struct business*)*(tmh));
    for (int i = 0; i < tmh; i++){
    
    printf("BUSSINESS%s;indice[%d];tmh[%d]\n",business[i]->business_id,i,tmh);
    addBusiness(business[i], info[i]);
    
}

for (int j = 0; j < tmh; j++)
    free (info[j]);

    return business; 
}


REVIEWS* transStrToRev(char **info,int tmh,REVIEWS *reviews){


}


USER* transStrToUsers(char **info,int tmh,USER *users){


}

void addUser (USER user, char info[]){

	user->id = strdup(strsep(&info,";"));
	   
}


void addBusiness (BUSINESS bus, char info[]){

	bus->business_id = strdup(strsep(&info,";"));
	//if(strlen(getBusId()) >22);
  bus->name = strdup(strsep(&info, ";"));
  bus->city = strdup(strsep(&info, ";"));
	bus->state = atof(strsep(&info, ";"));  
	bus->categories = atoi(strsep(&info, ";"));   
}


void addReviews (REVIEWS rev, char info[]){
	
	rev->review_id = strdup(strsep(&info, ";"));
	rev->user_id = strdup(strsep(&info, ";"));
  rev->business_id = strdup(strsep(&info, ";"));
	rev->stars = atof(strsep(&info, ";"));  
	rev->useful = atoi(strsep(&info, ";"));
  rev->funny = atoi(strsep(&info, ";"));
  rev->cool = atoi(strsep(&info, ";"));   
}
