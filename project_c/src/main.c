/**
@file main.c
Função que controla o progama.
*/
/**
@mainpage Projeto Li3

*/
#include <stdio.h>
#include "dados.h"
#include <glib-2.0/glib.h>
#include <stdio.h>
#include "sgr.h"
#include "paginacao.h"
#include <ctype.h>
#include "auxiliares.h"
#include "interpretador.h"

int main(int argc, char *argv[]) {

int r = 0;

clearScreen();
printf("STARTED LOADING SGR...\n");
SGR sgr = load_sgr(NULL,NULL,NULL);
printf("FINISHED LOADING SGR!\n");
clearScreen();

r = interpretador(sgr);

return r;
}