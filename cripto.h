#ifndef CRIPTO_H
#define CRIPTO_H

#include "data.h"

/*! \brief Função que criptografa o arquivo .txt (Cifra de César)
    * \param entrada Ponteiro pro arquivo .txt de entrada
    * \param k chave da criptografia
    * \return Retorna NULO
    */
void cripto(FILE **entrada,int k);

/*! \brief Função que descriptografa o arquivo .txt (Cifra de César)
    * \param saida Ponteiro pro arquivo .txt de saida
    * \param k chave da criptografia
    * \return Retorna NULO
    */
void descripto(FILE **saida,int k);

#endif
