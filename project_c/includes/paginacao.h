#ifndef PAGINACAO_H
#define PAGINACAO_H

#include <stdio.h>
#include <stdlib.h>


/*!
* @typedef table
*
* @field   paginas       Array de páginas (dos resultados obtidos nas queries)
* @field   numLin        O número da linha atual
* @field   numLinTotal   O número de linhas totais
*/
typedef struct table *TABLE;


/**
* \brief Obtém o número da linha atual
* @param table table
* @return número da linha atual
*/
int getNumLin(TABLE table);


/**
* \brief Muda o número da linha atual
* @param table table
* @param newNumLin nova linha atual
*/
void setNumLin(TABLE table, int newNumLin);


/**
* \brief Obtém o número total de linhas
* @param table table
* @return número total de linhas
*/
int getNumLinTotal(TABLE table);


/**
* \brief Muda o número de linhas totais
* @param table table
* @param newNumLinTotal novo número de linhas totais
*/
void setNumLinTotal(TABLE table, int newNumLinTotal);


/**
* \brief Obtém as variaveis da table
* @param table table
* @return variaveis da table
*/
char*** getVariaveis(TABLE table);


/**
* \brief Muda as variaveis da table
* @param table table
* @param newVariaveis novas variaveis 
*/
void setVariaveis(TABLE table, char ***newVariaveis);


/**
* \brief Inicializa a estrutura de dados table
* @return a table inicializada
*/
TABLE init_table();


/**
* \brief Dado o conteúdo de um ficheiro, lê o seu conteúdo e carrega a estrutura de dados table
* @param info Conteúdo de um ficheiro
* @return a table carregada com o conteúdo do ficheiro
*/
TABLE load_table(char ***info);


/**
* \brief Imprime uma linha do array de variaveis
* @param variaveis variaveis
*/
void printLinha (char **variaveis);


/**
 * \brief Função que imprime uma página (10 linhas por página)
 * @param table table
 */
void printPagina (TABLE table);

/**
* \brief Dependendo do comando, avança ou recua na linha
* @param table table 
* @return 1 para parar a visaulização de pagínas, 0 se for para continuar a visualizar
*/
int acao(TABLE table);


void add_linha(TABLE table, char** linha);


char** init_linha();

char** add_palavra(char **linha, char* palavra);


#endif