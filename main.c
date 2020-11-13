#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LDED.h"
//
int main()
{
    Tipo_Dado_Int *dadoint;
    Tipo_Dado_Double *dadodouble;
    Tipo_Dado_Reg *dadoreg;
    Lista *li1 = cria_lista();
    Lista *li2 = cria_lista();
    Lista *li3 = cria_lista();
    int i;

    printf("Tamanho Lista1: %d\n",tamanho_lista(li1));
    printf("Tamanho Lista2: %d\n",tamanho_lista(li2));
    printf("Tamanho Lista2: %d\n",tamanho_lista(li3));

    // Insere dados do Tipo1 na lista li1 (int)
    for(i=0; i < 10; i++)
    {
         dadoint=(Tipo_Dado_Int *)calloc(1,sizeof(Tipo_Dado_Int));
         (*dadoint).Num=i*10;
         insere_lista_inicio(li1,(void *)dadoint);
         printf("Inserindo inicio... %d\n",(*dadoint).Num);
    }

    imprime_lista(li1,1);
    printf("\nTamanho: %d\n",tamanho_lista(li1));

    system("pause");
    printf("\n\n");

    // Insere dados do Tipo2 na lista li2 (double)
    for(i=0; i < 5; i++)
    {
         dadodouble=(Tipo_Dado_Double *)calloc(1,sizeof(Tipo_Dado_Double));
         (*dadodouble).Valor=i*10+5.55;
         insere_lista_final(li2,(void *)dadodouble);
         printf("Inserindo final... %.2lf\n",(*dadodouble).Valor);
    }

    imprime_lista(li2,2);
    printf("\nTamanho: %d\n",tamanho_lista(li2));

    system("pause");
    printf("\n\n");

    // Insere dados do Tipo3 na lista li3 (int, double e txt)
    for(i=0; i < 8; i++)
    {
         dadoreg=(Tipo_Dado_Reg *)calloc(1,sizeof(Tipo_Dado_Reg));
         (*dadoreg).N=100-i;
         (*dadoreg).V=100-i+0.99;
         strcpy((*dadoreg).Txt,"XFulano");
         (*dadoreg).Txt[0]=i+'0';  // Adiciona ASCII do valor de i
         insere_lista_final(li3,(void *)dadoreg);
         printf("Inserindo final... %d - %.2lf - %s\n",
               (*dadoreg).N,(*dadoreg).V,(*dadoreg).Txt);
    }

    imprime_lista(li3,3);
    printf("\nTamanho: %d\n",tamanho_lista(li3));

    system("pause");
    printf("\n\n");

    printf("\nRemovendo dados...\n");
    libera_lista(li1);
    libera_lista(li2);
    libera_lista(li3);
    printf("\nDados removidos...\n");

    system("pause");
    return 0;

}

