#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testar.h"

int lerBusiness (char **business){
    
    business = NULL;

    FILE *fd1 = fopen("business.csv", "r");
    if (fd1 == NULL){
          printf ("Error opening business.csv");
          return -1;
    }

    int i = 0;
    char buff[1024];
    while(fgets(buff,1024,fd1)){

      business = realloc(business, sizeof(char*)*(i+1));
      // estender espaço do business[][], do espaço que já temos (segundo i) + uma linha.
		  business[i] = strdup(buff); // malloc + strcpy.
		  i++;
    }

      fclose (fd1);
  return i;
} 

int lerUser (char **users,char path[]){
    
    users = NULL;

    FILE *fd2 = fopen(path, "r");
    if (fd2 == NULL){
          printf ("Error opening file");
          return -1;
    }

    int tmh = 0;
    char buff[1024];
    while(fgets(buff,1024,fd2)){

      users = realloc(users, sizeof(char*)*(tmh+1));
      // estender espaço do users, do espaço que já temos (segundo tmh) + uma linha.
		  users[tmh] = strdup(buff); // malloc + strcpy.
		  tmh++;
    }

    fclose (fd2);
	return tmh;
  
} 

int lerReviews (char **reviews){
    
    reviews = NULL;

    FILE *fd3 = fopen("reviews.csv", "r");
    if (fd3 == NULL){
          printf ("Error opening reviews.csv");
          return -1;
    }

    int tmh = 0;
    char buff[1024];
    while(fgets(buff,1024,fd3)){

      reviews = realloc(reviews, sizeof(char*)*(tmh+1));
      // estender espaço do reviews, do espaço que já temos (segundo tmh) + uma linha.
		  reviews[tmh] = strdup(buff); // malloc + strcpy.
		  tmh++;
    }

  

      fclose (fd3);
	return tmh;
}
