#ifndef DATA_H
#define DATA_H

/*! \struct alunos
 * \brief Struct para guardar as informações dos alunos
 * \var alunos::nome
 * 'nome' é uma string que guarda o nome do aluno
 * \var alunos::matricula
 * 'matricula' é uma string que guarda a matricula do aluno
 * \var alunos::recursos
 * 'recursos' é um vetor que guarda quantos recursos de cada tipo o aluno já pegou emprestado (usado pra limitar os empréstimos)
 * \var alunos::id
 * 'id' é um int que guarda o ID do aluno
 * \var alunos::pendencia
 * 'pendencia' é um int que guarda o número de pendencias do aluno com a biblioteca
 */
struct alunos{
    char nome[51];
    char matricula[12];
    int recursos[3];
    int id;
    int pendencia; //0 - Sem pendencias | != 0 - Com pendencias
};

/*! \struct livros
 * \brief Struct para guardar as informações dos livros
 * \var livros::nome
 * 'nome' é uma string que guarda o nome do livro
 * \var livros::categoria
 * 'categoria' é uma string que guarda a categoria do livro
 * \var livros::data
 * 'data' é um int que guarda o ano de pub. do livro
 * \var livros::id
 * 'id' é um int que guarda o ID do livro
 * \var livros::estado
 * 'estado' é um int que guarda o estado do livro (0 - Disponível | 1 - Emprestado)
 * \var livros::aluno
 * 'aluno' é um int que guarda o ID do aluno (caso o livro esteja emprestado)
 */
struct livros{
    char nome[51];
    char categoria[21];
    int data;
    int id;
    int estado;// 0 = Disponível | 1 = Emprestado
    int aluno;
};

/*! \struct recursos
 * \brief Struct para guardar as informações dos recursos
 * \var recursos::id
 * 'id' é um int que guarda o ID do recurso
 * \var recursos::tipo
 * 'tipo' é um int que guarda o tipo do recurso (1 - Sala | 2 - Computador | 3 - Armário)
 * \var recursos::estado
 * 'estado' é um int que guarda o estado do recurso (0 - Disponível | 1 - Emprestado)
 * \var recursos::aluno
 * 'aluno' é um int que guarda o ID do aluno (caso o recurso esteja emprestado)
 * \var recursos::prox
 * 'prox' é um ponteiro pra struct recursos que serve pra apontar para o próximo item na lista encadeada de recursos
 */
struct recursos{
    int id;
    int tipo;// 1 = Sala | 2 = Computador | 3 = Armário
    int estado;// 0 = Disponível | 1 = Emprestado
    int aluno;
    struct recursos *prox;
};

#endif
