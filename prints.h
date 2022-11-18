#ifndef PRINTS_H
#define PRINTS_H

#include "data.h"
//--------------------------Alunos--------------------------//

/*! \brief Função que imprime as opções do Menu Principal
    * \return Retorna NULO
    */
void print_menu();

/*! \brief Função que imprime as opções do Menu de Alunos
    * \return Retorna NULO
    */
void print_menu_alunos();

/*! \brief Função que lê as informações do aluno para cadastro
    * \param nome Nome do aluno
    * \param matricula Matricula do aluno
    * \return Retorna NULO
    */
void print_cad_alunos(char *nome,char *matricula);

/*! \brief Função imprime as informações do aluno a partir de seu ID
    * \param vetaluno Vetor de alunos
    * \param id ID do aluno
    * \return Retorna NULO
    */
void print_busca_alunos(struct alunos **vetaluno,int id);

//--------------------------Livros--------------------------//

/*! \brief Função que imprime as opções do Menu de Livros
    * \return Retorna NULO
    */
void print_menu_livros();

/*! \brief Função que lê as informações do livro para cadastro
    * \param nome Nome do livro
    * \param data Ano de publicação do livro
    * \param categoria Categoria do livro
    * \return Retorna NULO
    */
void print_cad_livros(char *nome, int *data, char *categoria);

/*! \brief Função imprime as informações do livro a partir de seu ID
    * \param vetlivros Vetor de livros
    * \param id ID do livro
    * \param vetaluno Vetor de alunos
    * \return Retorna NULO
    */
void print_busca_livros(struct livros **vetlivros,int id,struct alunos **vetaluno);

//--------------------------Recursos--------------------------//

/*! \brief Função que imprime as opções do Menu de Recursos
    * \return Retorna NULO
    */
void print_menu_recursos();

/*! \brief Função que lê as informações do recurso para cadastro
    * \param id ID do recurso
    * \param tipo Tipo do recurso (1 - Sala | 2 - Computador | 3 - Armário)
    * \return Retorna NULO
    */
void print_cad_recursos(int *id,int *tipo);

/*! \brief Função imprime as informações do recurso a partir de seu ponteiro de struct
    * \param pontr Ponteiro para o recurso
    * \param vetaluno Vetor de alunos
    * \param id ID do aluno
    * \return Retorna 1 se o ponteiro não for válido. Caso contrário, Retorna 0 e imprime as informações do recurso
    */
int print_busca_recursos(struct recursos **pontr,struct alunos **vetaluno,int id);

#endif
