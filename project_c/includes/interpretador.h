/**
* @file interpretador.h
* \brief Ficheiro que suporta a interpretação de uma sequência de um ou mais comandos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib-2.0/glib.h>


typedef struct var *VAR;


char ** doRegex (const gchar *string);

int interpretador();


