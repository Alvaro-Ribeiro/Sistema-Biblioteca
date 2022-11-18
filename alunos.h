#ifndef ALUNOS_H
#define ALUNOS_H

#include "data.h"
/*! \brief Função de cadastro de aluno (Variáveis passadas por parâmetro)
    * \param vetaluno Vetor de alunos
    * \param a Contador dos alunos
    * \param nome Nome do aluno (lido anteriormente)
    * \param matricula Matricula do aluno (lido anteriormente)
    * \param pendencia Variavel que guarda a quantidade de pendencias do aluno
    * \param recursos Vetor que guarda quantos recursos de cada tipo o aluno tem (usado para limitar os empréstimos)
    * \param ra Variável que guarda a quantidade de blocos de malloc criados (vetor começa com 64 pos. e vai aumentando conforme enche)
    * \param null Variável que verifica (na importação de arquivo) se o aluno foi removido para contagem correta do ID
    * \return Retorna 0 se o cadastro for efetuado com sucesso ou 1 se houve algum erro (ex: Matrícula repetida)
    */
int cadastra_aluno(struct alunos ***vetaluno,int *a,char *nome,char *matricula,int *pendencia,int *recursos,int *ra,int null);

/*! \brief Função de busca de aluno por ID
    * \param vetaluno Vetor de alunos
    * \param a Contador dos alunos
    * \param ID ID do aluno
    * \return Retorna -1 se a busca não encontrou o aluno ou o ID do aluno caso tenha sido encontrado
    */
int busca_aluno(struct alunos **vetaluno,int *a,int id);

/*! \brief Função de remoção de aluno (Verifica se o aluno existe e se ele nao tem pendencias e depois confirma a remoção)
    * \param vetaluno Vetor de alunos
    * \param a Contador dos alunos
    * \param ID ID do aluno
    * \return Retorna NULO
    */
void remove_aluno(struct alunos **vetaluno,int *a,int id);

/*! \brief Função de listar alunos (Percorre o vetor imprimindo as informações dos alunos (se vetoralunos[i] != NULL))
    * \param vetaluno Vetor de alunos
    * \param a Contador dos alunos
    * \return Retorna NULO
    */
void lista_aluno(struct alunos **vetaluno,int *a);

#endif
