#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

struct business{
	char *business_id;
	char *name;
	char *city;
	float state;
	int categories;
};

struct reviews{
	char *review_id;
	char *user_id;
	char *business_id;
	float stars;
	int useful;
	int funny;
	int cool;
	//char *date; ////////////////// char ?????????????????????
	//char *text;
} ;

struct user{
	char *id;
	char *name;
	char *friends;
};

char** lerFichCsv (char **info, int* tmh, char path[]){
    
    FILE *fp = fopen(path, "r");
    if (fp == NULL){
          printf ("Error opening file\n");
          return -1;
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

BUSINESS* transStrToBus(char **info,BUSINESS *business){


}


REVIEWS* transStrToRev(char **info,REVIEWS *reviews){


}


USER* transStrToUsers(char **info,USER *users){


}

void addUser (USER user, char info[]){

	user->id = strdup(strsep(&info,";"));
	   
}


void addBusiness (BUSINESS bus, char info[]){

	bus->business_id = strdup(strsep(&info,";"));
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
