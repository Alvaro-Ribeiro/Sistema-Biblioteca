#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "data.h"
#include "prints.h"

void cadastra_livro(struct livros ***vetlivros,int *l, char *nome,int *data,char *categoria,int *estado,int *aluno,int *rl,int null){
    (*l)++;
    if((*l) > (64 * (*rl))){//Verifica se o vetor encheu para alocar mais posições
        (*rl)++;
        (*vetlivros) = realloc((*vetlivros),sizeof((64 * (*rl))*sizeof(struct livros *)));
    }
    if(null == 1){//Trata os livros que foram removidos
        (*vetlivros)[(*l)-1] = NULL;
        return;
    }
    //Aloca espaço e adiciona o livro no vetor
    (*vetlivros)[(*l)-1] = malloc(sizeof(struct livros));

    (*vetlivros)[(*l)-1]->id = (*l)-1;
    (*vetlivros)[(*l)-1]->estado = (*estado);
    int tam_nome = strlen(nome),tam_cat = strlen(categoria);
    for(int i = 0;i < tam_nome; i++){
        (*vetlivros)[(*l)-1]->nome[i] = nome[i];
    }
    (*vetlivros)[(*l)-1]->nome[tam_nome] = '\0';
    for(int i = 0;i < tam_cat; i++){
        (*vetlivros)[(*l)-1]->categoria[i] = categoria[i];
    }
    (*vetlivros)[(*l)-1]->categoria[tam_cat] = '\0';
    (*vetlivros)[(*l)-1]->data = *data;
    (*vetlivros)[(*l)-1]->aluno = *aluno;

}

void busca_livro(struct livros **vetlivros,struct alunos **vetaluno,int *l,int pesq){
    if(pesq == 1){//busca por ID
        int id;
        printf("Digite o ID do livro que deseja buscar: ");
        scanf("%d",&id);
        if(((id > (*l)) || ((id < 0))) || (vetlivros[id] == NULL) ){
            printf("\nID inválido. Livro não cadastrado.\n\n");
            return;
        }
        print_busca_livros(vetlivros,id,vetaluno);
        printf("\n");
    }
    else if(pesq == 2){//busca por categoria
        int cont = 0;
        char cat[21];
        printf("\nDigite a categoria que deseja buscar: ");
        __fpurge(stdin);
        fgets(cat,21,stdin);
        strtok(cat,"\n");
        printf("\n");
        printf("Livros da categoria %s: \n",cat);
        for(int i = 0;i < (*l); i++){
            if(vetlivros[i] != NULL && strcmp(cat,vetlivros[i]->categoria) == 0){
                print_busca_livros(vetlivros,i,vetaluno);
                cont++;
            }
        }
        if(cont == 0){
            printf("\nNenhum livro dessa categoria encontrado\n");
        }
        printf("\n");
    }

}

void empresta_livro(struct livros **vetlivros,int *l,struct alunos **vetaluno,int *a){
    int id,aux,aux2;
    printf("Digite o ID do livro que deseja emprestar: ");
    scanf("%d",&id);
    if((id > (*l)-1 || id < 0) || (vetlivros[id] == NULL)){
        printf("\nID inválido. Livro não cadastrado\n\n");
        return;
    }
    if(vetlivros[id]->estado == 1){
        printf("\nLivro já se encontra emprestado para o aluno de matrícula %s\n\n",vetaluno[vetlivros[id]->aluno]->matricula);
        return;
    }
    printf("Digite o ID do aluno para o qual deseja emprestar o livro: ");
    scanf("%d",&aux);
    if((aux > (*a) || aux < 0) || (vetaluno[aux] == NULL)){
        printf("\nID inválido. Aluno não cadastrado\n\n");
        return;
    }
    printf("\nLivro:\n");
    print_busca_livros(vetlivros,id,vetaluno);
    printf("\nAluno:\n");
    print_busca_alunos(vetaluno,aux);
    printf("Deseja confirmar o empréstimo do livro ?\nSe sim, digite 1. Caso contrário, digite 2: ");
    scanf("%d",&aux2);
    printf("\n");
    if(aux2 == 1){
        vetlivros[id]->estado = 1;
        vetlivros[id]->aluno = aux;
        vetaluno[aux]->pendencia += 1;
        printf("Empréstimo efetuado com sucesso\n\n");
        return;
    }
    printf("Operação cancelada\n\n");
    return;
}

void devolve_livro(struct livros **vetlivros,int *l,struct alunos **vetaluno){
    int id,aux;
    printf("Digite o ID do livro que deseja devolver: ");
    scanf("%d",&id);
    if((id > (*l)-1 || id < 0) || (vetlivros[id] == NULL)){
        printf("\nID inválido. Livro não cadastrado\n\n");
        return;
    }
    if(vetlivros[id]->estado == 1){
        printf("\nInformações do Livro:\n");
        print_busca_livros(vetlivros,id,vetaluno);
        printf("\nDeseja confirmar a devolução do livro ?\nSe sim, digite 1. Caso contrário, digite 2: ");
        scanf("%d",&aux);
        printf("\n");
        if(aux == 1){
            vetlivros[id]->estado = 0;
            vetaluno[vetlivros[id]->aluno]->pendencia -= 1;
            printf("Devolução lançada com sucesso.\n\n");
            return;
        }
        printf("Operação cancelada\n\n");
        return;
    }
    printf("\nO livro de ID %d não se encontra emprestado para nenhum aluno.\n\n",id);
    return;
}

void remove_livro(struct livros **vetlivros,int *l,struct alunos **vetaluno){
    int id,aux;
    printf("Digite o ID do livro que deseja remover: ");
    scanf("%d",&id);
    if(((id > (*l)) || ((id < 0))) || (vetlivros[id] == NULL)){
        printf("\nID inválido. Livro não cadastrado.\n\n");
        return;
    }
    printf("\n");
    print_busca_livros(vetlivros,id,vetaluno);
    if(vetlivros[id]->estado == 1){
        printf("\nImpossível remover o livro do sistema, pois se encontra emprestado no momento\n\n");
        return;
    }
    printf("\nConfirma a remoção desse livro ?\n Se sim, digite 1. Caso contrário, digite 2: ");
    scanf("%d",&aux);
    if(aux == 1){
        free(vetlivros[id]);
        vetlivros[id] = NULL;
        printf("\nLivro removido com sucesso\n\n");
        return;
    }
    printf("\nOperação cancelada\n\n");
    return;
}

void lista_livro(struct livros **vetlivros,int *l,struct alunos **vetaluno){
    int cont=0;
    for(int i=0;i<(*l);i++){
        if(vetlivros[i]!=NULL){
            print_busca_livros(vetlivros,i,vetaluno);
            cont++;
        }
    }
    if(cont==0){
        printf("Nenhum livro cadastrado no sistema\n");
    }
    printf("\n");
}
