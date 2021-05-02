#ifndef DADOS_H
#define DADOS_H


/**
* @file dados.h
* \brief Ficheiro sobre as estruturas de dados, inclusive a leitura de um ficheiro e o tratamento dos dados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <glib-2.0/glib.h>

/***************************************************** Estruturas de dados *****************************************************/

/*!
* @typedef user
*
* @field   id        Identificação de um usuário
* @field   name      Nome do usuário
* @field   friends   Amigos do usuário
*/
typedef struct user *USER;


/*!
* @typedef business
*
* @field   business_id   Identificação de um negócio
* @field   name          Nome do negócio
* @field   city          Cidade onde está o negócio
* @field   state         Estado do negócio
* @field   categorias    Categorias do negócio
*/
typedef struct business *BUSINESS; 


/*!
* @typedef review
*
* @field   review_id      Identificação da review
* @field   user_id        Identificação do usuário        
* @field   business_id    Identificação do negócio
* @field   stars          Número de estrelas do negócio
* @field   useful         Grau de utilidade do negócio
* @field   funny          Grau de diversão do negócio
* @field   cool           O quão fixe é o negócio
* @field   date           Data de criação do negócio
* @field   text           Review do negócio
*/
typedef struct review *REVIEW;


/****************************************************** Funções get e set ******************************************************/

/**
* \brief Obtém a identificação do negócio
* @param bus Negócio
* @return identificação do negócio
*/
char *getBusId(BUSINESS bus);

/**
* \brief Muda a identificação do negócio
* @param bus Negócio
* @param newId nova identificação do negócio
*/
void setBusId(BUSINESS bus, char newId[]);

/**
* \brief Obtém o nome do negócio
* @param bus Negócio
* @return nome do negócio
*/
char *getBusName(BUSINESS bus);

/**
* \brief Muda o nome do negócio
* @param bus Negócio
* @param newName novo nome do negócio
*/
void setBusName(BUSINESS bus, char newName[]);




int getBusNameInicial(BUSINESS bus);





/**
* \brief Obtém a cidade onde está situado o negócio
* @param bus Negócio
* @return cidade onde está o negócio
*/
char *getBusCity(BUSINESS bus);

/**
* \brief Muda a cidade onde está situado o negócio
* @param bus Negócio
* @param newCity nova cidade onde está o negócio
*/
void setBusCity(BUSINESS bus, char newCity[]);

/**
* \brief Obtém o estado do negócio
* @param bus Negócio
* @return estado do negócio
*/
char* getBusState(BUSINESS bus);

/**
* \brief Muda o estado do negócio
* @param bus Negócio
* @param newState novo estado do negócio
*/
void setBusState(BUSINESS bus, char newState[]);

/**
* \brief Obtém as categorias do negócio
* @param bus Negócio
* @return categorias do negócio
*/
char** getBusCategories(BUSINESS bus);

/**
* \brief Muda as categorias do negócio
* @param bus Negócio
* @param newCategories novas categorias do negócio
*/
void setBusCategories(BUSINESS bus, char** newCategories);

/**
* \brief Obtém a identificação do usuário
* @param user Usuário
* @return identificação do usuário
*/
char *getUserId (USER user);

/**
* \brief Muda a identificação do usuário
* @param user Usuário
* @param newId nova identificação do usuário
*/
void setUserId(USER user, char newId[]);

/**
* \brief Obtém o nome do usuário
* @param user Usuário
* @return nome do usuário
*/
char *getUserName (USER user);

/**
* \brief Muda o nome do usuário
* @param user Usuário
* @param newName novo nome do usuário
*/
void setUserName(USER user, char newName[]);

/**
* \brief Obtém os amigos do usuário
* @param user Usuário
* @return amigos do usuário
*/
char **getUserFriends (USER user);

/**
* \brief Muda os amigos do usuário
* @param user Usuário
* @param newFriends novos amigos do usuário
*/
void setUserFriends(USER user, char **newFriends);

/**
* \brief Obtém a identificação da review
* @param review Review
* @return identificação da review
*/
char *getReviewId (REVIEW review);

/**
* \brief Muda a identificação da review
* @param review Review
* @param newId nova identificação da review
*/
void setReviewId(REVIEW review, char newId[]);

/**
* \brief Obtém a identificação do usuário
* @param review Review
* @return identificação do usuário
*/
char *getReviewUser (REVIEW review);

/**
* \brief Muda a identificação do usuário
* @param review Review
* @param newUser nova identificação do usuário
*/
void setReviewUser(REVIEW review, char newUser[]);

/**
* \brief Obtém a identificação do negócio
* @param review Review
* @return identificação da negócio
*/
char *getReviewBus (REVIEW review);

/**
* \brief Muda a identificação do negócio
* @param review Review
* @param newBus nova identificação do negócio
*/
void setReviewBus(REVIEW review, char newBus[]);

/**
* \brief Obtém o número de estrelas do negócio
* @param review Review
* @return número de estrelas do negócio
*/
float getReviewStars (REVIEW review);

