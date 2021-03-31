#include <stdio.h>
#include <stdlib.h>

/*
typedef struct cidade{
	char **referencias;
} *CIDADE; 
*/
typedef struct business{
	char *business_id;
	char *name;
	char *city;
	float state;
	int categories;
} *BUSINESS; 
// estou a criar um tipo de dados de business e este business já é um apontador.


typedef struct user{
	char *id;
	char *name;
	char *friends;
} *USER;
// estou a criar um tipo de dados de user e este user já é um apontador.


typedef struct review{
	char *review_id;
	char *user_id;
	char *business_id;
	float stars;
	int useful;
	int funny;
	int cool;
	//char *date; ////////////////// char ?????????????????????
	//char *text;
} *REVIEW;
// estou a criar um tipo de dados de review e este review já é um apontador.


/**
* \brief Função que faz a leitura do ficheiro e o guarda o seu conteúdo
*
* @param info é o array que guarda o conteúdo do ficheiro lido
* @param tmh é o número de linhas que tem o ficheiro (é o tamanho do array de strings, info)
* @param path é o nome do ficheiro
*/
char** lerFichCsv (char **info, int* tmh, char path[]);


/**
* \brief Função que converte uma String num BUSINESS
*
* @param info é o array que guarda o conteúdo do ficheiro lido
* @param tmh é o tamanho do array de strings, info
* @param business é o array onde será guardado o conteúdo do ficheiro, mas convertido para structs do tipo BUSINESS
*/
BUSINESS* transStrToBus(char **info,int tmh, BUSINESS *business);


/**
* \brief Função que converte uma String num BUSINESS
*
* @param info é o array que guarda o conteúdo do ficheiro lido
* @param tmh é o tamanho do array de strings, info
* @param review é o array onde será guardado o conteúdo do ficheiro, mas convertido para structs do tipo REVIEW
*/
REVIEW* transStrToRev(char **info,int tmh, REVIEW *review);


/**
* \brief Função que converte uma String num BUSINESS
*
* @param info é o array que guarda o conteúdo do ficheiro lido
* @param tmh é o tamanho do array de strings, info
* @param user é o array onde será guardado o conteúdo do ficheiro, mas convertido para structs do tipo USER
*/
USER* transStrToUsers(char **info,int tmh, USER *users);


/**
* \brief Função que preenche os campos da struct do tipo USER
*
* @param user é o array que guarda o conteúdo do ficheiro, convertido para structs do tipo USER
* @param info é o array que guarda o conteúdo do ficheiro lido
*/
USER addUser (USER user, char info[]);


/**
* \brief Função que preenche os campos da struct do tipo BUSINESS
*
* @param bus é o array que guarda o conteúdo do ficheiro, convertido para structs do tipo BUSINESS
* @param info é o array que guarda o conteúdo do ficheiro lido
*/
BUSINESS addBusiness (BUSINESS bus, char info[]);


/**
* \brief Função que preenche os campos da struct do tipo REVIEW
*
* @param rev é o array que guarda o conteúdo do ficheiro, convertido para structs do tipo REVIEW
* @param info é o array que guarda o conteúdo do ficheiro lido
*/
REVIEW addReview (REVIEW rev, char info[]);


/**
* \brief Função que converte o array da struct do tipo REVIEW num array de strings
*
* @param rev é o array que guarda o conteúdo do ficheiro, convertido para structs do tipo REVIEW
*/
char *reviewToString(REVIEW rev);
