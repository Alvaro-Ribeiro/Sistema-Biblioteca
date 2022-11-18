#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include <unistd.h>
#include "data.h"
#include "alunos.h"
#include "livros.h"
#include "recursos.h"
#include "cripto.h"
#include "prints.h"

int main(){
    struct alunos **vetaluno = (struct alunos **)malloc(64 * sizeof(struct alunos *));//Vetor de alunos
    struct livros **vetlivros = (struct livros **)malloc(64 * sizeof(struct livros *));//Vetor de livros
    struct recursos *cab_recurso = malloc(sizeof(struct recursos));//Cabeça da Lista enc. de recursos
    cab_recurso->prox=NULL;
    int recursos[3] = {0,0,0};
    int a=0,l=0,ra=1,rl=1,null=0,pendencia=0,data,aux,id,tipo,estado,aluno,rec;// Contadores e
    char nome[51],nome2[51],matricula[12],categoria[21],lixo[2],c;// variáveis auxiliares

    //-----Importação-----//

    FILE *entrada;
    if(access("db.txt",F_OK) == 0){//Descriptografar
        entrada = fopen("db.txt","r+");
        descripto(&entrada,5);
        fclose(entrada);
    }

    if(access("db.txt",F_OK) == 0){//Importar dados
        entrada = fopen("db.txt","r");
        fscanf(entrada,"%c",&c);
        while(c!='&'){//Importar alunos
            fseek(entrada,-1,SEEK_CUR);
            fscanf(entrada,"%[^|]",nome);
            if(strcmp(nome,"*") != 0){
                null = 0;
                fscanf(entrada, "|%[^|]|%d |%d |%d |%d\n", matricula, &pendencia,&recursos[0],&recursos[1],&recursos[2]);
            }else{
                null = 1;
                fscanf(entrada, "|\n");
            }
            cadastra_aluno(&vetaluno,&a,nome,matricula,&pendencia,recursos,&ra,null);
            fscanf(entrada,"%c",&c);
        }

        fscanf(entrada,"%c",&c);

        while(c!='&'){//Importar livros
            fseek(entrada,-1,SEEK_CUR);
            fscanf(entrada, "%[^|]",nome);
            if(strcmp(nome,"*") != 0){
                null = 0;
                fscanf(entrada, "|%[^|]|%d |%d |%d\n", categoria, &data, &pendencia, &aluno);
            }else{
                null=1;
                fscanf(entrada, "|\n");
            }
            cadastra_livro(&vetlivros, &l, nome, &data, categoria, &pendencia, &aluno,&rl,null);
            fscanf(entrada,"%c",&c);
        }

        fscanf(entrada,"%c",&c);

        while(c!='&'){//Importar recursos
            fseek(entrada,-1,SEEK_CUR);
            fscanf(entrada, "%d |%d |%d |%d\n", &id, &tipo, &pendencia, &aluno);
            cadastra_recurso(&cab_recurso,&id,&tipo,&pendencia,&aluno);
            fscanf(entrada,"%c",&c);
        }

        fclose(entrada);
        remove("db.txt");
    }

    pendencia = 0;
    for(int i=0;i<3;i++){
        recursos[i]=0;
    }

    //-----Inicio do Programa-----//

    system("clear");
    printf("Bem-vindo(a) ao Sistema de Gerenciamento da Biblioteca!\n\nPressione ENTER para acessar.\n");
    __fpurge(stdin);
    fgets(lixo,2,stdin);

    for(;;){
        system("clear");
        print_menu();
        __fpurge(stdin);
        scanf("%d",&aux);

        if(aux == 0){//Finalizar o programa e salvar/criptografar os dados
            //---Salvar os dados---
            FILE *saida = fopen("db.txt","w");

            //--Alunos--

            for(int i=0;i<a;i++){
                if(vetaluno[i]!=NULL){
                    fprintf(saida,"%s|%s|%d|%d|%d|%d\n",vetaluno[i]->nome,vetaluno[i]->matricula,vetaluno[i]->pendencia,vetaluno[i]->recursos[0],vetaluno[i]->recursos[1],vetaluno[i]->recursos[2]);
                    free(vetaluno[i]);
                }
                else{
                    fprintf(saida,"*|\n");
                }
            }
            fprintf(saida,"&");

            //--Livros--

            for(int i=0;i<l;i++){
                if(vetlivros[i]!=NULL){
                    fprintf(saida,"%s|%s|%d|%d|%d\n",vetlivros[i]->nome,vetlivros[i]->categoria,vetlivros[i]->data,vetlivros[i]->estado,vetlivros[i]->aluno);
                    free(vetlivros[i]);
                }
                else{
                    fprintf(saida,"*|\n");
                }
            }
            fprintf(saida,"&");

            //--Recursos--

            if(cab_recurso->prox != NULL){
                struct recursos *er = cab_recurso->prox;
                struct recursos *auxrec;
                while(er != NULL){
                    fprintf(saida,"%d|%d|%d|",er->id,er->tipo,er->estado);
                    if(er->estado == 1){
                        fprintf(saida,"%d",er->aluno);
                    }
                    else{
                        fprintf(saida,"-1");
                    }
                    fprintf(saida,"\n");
                    auxrec = er->prox;
                    free(er);
                    er = auxrec;
                }
            }
            fprintf(saida,"&$");

            fclose(saida);

            //---Criptografar os dados---
            saida = fopen("db.txt","r+");
            cripto(&saida,5);

            fclose(saida);
            return 0;
        }

        else if(aux == 1){//Seção de alunos
            system("clear");
            print_menu_alunos();
            scanf("%d",&aux);

            if(aux == 1){//Cadastro de Aluno
                system("clear");
                print_cad_alunos(nome2,matricula);
                id = cadastra_aluno(&vetaluno,&a,nome2,matricula,&pendencia,recursos,&ra,0);
                if(id == 0){
                    printf("\nAluno cadastrado com sucesso!\nID do aluno: %d\n\n",a-1);
                }
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 2){//Visualizar dados do aluno já cadastrado
                system("clear");
                printf("Digite o ID do aluno: ");
                int rec;
                scanf("%d",&id);
                rec = busca_aluno(vetaluno,&a,id);
                if(rec !=-1 || vetaluno[id] != NULL){
                    print_busca_alunos(vetaluno,id);
                }
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 3){//Remoção de Aluno
                system("clear");
                printf("Digite o id do aluno que deseja remover: ");
                scanf("%d",&id);
                remove_aluno(vetaluno,&a,id);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 4){//Listar Alunos
                system("clear");
                lista_aluno(vetaluno,&a);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 5){//Voltar ao menu
                continue;
            }
            else{//Tratamento para opções não existentes
                system("clear");
                printf("\n Opção não existente. Retornando ao menu.\n\n");
                printf("Opção não existente.\n\nPressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
        }

        else if(aux == 2){//Seção de Livros
            system("clear");
            print_menu_livros();
            scanf("%d",&aux);
            if(aux == 1){//Cadastro de Livro
                system("clear");
                print_cad_livros(nome,&data,categoria);
                cadastra_livro(&vetlivros,&l,nome,&data,categoria,&pendencia,&aluno,&rl,0);
                printf("\nLivro cadastrado com sucesso.\nO ID do livro é: %d\n\n",l-1);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 2){//Visualizar a situação de um livro já cadastrado
                system("clear");
                int pesq;
                printf("Deseja pesquisar pelo ID ou por categoria ?\n(digite 1 para ID ou 2 para Categoria): ");
                scanf("%d",&pesq);
                busca_livro(vetlivros,vetaluno,&l,pesq);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 3){//Empréstimo de Livros
                system("clear");
                empresta_livro(vetlivros,&l,vetaluno,&a);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 4){//Devolução de Livros
                system("clear");
                devolve_livro(vetlivros,&l,vetaluno);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 5){//Remoção de Livros
                system("clear");
                remove_livro(vetlivros,&l,vetaluno);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 6){//Listar Livros
                system("clear");
                lista_livro(vetlivros,&l,vetaluno);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 7){//Voltar ao menu
                continue;
            }
            else{//Tratamento para opções não existentes
                system("clear");
                printf("Opção não existente.\n\n Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
        }

        else if(aux == 3){//Seção de Recursos
            system("clear");
            print_menu_recursos();
            scanf("%d",&aux);
            if(aux == 1){//Cadastro de Recursos
                system("clear");
                print_cad_recursos(&id,&tipo);
                rec = cadastra_recurso(&cab_recurso,&id,&tipo,&pendencia,&aluno);
                if(rec == 1){
                    printf("\nRecurso com ID %d já cadastrado no sistema.\n\n",id);
                    printf("Pressione ENTER para retornar ao menu.\n");
                    __fpurge(stdin);
                    fgets(lixo,2,stdin);
                    continue;
                }
                printf("Recurso de ID %d cadastrado com sucesso.\n\n",id);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 2){//Visualizar a situação de um recurso já cadastrado (busca por id);
                system("clear");
                printf("\nDigite o ID do recurso que deseja buscar: ");
                scanf("%d",&id);
                struct recursos *pontr = busca_recurso_id(&cab_recurso,id);
                print_busca_recursos(&pontr,vetaluno,id);
                printf("\n");
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 3){//Emprestar recursos
                system("clear");
                ocupa_recurso(&cab_recurso,vetaluno,&a);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 4){//Desocupar recurso
                system("clear");
                desocupa_recurso(&cab_recurso,vetaluno,&a);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 5){//Remover recurso
                system("clear");
                remove_recurso(&cab_recurso,vetaluno);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 6){//listar recursos
                system("clear");
                lista_recurso(&cab_recurso,vetaluno);
                printf("Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
            else if(aux == 7){//Voltar ao menu
                continue;
            }
            else{//Tratamento para opções não existentes
                system("clear");
                printf("Opção não existente.\n\n Pressione ENTER para retornar ao menu.\n");
                __fpurge(stdin);
                fgets(lixo,2,stdin);
                continue;
            }
        }

        else{//Tratamento para opções não existentes
            system("clear");
            printf("Opção não existente.\n\n Pressione ENTER para retornar ao menu.\n");
            __fpurge(stdin);
            fgets(lixo,2,stdin);
            continue;
        }
    }
    return 0;
}
