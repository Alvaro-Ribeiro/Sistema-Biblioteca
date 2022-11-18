#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "data.h"

void print_menu(){
    printf("1 | Acessar seção de alunos\n");
    printf("2 | Acessar seção de livros\n");
    printf("3 | Acessar seção de recursos\n");
    printf("0 | Finalizar o programa\n");
}

void print_menu_alunos(){
    printf("1 | Efetuar cadastro de um novo aluno\n");
    printf("2 | Visualizar dados de um aluno\n");
    printf("3 | Remover aluno do sistema\n");
    printf("4 | Listar alunos cadastrados\n");
    printf("5 | Voltar ao Menu Principal\n");
}

void print_cad_alunos(char *nome,char *matricula){
    printf("Digite o nome do aluno: ");
    __fpurge(stdin);
    fgets(nome,51,stdin);
    printf("Digite a matrícula do aluno: ");
    __fpurge(stdin);
    fgets(matricula,12,stdin);
    strtok(nome,"\n");
    strtok(matricula,"\n");
}

void print_busca_alunos(struct alunos **vetaluno,int id){
    printf("\nNome: %s\n",vetaluno[id]->nome);
    printf("Matrícula: %s\n",vetaluno[id]->matricula);
    if(vetaluno[id]->pendencia == 0){
        printf("OBS: Aluno sem pendências com a biblioteca!\n");
    }
    else{
        printf("OBS: Aluno possui %d pendências com a biblioteca!\n",vetaluno[id]->pendencia);
    }
    printf("\n");
}

void print_menu_livros(){
    printf("1 | Efetuar cadastro de um novo livro\n");
    printf("2 | Visualizar situação de um livro\n");
    printf("3 | Efetuar empréstimo de um livro\n");
    printf("4 | Efetuar devolução de um livro\n");
    printf("5 | Remover livro do sistema\n");
    printf("6 | Listar livros cadastrados\n");
    printf("7 | Voltar ao Menu Principal\n");
}

void print_cad_livros(char *nome, int *data, char *categoria){
    int cont = 0;
    printf("Digite o nome do livro:");
    __fpurge(stdin);
    fgets(nome,51,stdin);
    strtok(nome,"\n");
    printf("Digite o ano de publicação do livro no formato AAAA: ");
    scanf("%d",data);
    printf("Digite a categoria do livro: ");
    __fpurge(stdin);
    fgets(categoria,21,stdin);
    strtok(categoria,"\n");
}

void print_busca_livros(struct livros **vetlivros,int id,struct alunos **vetaluno){
    printf("ID do livro: %d\n",id);
    printf("Nome do livro: %s\n",vetlivros[id]->nome);
    printf("Data de publicação: %d\n",vetlivros[id]->data);
    printf("Categoria: %s\n",vetlivros[id]->categoria);
    if(vetlivros[id]->estado == 0){
        printf("Estado: Disponível\n");
    }
    else{
        printf("Estado: Emprestado para o aluno de matrícula: %s\n",vetaluno[(vetlivros[id]->aluno)]->matricula);
    }
}

void print_menu_recursos(){
    printf("1 | Efetuar cadastro de um novo recurso\n");
    printf("2 | Visualizar situação de um recurso\n");
    printf("3 | Efetuar empréstimo de um recurso\n");
    printf("4 | Efetuar devolução de um recurso\n");
    printf("5 | Remover recurso do sistema\n");
    printf("6 | Listar recursos cadastrados\n");
    printf("7 | Voltar ao Menu Principal\n");
}

void print_cad_recursos(int *id,int *tipo){
    printf("Digite o ID para o recurso que quer cadastrar: ");
    scanf("%d",id);
    printf("Digite o tipo de recurso (1 para sala, 2 para computador ou 3 para armário): ");
    scanf("%d",tipo);
}

int print_busca_recursos(struct recursos **pontr,struct alunos **vetaluno,int id){
    if((*pontr) == NULL || (*pontr)->id != id){
        printf("\nRecurso não cadastrado no sistema.\n\n");
        return 1;
    }
    printf("\nID do recurso: %d\n",id);
    if((*pontr)->tipo == 1){
        printf("Tipo de recurso: Sala\n");
    }
    else if((*pontr)->tipo == 2){
        printf("Tipo de recurso: Computador\n");
    }
    else if((*pontr)->tipo == 3){
        printf("Tipo de recurso: Armário\n");
    }
    if((*pontr)->estado == 0){
        printf("Estado: disponível\n");
    }
    else{
        printf("Estado: emprestado para o aluno de matrícula %s\n",vetaluno[(*pontr)->aluno]->matricula);
    }
    return 0;
}
