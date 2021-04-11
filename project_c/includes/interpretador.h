/**
* @file interpretador.h
* \brief Ficheiro que suporta a interpretação de uma sequência de um ou mais comandos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


TABLE query2(SGR sgr, char lette);

TABLE query3(SGR sgr, char *business_id);

TABLE query4(SGR sgr, char *user_id);

TABLE query5(SGR sgr, float stars, char *city);

TABLE query6(SGR sgr, int top);

TABLE query7(SGR sgr);

TABLE query8(SGR sgr, int top, char *category);

TABLE query9(SGR sgr, int top, char *word);