#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

int lerFichCsv (char **users,char path[]){
    

    FILE *fp = fopen(path, "r");
    if (fp == NULL){
          printf ("Error opening file\n");
          return -1;
    }

    int tmh = 0;
    char buff[1024];
    while(fgets(buff,1024,fp)){

      users = realloc(users, sizeof(char*)*(tmh+1));
      // estender espaço do users, do espaço que já temos (segundo tmh) + uma linha.
		  users[tmh] = strdup(buff); // malloc + strcpy.
		  tmh++;
    }
    
    fclose (fp);
	return tmh;
  
} 
