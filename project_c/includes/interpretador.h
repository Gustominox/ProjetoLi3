/**
* @file interpretador.h
* \brief Ficheiro que suporta a interpretação de uma sequência de um ou mais comandos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* \brief Guarda numa variável o valor do resultado da invocação da query2
* @param sgr sgr
* @param letter letra com que o nome de um negócio
*/
TABLE query2(SGR sgr, char letter);

/**
* \brief Guarda numa variável o valor do resultado da invocação da query3
* @param sgr sgr
* @param business_id id de negócio
*/
TABLE query3(SGR sgr, char *business_id);

/**
* \brief Guarda numa variável o valor do resultado da invocação da query4
* @param sgr sgr
* @param user_id id de utilizador
*/
TABLE query4(SGR sgr, char *user_id);

/**
* \brief Guarda numa variável o valor do resultado da invocação da query5
* @param sgr sgr
* @param stars número de estrelas de um negócio
* @param city cidade onde se situa o negócio
*/
TABLE query5(SGR sgr, float stars, char *city);

/**
* \brief Guarda numa variável o valor do resultado da invocação da query6
* @param sgr sgr
* @param top top negócios
*/
TABLE query6(SGR sgr, int top);

/**
* \brief Guarda numa variável o valor do resultado da invocação da query7
* @param sgr sgr
*/
TABLE query7(SGR sgr);

/**
* \brief Guarda numa variável o valor do resultado da invocação da query8
* @param sgr sgr
* @param top quantidade dos top negócios
* @param category categorias de negócios
*/
TABLE query8(SGR sgr, int top, char *category);

/**
* \brief Guarda numa variável o valor do resultado da invocação da query9
* @param sgr sgr
* @param top número de top negócios
* @param word palavra referida no campo text
*/
TABLE query9(SGR sgr, int top, char *word);