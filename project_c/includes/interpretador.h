/**
* @file interpretador.h
* \brief Ficheiro que suporta a interpretação de uma sequência de um ou mais comandos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib-2.0/glib.h>


typedef struct var *VAR;

/**
 * @brief
 * @param
 * @return
 */
char ** doRegex (const gchar *string);


/**
 * @brief Função que visualiza o valor de uma variável num formato visual, sob a forma de uma tabela
 * @param table table
 */
void show (TABLE table);


/**
 * @brief  Função que envia o conteúdo de uma variável para um ficheiro de formato csv
 * @param table table
 * @param delim separador
 * @param path ficheiro a formatar
 */
void toCSV(TABLE table, char delim, char path[]);


/**
 * @brief Função que atribui a uma variável o conteúdo de um ficheiro csv 
 * @param filepath ficheiro csv
 * @param delim separador
 * @return table que contém o conteúdo do ficheiro csv
 */
TABLE fromCSV(char filepath[] ,char delim);


/**
 * @brief Função que compara o conteúdo de uma table, numa dada coluna, com o valor de comparação que é dado
 * @param content conteúdo da table recebida, numa dada coluna
 * @param value valor de comparação 
 * @param oper operador de comparação
 * @return zero se tiver sucesso, 1 caso contrário
 */ 
int compare(char* content, char* value, OPERATOR oper);


/**
 * @brief Função que filtra dados de uma tabela, dada uma coluna, um valor de comparação e um operador de comparação
 * @param table table
 * @param columName nome da coluna especifica cujos conteúdos serão comparados ao value
 * @param value valor de comparação
 * @param oper operador de comparação
 * @return table filtrada
 */
TABLE filter(TABLE table, char columName[], char* value, OPERATOR oper);


/**
 * @brief Função que obtém um subconjunto de colunas de uma tabela
 * @param table table
 * @param cols primeiras cols colunas
 * @return table com apenas o subconjunto de colunas
 */
TABLE proj(TABLE table, int cols);


/**
 * 
 */
int isAssignment(char *linha);


/**
 * 
 */
int interpretador();


