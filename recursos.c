#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "data.h"
#include "prints.h"

struct recursos *busca_recurso_id(struct recursos **cab_recurso,int id,int remover){
    struct recursos *p = (*cab_recurso)->prox;
    if((*cab_recurso)->prox == NULL){
        p = NULL;
        return p;
    }
    struct recursos *pr = (*cab_recurso);
    while(p->prox != NULL && p->id != id){
        pr = p;
        p = p->prox;
    }
    if(remover == 1){
        return pr;
    }
    return p;

}

int cadastra_recurso(struct recursos **cab_recurso,int *id,int *tipo,int *estado,int *aluno){
    struct recursos *p = busca_recurso_id(cab_recurso,*id,0);
    if(p!= NULL && p->id == *id){
        //printf("\nRecurso com ID %d já cadastrado no sistema.\n\n",id);
        return 1;
    }
    struct recursos *pr = malloc(sizeof(struct recursos));
    pr->prox = (*cab_recurso)->prox;
    (*cab_recurso)->prox = pr;
    pr->id = *id;
    pr->tipo = *tipo;
    pr->estado = (*estado);
    pr->aluno = (*aluno);
    return 0;
}

void lista_recurso(struct recursos **cab_recurso,struct alunos **vetaluno){
    if((*cab_recurso)->prox == NULL){
        printf("\nNenhum recurso cadastrado no sistema.\n\n");
    }
    struct recursos *p = (*cab_recurso)->prox;
    while(p != NULL){
        print_busca_recursos(&p,vetaluno,p->id);
        p = p->prox;
    }
    printf("\n");
}

void remove_recurso(struct recursos **cab_recurso,struct alunos **vetaluno){
    int id;
    printf("Digite o ID do recurso que deseja remover: ");
    scanf("%d",&id);
    struct recursos *p = busca_recurso_id(cab_recurso,id,1);
    int a = print_busca_recursos(&(p->prox),vetaluno,id);
    if(a == 1){
        return;
    }
    if(p->prox->estado == 1){
        printf("\nImpossível remover esse recurso, pois está emprestado para o aluno de matrícula %s\n",vetaluno[p->aluno]->matricula);
        return;
    }
    printf("\nDeseja confirmar a remoção do recurso acima ?\n Se sim, digite 1. Caso contrário, digite 2: ");
    scanf("%d",&id);
    if(id == 1){
        struct recursos *pont = p->prox;
        p->prox = pont->prox;
        free(pont);
        printf("\nRecurso removido com sucesso\n\n");
        return;
    }
    printf("\nOperação cancelada\n\n");
    return;
}

void ocupa_recurso(struct recursos **cab_recurso,struct alunos **vetaluno,int *a){
    int id,id2;
    printf("Digite o ID do recurso que deseja emprestar: ");
    scanf("%d",&id);
    struct recursos *p = busca_recurso_id(cab_recurso,id,0);
    if(p==NULL || p->id != id){
        printf("\nRecurso de ID '%d' não cadastrado no sistema.\n\n",id);
        return;
    }
    if(p->estado == 1){
        printf("Esse recurso já se encontra emprestado para o aluno de matrícula %s",vetaluno[p->aluno]->matricula);
        return;
    }
    printf("Digite o ID do aluno para quem deseja emprestar o recurso: ");
    scanf("%d",&id2);
    if(id2 > (*a)-1){
        printf("\nAluno não existente no sistema.\n\n");
        return;
    }
    if(vetaluno[id2] == NULL){
        printf("\nAluno não existente no sistema.\n\n");
        return;
    }
    if(vetaluno[id2]->recursos[(p->tipo)-1] == 1){
        printf("\nEsse aluno já está ocupando um recurso desse tipo.\n\n");
        return;
    }
    print_busca_recursos(&p,vetaluno,id);
    print_busca_alunos(vetaluno,id2);
    printf("\nConfirma o empréstimo do recurso ?\nSe sim, digite 1. Caso contrário, digite 2: ");
    scanf("%d",&id);
    if(id == 1){
        vetaluno[id2]->recursos[(p->tipo)-1] = 1;
        vetaluno[id2]->pendencia += 1;
        p->aluno = id2;
        p->estado = 1;
        printf("\nRecurso atribuído com sucesso\n\n");
        return;
    }
    printf("\nOperação cancelada\n\n");
    return;
}

void desocupa_recurso(struct recursos **cab_recurso,struct alunos **vetaluno,int *a){
    int id,aux;
    printf("Digite o ID do recurso que deseja desocupar: ");
    scanf("%d",&id);
    struct recursos *p = busca_recurso_id(cab_recurso,id,0);
    if(p==NULL || p->id != id){
        printf("\nRecurso de ID '%d' não cadastrado no sistema.\n\n",id);
        return;
    }
    if(p->estado == 0){
        printf("\nEsse recurso não se encontra emprestado para nenhum aluno no momento\n\n");
        return;
    }
    print_busca_recursos(&p,vetaluno,id);
    printf("\nDeseja realmente desocupar esse recurso?\nSe sim, digite 1. Caso contrário, digite 2: ");
    scanf("%d",&aux);
    if(aux == 1){
        p->estado = 0;
        vetaluno[p->aluno]->pendencia -= 1;
        vetaluno[p->aluno]->recursos[(p->tipo)-1] = 0;
        printf("\nRecurso desocupado com sucesso\n\n");
        return;
    }
    printf("\nOperação cancelada\n\n");
    return;
}
