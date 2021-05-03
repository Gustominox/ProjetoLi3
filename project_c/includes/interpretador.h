#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

/**
* @file interpretador.h
* \brief Ficheiro que suporta a interpretação de uma sequência de um ou mais comandos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib-2.0/glib.h>
#include "paginacao.h"
#include "auxiliares.h"
#include "sgr.h"


typedef struct var *VAR;

/**
 * \brief
 * @param
 * @return
 */
char ** doRegex (const gchar *string);


/**
 * \brief Função que visualiza o valor de uma variável num formato visual, sob a forma de uma tabela
 * @param table table
 */
void show (TABLE table);


/**
 * \brief  Função que envia o conteúdo de uma variável para um ficheiro de formato csv
 * @param table table
 * @param delim separador
 * @param path ficheiro a formatar
 */
void toCSV(TABLE table, char delim, char path[]);


/**
 * \brief Função que atribui a uma variável o conteúdo de um ficheiro csv 
 * @param filepath ficheiro csv
 * @param delim separador
 * @return table que contém o conteúdo do ficheiro csv
 */
TABLE fromCSV(char filepath[] ,char *delim);


/**
 * \brief Função que filtra dados de uma tabela, dada uma coluna, um valor de comparação e um operador de comparação
 * @param table table
 * @param columName nome da coluna especifica cujos conteúdos serão comparados ao value
 * @param value valor de comparação
 * @param oper operador de comparação
 * @return table filtrada
 */
TABLE filter(TABLE table, char columName[], char* value, OPERATOR oper);


/**
 * \brief Função que obtém um subconjunto de colunas de uma tabela
 * @param table table
 * @param cols primeiras cols colunas
 * @return table com apenas o subconjunto de colunas
 */
TABLE proj(TABLE table, int cols);


/**
* \brief Função que acede a valores/registos contidos numa determinada posição da tabela
* @param table table 
* @param linha linha em que se encontra o valor/registo da tabela dada
* @param coluna coluna em que se encontra o valor/registo da tabela dada
* @return table com apenas o valor/registo contido numa determinada posição da tabela dada
*/
TABLE indexa (TABLE table, int linha, int coluna);


/**
 * \brief Função que indica o extremo valor de uma dada coluna de acordo com o operador de comparação
 * Se o operador for GT, será indicado o máximo valor dessa coluna; se for LT, será indicado o mínimo valor dessa coluna
 *
 * @param table table
 * @param columName coluna da tabela dada
 * @param op operador de comparação
 */
void maxOrMin(TABLE table, char columName[], OPERATOR op);


/**
 * \brief Função que testa se o caracter '=' é encontrado na linha ou não
 * @param linha a linha dada pelo usuário
 * @return 1 se for encontrado, 0 caso contrário
 */
int isAssignment(char *linha);


/**
 * \brief Função que verifica se uma variável existe no array
 * @param vars array com o nome das variáveis 
 * @param N numero de posições ocupadas no array
 * @param var variável 
 * @return posição se a variavel existir no array, -1 se não existir
 */
int verificaVar(VAR vars, int N, char* var);


/**
 * 
 */
int interpretador();

#endif