#ifndef RECURSOS_H
#define RECURSOS_H

#include "data.h"

/*! \brief Função de cadastro de recursos (Variáveis passadas por parâmetro)
    * \param cab_recurso Cabeça da lista encadeada dos recursos
    * \param id ID do recurso (lido anteriormente)
    * \param tipo Tipo do recurso (1 - sala | 2 - Computador | 3 - Armário) (lido anteriormente)
    * \param estado Variavel que guarda o estado do recurso (0 - Disponível | 1 - Ocupado)
    * \param aluno Variavel que guarda o ID do aluno (Se o recurso estiver emprestado) (usado na importação)
    * \return Retorna 0 se o cadastro for efetuado com sucesso ou 1 se houve algum erro (ex: ID repetido)
    */
int cadastra_recurso(struct recursos **cab_recurso,int *id,int *tipo,int *estado,int *aluno);

/*! \brief Função de busca de recursos por id
    * \param cab_recurso Cabeça da lista encadeada dos recursos
    * \param id ID do recurso (lido anteriormente)
    * \param tipo Tipo do recurso (1 - sala | 2 - Computador | 3 - Armário) (lido anteriormente)
    * \param estado Variavel que guarda o estado do recurso (0 - Disponível | 1 - Ocupado)
    * \param aluno Variavel que guarda o ID do aluno (Se o recurso estiver emprestado) (usado na importação)
    * \return Retorna o ponteiro do recurso (p) caso seja encontrado. Se remover == 1, Retorna o ANT (pr) para possibilitar a remoção
    */
struct recursos *busca_recurso_id(struct recursos **cab_recurso,int id);

/*! \brief Função de listar recursos (Percorre a lista encadeada até o final imprimindo as informações de cada recurso)
    * \param cab_recurso Cabeça da lista encadeada dos recursos
    * \param vetaluno Vetor de alunos
    * \return Retorna NULO
    */
void lista_recurso(struct recursos **cab_recurso,struct alunos **vetaluno);

/*! \brief Função de remover recursos (Usa a função de busca retornando o ANT do recurso e efetua a remoção)
    * \param cab_recurso Cabeça da lista encadeada dos recursos
    * \param vetaluno Vetor de alunos
    * \return Retorna NULO
    */
void remove_recurso(struct recursos **cab_recurso,struct alunos **vetaluno);

/*! \brief Função de emprestar recursos (Verifica se o recurso e o aluno existem e se o recurso ainda não está emprestado e confirma o empréstimo)
    * \param cab_recurso Cabeça da lista encadeada dos recursos
    * \param vetaluno Vetor de alunos
    * \param a Contador dos alunos
    * \return Retorna NULO
    */
void ocupa_recurso(struct recursos **cab_recurso,struct alunos **vetaluno,int *a);

/*! \brief Função de devolver recursos (Verifica se o recurso existe e se está emprestado e confirma a devolução)
    * \param cab_recurso Cabeça da lista encadeada dos recursos
    * \param vetaluno Vetor de alunos
    * \param a Contador dos alunos
    * \return Retorna NULO
    */
void desocupa_recurso(struct recursos **cab_recurso,struct alunos **vetaluno,int *a);

#endif
