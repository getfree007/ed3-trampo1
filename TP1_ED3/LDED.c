#include <stdio.h>
#include <stdlib.h>

#include "LDED.h"

/*
    TAD já pronta de desenvolvida em ED1 
    SSC0603 - Estrutura de Dados 1 (ED1 - 2020 2o. Sem - Prof. Fernando Santos OSÓRIO )
    http://wiki.icmc.usp.br/index.php/SSC0603_Material_Aulas_2020(fosorio)
*/

Lista* cria_lista()
{
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

/*void libera_lista(Lista* li)
{
    if (li != NULL)
	{
        Elem* no;
        while ((*li) != NULL)
		{
            no = *li;
            *li = (*li)->prox;
            free(no->dado.idPessoa);
            free(no->dado.RRN);
            free(no->dado);
            free(no);
        }
        free(li);
    }
}*/

int insere_lista_final(Lista* li, indexaPessoa dt)
{
    Elem *no;

    if (li == NULL) return ERRO;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)  return ERRO;

    no->dado = dt;
    no->prox = NULL;

	if ((*li) == NULL)
	{   //lista vazia: insere in�cio
        no->ant = NULL;
        *li = no;
    }else
	{
        Elem *aux;
        aux = *li;
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return OK;
}

int insere_lista_inicio(Lista* li, indexaPessoa dt)
{
    if (li == NULL)
        return ERRO;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return ERRO;

    no->dado = dt;
    no->prox = (*li);
    no->ant = NULL;

	if (*li != NULL) //lista n�o vazia: apontar para o anterior!
        (*li)->ant = no;
    *li = no;
    return OK;
}

int tamanho_lista(Lista* li)
{
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_vazia(Lista* li)
{
    if (li == NULL)
        return OK;
    if (*li == NULL)
        return OK;
    return FALSO;
}

/*void imprime_lista(Lista* li, int tipo)
{
    Elem* no = *li;
    Tipo_Dado_Int *ptrint;
    Tipo_Dado_Double *ptrdouble;
    Tipo_Dado_Reg *ptrreg;

    if (li == NULL)
        return;

    printf("-------------- INICIO LISTA -----------------\n");
    while (no != NULL)
    {
        // Rotina especifica para exibicao de dados do Tipo1 (int)
        if (tipo==1)
        {
           ptrint=(Tipo_Dado_Int *)no->dado;
           printf("Dado: %d \n",(*ptrint).Num);
        }

        // Rotina especifica para exibicao de dados do Tipo2 (double)
        if (tipo==2)
        {
           ptrdouble=(Tipo_Dado_Double *)no->dado;
           printf("Dado: %.2lf \n",(*ptrdouble).Valor);
        }

        // Rotina especifica para exibicao de dados do Tipo3 (int,double,txt)
        if (tipo==3)
        {
           ptrreg=(Tipo_Dado_Reg *)no->dado;
           printf("Dado: %d - %.2lf - %s\n",(*ptrreg).N,(*ptrreg).V,(*ptrreg).Txt);
        }

        no = no->prox;
    }
    printf("-------------- FIM LISTA -----------------\n");
}*/
