#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testar.h"
#include "ex2.c"

void addBusiness (BUSINESS bus, char *buf, int N){
	// char *str que representa todos os campos do business.
	
	bus[N] = malloc(sizeof(struct business));
	bus[N]->business_id = strdup(strsep(&buf,";"));
	bus[N]->name = strdup(strsep(&buf, ";"));
    bus[N]->city = strdup(strsep(&buf, ";"));
	bus[N]->state = atof(strsep(&buf, ";"));  
	bus[N]->categories = atoi(strsep(&buf, ";"));   
    
}

void addReviews (REVIEWS rev, char info[]){
	// char *str que representa todos os campos do business.
	
	rev = malloc(sizeof(struct reviews));
	rev->review_id = strdup(strsep(&info, ";"));
	rev->user_id = strdup(strsep(&info, ";"));
    rev->business_id = strdup(strsep(&info, ";"));
	rev->stars = atof(strsep(&info, ";"));  
	rev->useful = atoi(strsep(&info, ";"));
    rev->funny = atoi(strsep(&info, ";"));
    rev->cool = atoi(strsep(&info, ";"));   
}

// a)
int nr_neg_reviews(BUSINESS bus[], char **c1, int N){
    int n = 0;
    for (int i = 0; i < N; i++)
        if (bus[i]->review_count != 0) n++;
    return n;
}

// b)

int mais4estrelas (BUSINESS bus[], char **c1, int N){
    int n = 0;
    for (int i = 0; **c1; i++)
        if (bus[i]->stars >= 4.0) n++;
    return n;
}

// c)
/*
int maxReviews(REVIEWS rev[], int N){
    int max = 0;
    for (int i = 0; **c1; i++){
        int res = rev[i]->review_count;
        if (max < res) max = res;
    }
    return max;
}
*/
// d)

int nr_neg_cidade(BUSINESS bus[], char **c1, int N, char *cityName){
    int n = 0;
    for (int i = 0; **c1; i++)
        if (bus[i]-> city == cityName) n++;
    return n;
}

int maxNegocio(BUSINESS bus[], char **c1, int N){
    int max = 0;
    for (int i = 0; **c1; i++){
        int res = nr_neg_cidade(bus, c1,N, bus[i]->city);
        if (max < res) max = res;
    }
    return max;
}

// e)

/*
char* revMaisCool(REVIEWS rev[], char **c3, int N){
    int max1 = 0, max2 = 0, max3 = 0;
    char *res = NULL;
    for (int i = 0; **c3; i++){
        if (max1 < rev->cool){
            max1 = rev->cool;
            ...
        }
        if (max2 < max1){
            max2 = max1;
            ...
        }
        if (max3 < max2){
            ...
        }
    }
    return res;
}
*/


