#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testar.h"

int lerBusiness (){
    char **c1; // guarda todas as linhas.
    c1 = NULL;

    FILE *fd1 = fopen("business.csv", "r");
    if (fd1 == NULL){
          printf ("Error opening business.csv");
          return -1;
    }

    int i = 0;
    char buff[1024];
    while(fgets(buff,1024,fd1)){

      c1 = realloc(c1, sizeof(char*)*(i+1));
      // estender espaço do c2, do espaço que já temos (segundo i) + uma linha.
		  c1[i] = strdup(buff); // malloc + strcpy.
		  i++;
    }

    for (int j = 0; j < i; j++)
      printf("%s", c1[j]);

    for (int j = 0; j < i; j++)
      free (c1[j]);

      fclose (fd1);
	return 0;
} 

int lerUser (){
    char **c2;
    c2 = NULL;

    FILE *fd2 = fopen("users.csv", "r");
    if (fd2 == NULL){
          printf ("Error opening users.csv");
          return -1;
    }

    int i = 0;
    char buff[1024];
    while(fgets(buff,1024,fd2)){

      c2 = realloc(c2, sizeof(char*)*(i+1));
      // estender espaço do c2, do espaço que já temos (segundo i) + uma linha.
		  c2[i] = strdup(buff); // malloc + strcpy.
		  i++;
    }

    for (int j = 0; j < i; j++){
      printf("%s", c2[j]);
    }

    for (int j = 0; j < i; j++)
      free (c2[j]);

      fclose (fd2);
	return 0;
} 

int lerReviews (){
    char **c3;
    c3 = NULL;

    FILE *fd3 = fopen("reviews.csv", "r");
    if (fd3 == NULL){
          printf ("Error opening reviews.csv");
          return -1;
    }

    int i = 0;
    char buff[1024];
    while(fgets(buff,1024,fd3)){

      c3 = realloc(c3, sizeof(char*)*(i+1));
      // estender espaço do c3, do espaço que já temos (segundo i) + uma linha.
		  c3[i] = strdup(buff); // malloc + strcpy.
		  i++;
    }

    for (int j = 0; j < i; j++){
      printf("%s", c3[j]);
    }

    for (int j = 0; j < i; j++)
      free (c3[j]);

      fclose (fd3);
	return 0;
}
