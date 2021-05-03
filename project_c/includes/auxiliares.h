#ifndef AUXILIARES_H
#define AUXILIARES_H

/**
* @file auxiliares.h
* \brief Ficheiro com funções auxiliares usadas.
*/

#include <stdio.h>
#include <stdlib.h>


typedef enum{
    LT,
    EQ,
    GT
} OPERATOR;


/**
* \brief Testa se uma string contem um float
* @return 1 se verdadeiro, 0 se falso
*/
int isFloat (char *s);


/**
* \brief Testa se uma string contem um integer
* @return 1 se verdadeiro, 0 se falso
*/
int isInteger (char *s);


/**
 * \brief Função que compara o conteúdo de uma table, numa dada coluna, com o valor de comparação que é dado
 * @param content conteúdo da table recebida, numa dada coluna
 * @param value valor de comparação 
 * @param oper operador de comparação
 * @return zero se tiver sucesso, 1 caso contrário
 */ 
int compare(char* content, char* value, OPERATOR oper);


/**
 * \brief Troca dois arrays de strings
 * @param xp um array de strings
 * @param yp outro array de strings
 */
void swap(char **xp, char **yp);


/**
 * \brief Ordena uma matriz de forma decrescente segundo o valor de stars de cada linha
 * @param arr matriz
 * @param linhas número de linhas
 */
void ordenaDecresc(int ***arr, int linhas);


/**
 * \brief Função que transforma uma string num OPERATOR
 * @param oper string cujo contuedo refere um OPERATOR
 * @return OPERATOR
 */
OPERATOR stringToOperator(char* oper);


#endif