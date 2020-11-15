#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LDED.h"
#include "fornecido.h"

    static char lixo = '$';
    static char nulo = '-';
    static char finalString = '\0';
    static char zero = '0';
    static char um = '1';
    static int TAM = 64;
    int ultimoRRN = 1;

typedef struct registroPessoa{

    char removido;
    int idPessoa;
    char nomePessoa[40];
    int idadePessoa;
    char twitterPessoa[15];

}registroPessoa;


//Funcao para imprimir todos os dados de um registro
void imprimeRegistro(registroPessoa *registro){

    printf("Dados da pessoa de código ");
    printf ("%d\n", registro->idPessoa);
    

    printf("Nome: ");
    if (strlen(registro->nomePessoa) == 0){
        printf("%c\n", nulo);
    }else{
        printf ("%s\n", registro->nomePessoa);
    }

    printf("Idade: ");
    if(registro->idadePessoa < 0){
        printf("%c\n", nulo);
    } else if (registro->idadePessoa >= 0){
        printf("%d anos\n", registro->idadePessoa);
    }

    printf("Twitter: ");
    if (strlen(registro->twitterPessoa) == 0){
        printf("%c\n", nulo);
    }else{
        printf("%s\n", registro->twitterPessoa);
    }

    printf ("\n");
}


//Funcao que recebe um arquivo Bin para leitura e 
int lerBinario (FILE* arquivo){
        //funcionalidade 2
    char status, removido;
    int quantidadePessoas,  byteOfSetJump = 0;

    rewind(arquivo);

    fread(&status, sizeof(char), 1, arquivo);
    switch (status)
    {
    case 0:
        {
        printf("Falha no processamento do arquivo.");
        break;
        }
    case 1:
        {
        fread(&quantidadePessoas, sizeof(int), 1, arquivo);
        fseek(arquivo, TAM, SEEK_SET); // posiciona a leitora no final do lixo '$' do cabeçalho
        for (int i = quantidadePessoas; i > 0; i--){
            fseek(arquivo, (byteOfSetJump + 1) * TAM, SEEK_SET);
            fread(&removido, sizeof(char), 1, arquivo); 
            // alocando uma struct do tipo 'registroPessoa' criada dianmicamente
            struct registroPessoa *input = (struct registroPessoa*)calloc(1, sizeof(struct registroPessoa));
                
            //trasnferindo dados para struct
            fread(&input->idPessoa, sizeof(int), 1, arquivo);
            fread(input->nomePessoa, sizeof(char), 40, arquivo);
            fread(&input->idadePessoa, sizeof(int), 1, arquivo);
            fread(input->twitterPessoa, sizeof(char), 15, arquivo);

            if (removido == '1'){
                imprimeRegistro(input); // imprimir arquivo caso não tenha sido excluido
            }
            free (input); // libera alocaçao
            byteOfSetJump++;      
        }
        break;
        }
    } 
    fseek(arquivo, TAM, SEEK_SET);
    return OK;
}


//Funcao que insere dados de todos os registros em um arquivo
int inserirBinario(indexaPessoa index, registroPessoa registro, FILE* arquivo, Lista* lista){
    if(arquivo == NULL){
        printf("Falha no carregamento do arquivo.\n");
        return ERRO;
    }

    char statusOFF = '1';
    char statusON = '0';
    char removido = '1';
    
    rewind(arquivo);
    fwrite(&statusOFF, sizeof(char), 1 , arquivo);
    fwrite(&ultimoRRN, sizeof(int), 1, arquivo);
    //
    fseek(arquivo, (index.RRN+1) * TAM, SEEK_SET);
    
    //escrevendo campo removido como 1 (para indicar que o registro não está marcado como removido)
    fwrite(&removido, sizeof(char), 1, arquivo);
    
    //escrevendo idPessoa
    fwrite(&registro.idPessoa, sizeof(int), 1, arquivo);
    
    //escrevendo nomePessoa e completando o que falta dos 40bytes com '$' 
    fwrite(registro.nomePessoa, sizeof(char), strlen(registro.nomePessoa), arquivo);
    for(int i=0; i < 40 - strlen(registro.nomePessoa) - 1; i++){
        fwrite(&lixo, sizeof(char), 1, arquivo);
    }
    //escrevendo idadePessoa
    fwrite(&registro.idadePessoa, sizeof(int), 1, arquivo);
    
    ///escrevendo twitterPessoa e completando o que falta dos 15bytes com '$'
    fwrite(registro.twitterPessoa, strlen(registro.twitterPessoa)+1, 1, arquivo);
    for(int i=0; i < 15 - strlen(registro.twitterPessoa) - 1; i++){
        fwrite(&lixo, sizeof(char), 1, arquivo);
    }
    //
    insere_lista_final(lista, index);
    rewind(arquivo);
    fwrite(&statusON, sizeof(char), 1 , arquivo);

    return OK;
}


//Função que escreve cria o cabeçalho pessoa com "0" pessoas e status "0" (ou seja arquivo inconsistente, pq não há pessoas) 
int criarCabecalhoPessoa(FILE *arquivo){
    if(arquivo == NULL){
        printf("Falha no carregamento do arquivo.");
        return ERRO;
    }

    rewind(arquivo);

    int status = 0;
    fwrite(&status, sizeof(char), 1, arquivo);

    int quantidadePessoas = 0;
    fwrite(&quantidadePessoas, sizeof(int), 1, arquivo);

    for(int i=0; i<59; i++){        
        fwrite(&lixo, sizeof(char), 1, arquivo);
    }

    return OK;
}


