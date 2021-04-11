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


/**void show(TABLE table){
    int colunas, linhas;
    
    printf();
    printf("|      business_id   |    name        |");


}

void show(TABLE x){
    printf("----------------------------------------------------------");
    ...
    int i = 0;
    while(i < tsize)
}*/

int interpretador(SGR sgr){
    char linha[BUF_SIZE];
    char col[2], lin[2];
    char cmdname[BUF_SIZE];
    char filename[BUF_SIZE];
    char letter;
    TABLE x;
    SINAL s = OK;

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return ERRO_IO;
    
    
    if(strlen(linha)==8){ // comandos clinhaom 6 letras
        
        if(linha[0] == 'q' && linha[1] == 'u' && linha[2] == 'e' && linha[3] == 'r' && linha[4] == 'y' && linha[5] == '2' && linha[6] == ';'){
            printf("Qual e a letra com que comeca o nome do negocio?");
            scanf("%c", &letter);
            x = query2(sgr, letter);
        }
        else if(linha[0] == 'q' && linha[1] == 'u' && linha[2] == 'e' && linha[3] == 'r' && linha[4] == 'y' && linha[5] == '3' && linha[6] == ';'){
            x = query3(sgr, business_id);
        }
        else if(linha[0] == 'q' && linha[1] == 'u' && linha[2] == 'e' && linha[3] == 'r' && linha[4] == 'y' && linha[5] == '4' && linha[6] == ';'){
            x = query4(sgr, user_id);
        }
        else if(linha[0] == 'q' && linha[1] == 'u' && linha[2] == 'e' && linha[3] == 'r' && linha[4] == 'y' && linha[5] == '5' && linha[6] == ';'){
            x = query5(sgr, stars, city);
        }
        else if(linha[0] == 'q' && linha[1] == 'u' && linha[2] == 'e' && linha[3] == 'r' && linha[4] == 'y' && linha[5] == '6' && linha[6] == ';'){
            x = query6(sgr, top);    
        }
        else if(linha[0] == 'q' && linha[1] == 'u' && linha[2] == 'e' && linha[3] == 'r' && linha[4] == 'y' && linha[5] == '7' && linha[6] == ';'){
            x = query7(sgr);
        }
        else if(linha[0] == 'q' && linha[1] == 'u' && linha[2] == 'e' && linha[3] == 'r' && linha[4] == 'y' && linha[5] == '8' && linha[6] == ';'){
           x = query8(sgr, top, categorie);
        }
        else if(linha[0] == 'q' && linha[1] == 'u' && linha[2] == 'e' && linha[3] == 'r' && linha[4] == 'y' && linha[5] == '9' && linha[6] == ';'){
            x = query2(sgr, top, word);
        }    
        else s = COMANDO_INEXISTENTE;

    }


    //Ainda podem faltar mais comandos com 4 letras

    else if (strlen(linha) == 6){ // Comandos 4 letras
        if(linha[0] == 'q' && linha[1] == 'u' && linha[2] == 'i' && linha[3] == 't' && linha[4] == ';') exit(0);
        else s = COMANDO_INEXISTENTE;
    }
    else
        s = COMANDO_INEXISTENTE;

}    

