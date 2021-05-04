#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "dados.h"
#include "paginacao.h"

// #include <glib-2.0/glib.h>

/*!
* @typedef GHashTable
*/


/*!
* @typedef sgr
*
* @field   user        Utilizador
* @field   business    Negócio
* @field   review      Review
*/
typedef struct sgr *SGR;


/**
* \brief Inicializa as estruturas de dados correspondentes
*/
SGR init_sgr();


/** 
* \brief 
* @param sgr sgr
*/
void free_sgr(SGR sgr);


/**
 * \brief
 * @param value
 */
void *threadQuery9(void* value);


/**
 * \brief
 * @param value
 */
void *threadBusiness(void* value);


/**
 * \brief 
 * @param value
 */
void *threadReviews(void* value);


/** query 1
* \brief Dado o caminho para os 3 ficheiros (Users, Businesses, e Reviews), lê o seu conteúdo e carrega as estruturas de dados correspondentes
* @param users Utilizadores
* @param business Negócio
* @param reviews Reviews
*/
SGR load_sgr(char *users, char *businesses, char *reviews);


/** query 2
* \brief Determina a lista de nomes de negócios e o número total de negócios cujo nome inicia por uma dada letra
* @param sgr sgr
* @param letter letra com que o nome de um negócio
*/
TABLE businesses_started_by_letter(SGR sgr, char letter);


/** query 3
 * \brief Dado um id de negócio, determinar a sua informação: nome, cidade, estado, stars, e número total reviews
 * @param sgr sgr
 * @param business_id id de negócio
 */
TABLE business_info(SGR sgr, char *business_id);


/** query 4
 * \brief Dado um id de utilizador, determinar a lista de negócios aos quais fez review
 * @param sgr sgr
 * @param user_id id de utilizador
 */
TABLE businesses_reviewed(SGR sgr, char *user_id);


/** query 5 
 *  \brief Dado um número n de stars e uma cidade, determinar a lista de negócios com n ou mais stars na dada cidade
 * @param sgr sgr
 * @param stars número de estrelas de um negócio
 * @param city cidade onde se situa o negócio
*/
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city);


/** query 6 
 * \brief  Dado um número inteiro n, determinar a lista dos top n negócios em cada cidade
 * @param sgr sgr
 * @param top top negócios
*/
TABLE top_businesses_by_city(SGR sgr, int top);


/** query 7 
 * \brief  Determinar a lista de ids de utilizadores e o número total de utilizadores que tenham visitado mais de um estado
 * @param sgr sgr
*/
TABLE international_users(SGR sgr);


/** query 8 
 * \brief Dado um número inteiro n e uma categoria, determinar a lista dos top n negócios que pertencem a uma determinada categoria
 * @param sgr sgr
 * @param top quantidade dos top negócios
 * @param category categorias de negócios
*/
TABLE top_businesses_with_category(SGR sgr, int top, char *category);


/** query 9 
 * \brief Dada uma palavra, determinar a lista de ids de reviews que a referem no campo text
 * @param sgr sgr
 * @param top número de top negócios
 * @param word palavra referida no campo text
*/
TABLE reviews_with_word(SGR sgr, int top, char *word);

#endif