//Função que escreve cria o cabeçalho pessoa indexada com status "0" (ou seja arquivo inconsistente, pq não há dados) 
int criarCabecalhoIndex(FILE *arquivo){
    if(arquivo == NULL){
        printf("Falha no carregamento do arquivo.");
        return ERRO;
    }

    rewind(arquivo);

    fwrite(&zero, sizeof(char), 1, arquivo);

    for(int i=0; i<7; i++){        
        fwrite(&lixo, sizeof(char), 1, arquivo);
    }

    return OK;
}

int criarArquivoIndexado(Lista* lista, FILE* arquivo){//Funcao que transcreve a lista dinamica pro arquivo indice
    if(arquivo == NULL){
        printf("Falha no carregamento do arquivo");
        return ERRO;
    }
    if (lista == NULL || *lista == NULL){
        printf("Falha no processamento do arquivo.");
        return ERRO;
    }
    criarCabecalhoIndex (arquivo); //criando cabeçalho do arquivo
    Elem *no = *li;
    // preenchendo arquivo com dados indexados da lista
    while(no != NULL){
        fwrite(&no->idPessoa, sizeof(int), 1, arquivo);
        fwrite(&no->RRN, sizeof(int), 1, arquivo);
        no = no->prox;
    }
    //modificando o status do arquivo de '0' (dados inconsistentes) para '1' (dados consistentess)
    rewind(arquivo);
    fwrite(&um, sizeof(char), 1, arquivo);
    return OK;
}

int main (){

    int funcionalidade;
    scanf("%d", &funcionalidade);
    int idPessoa = 0 , RRN = 0 ;
    switch (funcionalidade)
    {
    case 1:
        {
        char cabecalhoLixo [36]; // usado p/ pular o cabecaLho inicial do aqv de leitura
        char charLixo; // usado pra ler coisas inuteis
        fgets (cabecalhoLixo, 36, stdin);
        char *auxiliar = cabecalhoLixo;
        char *arquivoLeituraNome = strtok_r(auxiliar, " ", &auxiliar);
        char *arquivoEscritaNome = strtok_r(auxiliar, " ", &auxiliar);
        char *arquivoIndexadoNome = strtok_r(auxiliar, " ", &auxiliar);
        trim(arquivoLeituraNome);
        trim(arquivoEscritaNome);
        trim(arquivoIndexadoNome);
        
        //abrindo os arquivos de Leitura, Escrita e Indexação :)
        FILE *arquivoLeitura = fopen(arquivoLeituraNome, "r");
        if (arquivoLeitura == NULL){
            printf("Falha no carregamento do arquivo de dados.\n");
            return ERRO;
        }

        FILE *arquivoEscrita = fopen(arquivoEscritaNome, "wb");
        if (arquivoEscrita == NULL){
            printf("Falha no carregamento do arquivo de dados.\n");
            return ERRO;
        }
        FILE *arquivoIndex = fopen(arquivoIndexadoNome, "wb");
        if(arquivoIndex == NULL){
            printf("Falha no carregamento do arquivo index\n");
            return ERRO;
        }

        criarCabecalhoPessoa(arquivoEscrita); // criando cabecalho p/ arqv pessoa
        Lista* lista = cria_lista(); //iniciando lista p indexacao

        fseek(arquivoLeitura, 45, SEEK_SET); //pulando cabecalho do arquivo

        while(fscanf(arquivoLeitura,"%d%*c", &idPessoa)>0){
            registroPessoa *registro = (registroPessoa*)calloc(1,sizeof(registroPessoa));
            registro->idPessoa = idPessoa;

            char *nomePessoa = (char*)calloc(40, sizeof(char));
            if(fscanf(arquivoLeitura, "%[^,]s", nomePessoa)>0){
                trim(nomePessoa);
                strncpy(registro->nomePessoa, nomePessoa, 39);
            }
            if(fscanf(arquivoLeitura, "%*c%d%*c", &registro->idadePessoa)<=0){
            registro->idadePessoa = -9;
            fscanf(arquivoLeitura, "%*c", charLixo);
            }
            index->RRN = RRN++;
            fscanf(arquivoLeitura, "%s", registro->twitterPessoa);
            trim(registro->twitterPessoa);
            inserirBinario(*registro, arquivoEscrita, lista);
            free(registro);
            free(nomePessoa);
        }
            
            rewind(arquivoEscritaNome);
            //modificando o status do arquivo de '0' (dados inconsistentes) para '1' (dados consistentess)
            charLixo = '1';
            fwrite(&charLixo, sizeof(char), 1, arquivoEscrita);
            fclose(arquivoLeitura);
            fclose(arquivoEscrita);

            //parte de indexacao 
            criarArquivoIndexado(lista, FILE* arquivoIndex)
            fclose(arquivoIndex);


            //printando a saida solocida com a funcao fornecida
            binarioNaTela1(arquivoEscritaNome, arquivoIndexadoNome);
        break;
        }
    case 2:
        {
        /*
        char nomeArquivo[11];
        scanf("%s", nomeArquivo);

        FILE *arquivo = fopen(nomeArquivo, "rb");

        if(arquivo == NULL){
            printf("Falha no processamento do arquivo.");
            break;
        }

        lerBinario (arquivo);
        */
        break;
        }
    }
    return OK;
    
}