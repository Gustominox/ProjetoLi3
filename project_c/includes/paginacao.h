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
typedef struct table{
    char ***variaveis;        
    int numLin;               
    int numLinTotal;         
} *TABLE;


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
* \brief Obtém as variaveis da table
* @param table table
* @return variaveis da table
*/
char** getVariaveis(TABLE table);


/**
* \brief Muda as variaveis da table
* @param table table
* @param newVariaveis novas variaveis 
*/
void setVariaveis(TABLE table, char ***newVariaveis);


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
* \brief Avança para a próxima linha
* @param table table
* @param numLinAtual número de linha atual
*/
void nextLine(TABLE table, int numLinAtual);


/**
* \brief Recua para a linha anterior
* @param table table
* @param numLinAtual número da linha atual
*/
void previousLine(TABLE table, int numLinAtual);


/**
* \brief Imprime uma linha do array de variaveis
* @param variaveis variaveis
*/
void printLinha (char **variaveis);


/**
* \brief Dependendo do comando, avança ou recua na linha
* @param table table 
* @param tecla comando 
*/
void acao(TABLE table, char tecla);

#endif