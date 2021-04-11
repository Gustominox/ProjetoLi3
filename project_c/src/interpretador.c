#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpretador.h"

TABLE query2(SGR sgr, char letter){
    TABLE x = businesses_started_by_letter(sgr, letter);
    return x;
}

TABLE query3(SGR sgr, char *business_id){
    TABLE x = business_info(sgr, business_id);
    return x;
}

TABLE query4(SGR sgr, char *user_id){
    TABLE x =  businesses_reviewed(sgr, user_id);
    return x;
}

TABLE query5(SGR sgr, float stars, char *city){
    TABLE x = businesses_with_stars_and_city(sgr, stars, city);
    return x;
}

TABLE query6(SGR sgr, int top){
    TABLE x = top_businesses_by_city(sgr, top);
    return x;
}

TABLE query7(SGR sgr){
    TABLE x = international_users(sgr);
    return x;
}

TABLE query8(SGR sgr, int top, char *category){
    TABLE x = top_businesses_with_category(sgr, top, category);
    return x;
}

TABLE query9(SGR sgr, int top, char *word){
    TABLE x = reviews_with_word(sgr, top, word);
    return x;
}



