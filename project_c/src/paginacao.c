#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paginacao.h"
// #include <glib.h>


struct table{
    char **paginas;       // Array de páginas
    int *numPag;           // Número da página atual
};


// numPag++ :: Avançar na página
// numPag-- :: Recuar na página


int getNumPag(TABLE table){
    return *table->numPag;
}
void setNumPag(TABLE table, int newNumPag){
    table->numPag = newNumPag;
}

char** getPaginas(TABLE table){
    char **paginas = NULL;
    int i = 0;
    for(i = 0; table->paginas[i] != NULL; i++){
        paginas = realloc(paginas, sizeof(char*)*(i+1));
        paginas[i] = strdup(table->paginas[i]);
    }
    paginas[i] = NULL;
    return paginas;
}
void setPaginas(TABLE table, char **newPaginas){
    table->paginas = newPaginas;
}



