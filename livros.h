#ifndef LIVROS_H
#define LIVROS_H

#include "data.h"
/*! \brief Função de cadastro de livros (Variáveis passadas por parâmetro)
    * \param vetlivros Vetor de livros
    * \param l Contador dos livros
    * \param nome Nome do livro (lido anteriormente)
    * \param data Data de pub. do livro (lido anteriormente)
    * \param categoria Categoria do livro (lido anteriormente)
    * \param estado Estado do livro (emprestado ou disponível)
    * \param aluno ID do aluno (caso esteja emprestado)
    * \param rl Variável que guarda a quantidade de blocos de malloc criados (vetor começa com 64 pos. e vai aumentando conforme enche)
    * \param null Variável que verifica (na importação de arquivo) se o livro foi removido para contagem correta do ID
    * \return Retorna NULO
    */
void cadastra_livro(struct livros ***vetlivros,int *l,char *nome,int *data,char *categoria,int *estado, int *aluno,int *rl,int null);

/*! \brief Função de busca de livro por ID (pesq == 1) ou por categoria (pesq == 2)
    * \param vetlivros Vetor de livros
    * \param vetalunos Vetor de alunos
    * \param l Contador dos livros
    * \param pesq Variável que guarda se a busca é por ID ou categoria (1 ou 2)
    * \return Retorna NULO
    */
void busca_livro(struct livros **vetlivros,struct alunos **vetaluno,int *l,int pesq);

/*! \brief Função de empréstimo de livros (Verifica se o livro e o aluno são válidos e depois confirma o empréstimo)
    * \param vetlivros Vetor de livros
    * \param l Contador dos livros
    * \param vetalunos Vetor de alunos
    * \param a Contador dos Alunos
    * \return Retorna NULO
    */
void empresta_livro(struct livros **vetlivros,int *l,struct alunos **vetaluno,int *a);

/*! \brief Função de devolução de livros (Verifica se o livro realmente está emprestado e depois confirma a devolução)
    * \param vetlivros Vetor de livros
    * \param l Contador dos livros
    * \param vetalunos Vetor de alunos
    * \return Retorna NULO
    */
void devolve_livro(struct livros **vetlivros,int *l,struct alunos **vetaluno);

/*! \brief Função de remoção de livros (Verifica se o livro existe e se ele não está emprestado e depois confirma a remoção)
    * \param vetlivros Vetor de livros
    * \param l Contador dos livros
    * \param vetalunos Vetor de alunos
    * \return Retorna NULO
    */
void remove_livro(struct livros **vetlivros,int *l,struct alunos **vetaluno);

/*! \brief Função de listar livros (Percorre o vetor imprimindo as informações dos livros (se vetorlivros[i] != NULL))
    * \param vetlivros Vetor de livros
    * \param l Contador dos livros
    * \param vetalunos Vetor de alunos
    * \return Retorna NULO
    */
void lista_livro(struct livros **vetlivros,int *l,struct alunos **vetaluno);

#endif
