#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "data.h"
#include "prints.h"

int cadastra_aluno(struct alunos ***vetaluno,int *a,char *nome,char *matricula,int *pendencia,int *recursos,int *ra,int null){
    (*a)++;
    if((*a) > (64 * (*ra))){//Verifica se o vetor encheu para alocar mais posições
        (*ra)++;
        (*vetaluno) = realloc((*vetaluno),sizeof((64 * (*ra))*sizeof(struct alunos *)));
    }
    if(null == 1){//Trata os alunos que foram removidos
        (*vetaluno)[(*a)-1] = NULL;
        return 0;
    }
    //Verifica matrículas repetidas, aloca espaço e adiciona o aluno no vetor
    (*vetaluno)[(*a)-1] = malloc(sizeof(struct alunos));
    for(int i=0;i<(*a)-1;i++){
        if(((*vetaluno)[i] != NULL) && (strcmp(matricula,(*vetaluno)[i]->matricula)) == 0){
            printf("\nMatrícula já encontrada no cadastro do aluno de ID %d\n\n",i);
            (*a)--;
            return 1;
        }
    }
    int tam_nome = strlen(nome);
    int tam_matricula = strlen(matricula);
    for(int i=0;i<tam_nome;i++){
        (*vetaluno)[(*a)-1]->nome[i] = nome[i];
    }
    (*vetaluno)[(*a)-1]->nome[tam_nome] = '\0';
    for(int i=0;i<tam_matricula;i++){
        (*vetaluno)[(*a)-1]->matricula[i] = matricula[i];
    }
    (*vetaluno)[(*a)-1]->matricula[tam_matricula] = '\0';
    (*vetaluno)[(*a)-1]->id = (*a)-1;
    (*vetaluno)[(*a)-1]->pendencia = (*pendencia);
    for(int i=0;i<3;i++){
        (*vetaluno)[(*a)-1]->recursos[i] = recursos[i];
    }

    return 0;
}

int busca_aluno(struct alunos **vetaluno,int *a,int id){
    if((id > (*a)-1 || id < 0) || vetaluno[id] == NULL){//Verifica se o aluno é válido
        printf("\nID inválido. Aluno não cadastrado\n\n");
        return -1;
    }
    return id;
}

void remove_aluno(struct alunos **vetaluno,int *a,int id){
    //Verifica se o aluno é válido. Se for, remove.
    int rec = busca_aluno(vetaluno,a,id);
    if(rec==-1){
        return;
    }
    print_busca_alunos(vetaluno,id);
    if(vetaluno[id]->pendencia > 0){
        printf("\nEsse aluno tem %d pendências com a biblioteca, portanto não é possível removê-lo do sistema no momento\n\n", vetaluno[id]->pendencia);
        return;
    }
    printf("\nConfirma a remoção desse aluno ?\nSe sim, digite 1. Caso contrário, digite 2: ");
    scanf("%d",&rec);
    if(rec == 1){
        free(vetaluno[id]);
        vetaluno[id] = NULL;
        printf("\nAluno removido com sucesso.\n\n");
        return;
    }
    printf("\nOperação cancelada\n\n");
    return;
}

void lista_aluno(struct alunos **vetaluno,int *a){
    int cont = 0;
    for(int i=0;i<(*a);i++){//Verifica se o aluno foi removido (NULL) e printa as informações
        if(vetaluno[i] != NULL){
            printf("ID: %d",i);
            print_busca_alunos(vetaluno,i);
            //printf("\n");
            cont++;
        }
    }
    if(cont == 0)//Verifica se nao tem nenhum aluno cadastrado
        printf("\nNenhum aluno cadastrado no sistema\n\n");
}
