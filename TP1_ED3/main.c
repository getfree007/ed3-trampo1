#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LDED.h"
#include "fornecido.h"

    #define lixo = '$'
    #define nulo = '-';
    #define TAM = 64;

typedef struct {

    char status;
    int quantidadePessoas;

}cabecalhoAquivo;

typedef struct {

    char removido;
    int idPessoa;
    char nomePessoa[40];
    int idadePessoa;
    char twitterPessoa[15]

}registroPessoa

//Funcao para imprimir todos os dados de um registro
void imprimeRegistro(struct registroPessoa *registro){

    printf("Dados da pessoa de código ");
    if (registro->idPessoa == NULL){
        printf("%d\n", &nulo);
    }else{
        printf ("%d\n", registro->idPessoa);
    }

    printf("Nome: ");
    if (strlen(registro->nomePessoa) == 0){
        printf("%d\n", &nulo);
    }else{
        printf ("%s\n", registro->nomePessoa);
    }

    printf("Idade: ");
    if(registro->idadePessoa < 0){
        printf("%d\n", &nulo);
    } else if (registro->idadePessoa >= 0){
        printf("%d anos\n", registro->idadePessoa);
    }

    printf("Twitter: ");
    if (strlen(registro->twitterPessoa) == 0){
        printf("%d\n", &nulo);
    }else{
        printf("%s\n", registro->twitterPessoa);
    }

    printf ("\n");
}

//Funcao que recebe um arquivo Bin para leitura 
int lerBinario (FILE* arquivo){

    char status, removido;
    int quantidadePessoas, j = 0;

    rewind(arquivo);

    fread(&status, sizeof(char), 1, arquivo);
    switch (status)
    {
    case 0:
        printf("Falha no processamento do arquivo.");
        break;
    
    case 1:
        fread(&quantidadePessoas, sizeof(int), 1, arq);
        fseek(arqR, TAM, SEEK_SET); // posiciona a leitora no final do lixo '$' do cabeçalho
        for (int i = quantidadePessoas; i > 0; i--){
            fseek(arquivo, (j + 1) * TAM, SEEK_SET);
            fread(&removido, sizeof(char), 1, arquivo); 

            if (removido == '1'){

            }       
        }
        break;
    }
    
    
   

    return OK;
}


//Funcao que inserer os dados de todos os reginstros em um arquivo
void inserirBinario(struct registroPessoa, FILE *aquivo, Lista* lista){
    if(arquivo == NULL){
        printf("Falha no carregamento do arquivo.\n");
        return ERRO;
    }


    return OK;
}

//Função que escreve cria o cabeçalho inicial com "0" pessoas e status "0" (ou seja arquivo inconsistente, pq não há pessoas) 
int criarCabecalho(FILE *arquivo){
    if(arqW == NULL){
        printf("Falha no carregamento do arquivo.");
        return ERRO;
    }

    rewind(arquivo);

    cabecalhoAquivo->status = 0;
    fwrite(&cabecalhoAquivo->status, sizeof(char), 1, arquivo);

    cabecalhoAquivo->quantidadePessoas = 0;
    fwrite(&cabecalhoAquivo->quantidadePessoas, sizeof(int), 1, arquivo);

    for(int i=0; i<59; i++){        
        fwrite(&lixo, sizeof(char), 1, arquivo);
    }

    return OK;
}


int main (){

    int funcionalidade;
    scanf("%d", &funcionalidade);

    switch (funcionalidade)
    {
    case 1:
        /* code */
        break;
    case 2:
        char nomeArquivo[11];
        scanf("%s", nomeArquivo);

        FILE *arquivo = fopen(nomeArquivo, "rb");

        if(arquivo == NULL){
            printf("Falha no processamento do arquivo.");
            break;
        }

        lerBinario (arquivo);
        break;
    
    default:
        break;
    }

    if (arquivoLeitura == NULL){
            printf("Falha no carregamento do arquivo de dados.\n");
            return ERRO;
        }
        if (arquivoEscrita == NULL){
            printf("Falha no carregamento do arquivo de dados.\n");
            return ERRO;
        }

    criarCabecalho(arquivo)

    return OK;
}