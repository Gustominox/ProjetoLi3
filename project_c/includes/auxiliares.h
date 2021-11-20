#ifndef AUXILIARES_H
#define AUXILIARES_H

/**
* @file auxiliares.h
* \brief Ficheiro com funções auxiliares usadas.
*/

#include <stdio.h>
#include <stdlib.h>
#include "glibWarningAvoid.h"

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
* \brief Calcula o tamanho de um array de strings (char*)
* @return Tamanho do array
*/
int len(char **arr);


/**
* \brief Verifica se word (char*) é elemento de arr (char**)
* @return 1 se é elemento, 0 se nao é elemento
*/
int in(char **arr,int len, char* word);


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
 * @param xp apontador para um array de strings
 * @param yp apontador para outro array de strings
 */
void swap(char ***xp, char ***yp);


/**
 * \brief Ordena uma matriz de forma decrescente segundo o valor de stars de cada linha
 * @param arr matriz
 * @param linhas número de linhas
 */
void ordenaDecresc(char ***arr, int linhas);


/**
 * \brief Função que transforma uma string num OPERATOR
 * @param oper string cujo contuedo refere um OPERATOR
 * @return OPERATOR
 */
OPERATOR stringToOperator(char* oper);

/**
 * \brief Dado um padrao de regular expression e uma string retorna o array de 
 * tokens do tipo string(char*) obtido ao aplicar o padrao na string
 * @param string string a qual se aplica o padrao
 * @param pattern padrao a ser aplicado
 * @return array de tokens
 */
char ** doRegex (const gchar *string, char * pattern);

/**
 * \brief Dado um padrao de regular expression e uma string retorna o array de 
 * tokens do tipo string(char*) obtido ao aplicar o padrao na string, onde
 * NAO EXISTE repeticoes de um mesmo token
 * @param string string a qual se aplica o padrao
 * @param pattern padrao a ser aplicado
 * @return array de tokens
 */
char ** doRegexSingular (const gchar *string, char * pattern);

#endif