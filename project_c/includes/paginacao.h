#include <stdio.h>
#include <stdlib.h>

/*!
* @typedef table
*
* @field   paginas    Array de páginas (dos resultados obtidos nas queries)
* @field   numPag     O número da página atual
*/
typedef struct table{
    char ***variaveis;         // Array de páginas
    int *numLin;               // Número da linha atual
    int *numLinTotal;          // Número de linhas totais
} *TABLE;

int getNumPag(TABLE table);

void setNumPag(TABLE table, int newNumPag);

char** getPaginas(TABLE table);

void setPaginas(TABLE table, char **newPaginas);