/**
* \brief Muda o número de estrelas do negócio
* @param review Review
* @param newStars novo número de estrelas do negócio
*/
void setReviewStars(REVIEW review, float newStars);

/**
* \brief Obtém o grau de utilidade do negócio
* @param review Review
* @return grau de utilidade do negócio
*/
int getReviewUseful (REVIEW review);

/**
* \brief Muda o grau de utilidade do negócio
* @param review Review
* @param newUseful novo grau de utilidade do negócio
*/
void setReviewUseful(REVIEW review, int newUseful);

/**
* \brief Obtém o grau de diversão do negócio
* @param review Review
* @return grau de diversão do negócio
*/
int getReviewFunny (REVIEW review);

/**
* \brief Muda o grau de diversão do negócio
* @param review Review
* @param newFunny novo grau de diversão do negócio
*/
void setReviewFunny(REVIEW review, int newFunny);

/**
* \brief Obtém o grau de quão fixe é o negócio
* @param review Review
* @return grau de quão fixe é o negócio
*/
int getReviewCool (REVIEW review);

/**
* \brief Muda o grau de quão fixe é o negócio
* @param review Review
* @param newCool novo grau de quão fixe é o negócio
*/
void setReviewCool(REVIEW review, int newCool);

/**
* \brief Obtém a data de criação do negócio
* @param review Review
* @return data de criação do negócio
*/
char *getReviewDate (REVIEW review);

/**
* \brief Muda a data de criação do negócio
* @param review Review
* @param newDate nova data de criação do negócio
*/
void setReviewDate(REVIEW review, char newDate[]);

/**
* \brief Obtém a review (texto) do negócio
* @param review Review
* @return review do negócio
*/
char *getReviewText (REVIEW review);

/**
* \brief Muda a review (texto) do negócio
* @param review Review
* @param newText nova review do negócio
*/
void setReviewText(REVIEW review, char newText[]);

/************************************************ Leitura e Tratamento dos dados ************************************************/

/**
* \brief Função que faz a leitura do ficheiro e retorna a matriz dinâmica de strings em que cada linha é uma linha do fich
*
* @param info é o array que guarda o conteúdo do ficheiro lido
* @param tmh é o número de linhas que tem o ficheiro (é o tamanho do array de strings, info)
* @param path é o nome do ficheiro
* @return matriz dinâmica
*/
char** lerFichCsv (int* tmh, char path[]);


/**
* \brief Função que converte uma String num BUSINESS
*
* @param info é o array que guarda o conteúdo do ficheiro lido
* @param tmh é o tamanho do array de strings, info
* @param business é o array onde será guardado o conteúdo do ficheiro, mas convertido para structs do tipo BUSINESS
* @return array que guarda o conteúdo do ficheiro lido, convertido para structs do tipo BUSINESS
*/
BUSINESS* transStrToBus(char **info,int *tmh, BUSINESS *business);


/**
* \brief Função que converte uma String num BUSINESS
*
* @param info é o array que guarda o conteúdo do ficheiro lido
* @param tmh é o tamanho do array de strings, info
* @param review é o array onde será guardado o conteúdo do ficheiro, mas convertido para structs do tipo REVIEW
* @return array que guarda o conteúdo do ficheiro lido, convertido para structs do tipo REVIEW
*/
REVIEW* transStrToRev(char **info,int *tmh, REVIEW *review);


/**
* \brief Função que converte uma String num BUSINESS
*
* @param info é o array que guarda o conteúdo do ficheiro lido
* @param tmh é o tamanho do array de strings, info
* @param user é o array onde será guardado o conteúdo do ficheiro, mas convertido para structs do tipo USER
* @return array que guarda o conteúdo do ficheiro lido, convertido para structs do tipo USER
*/
USER* transStrToUsers(char **info,int *tmh, USER *users);


/**
* \brief Função que converte uma String numa TABLE
*
* @param path
* @param hash
* @param funcao
*/
void transStrToTable(char path[],GHashTable* hash ,void* (*funcao) (char info[]),int mode);

void transStructToTable( GHashTable* hash,void**arrStr,char* (*funcao) (void* bus) );

void 
transStructToTableInt( GHashTable* hash,void**arrStr,int (*funcao) (void* bus) );


/**
* \brief Função que preenche os campos da struct do tipo BUSINESS
*
* @param bus é o array que guarda o conteúdo do ficheiro, convertido para structs do tipo BUSINESS
* @param info é o array que guarda o conteúdo do ficheiro lido
*/
BUSINESS addBusiness (char info[]);


/**
* \brief Função que preenche os campos da struct do tipo USER
*
* @param user é o array que guarda o conteúdo do ficheiro, convertido para structs do tipo USER
* @param info é o array que guarda o conteúdo do ficheiro lido
*/
USER addUser ( char info[]);


/**
* \brief Função que preenche os campos da struct do tipo REVIEW
*
* @param rev é o array que guarda o conteúdo do ficheiro, convertido para structs do tipo REVIEW
* @param info é o array que guarda o conteúdo do ficheiro lido
*/
REVIEW addReview ( char info[]);


#endif