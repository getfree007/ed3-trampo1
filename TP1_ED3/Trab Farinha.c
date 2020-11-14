#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "fornecido.h"
#include "LDED.h"

//Estrutura que iguala a um registro do arquivo pessoa
struct regPessoa{
    int RRN;
    int id;
    char nome[40];
    int idade;
    char username[15];
};



int cabecalhoPessoa(FILE *arqW){//Basicamente inicializa o cabeçalho do arquivo Pessoa
    if(arqW == NULL){
        printf("Falha no carregamento do arquivo.");
        return ERRO;
    }

    char status = 0;
    int numReg = 0;
    char lixo = '$';
    rewind(arqW);
    fwrite(&status, sizeof(char), 1, arqW);
    fwrite(&numReg, sizeof(int), 1, arqW);
    for(int i=0; i<59; i++)//Bota os 59 caracteres de lixo;
        fwrite(&lixo, sizeof(char), 1, arqW);
    
    return OK;
}


/*Essa funcao printa os registros no formado especificado
na segunda funcionalidade*/
void printDados(struct regPessoa *dt){
    printf("Dados da pessoa de código %d\n", dt->id);
    printf("Nome: %s\n", (strlen(dt->nome)==0)?"-":dt->nome);/*Isso aqui eh um operador ternario, o helbert que me ensinou,
    eh basicamente um if que voce pode usar dentro dos parametros de uma funcao*/
    printf("Idade: ");
    if(dt->idade == -1)
        printf("-\n");
    else
        printf("%d anos\n", dt->idade);
    printf("Twitter: %s\n\n", dt->username);
}


/*Essa funcao recebe o arquivo para leitura, le registro por registro
e envia para a funcao que printa no formato correto*/
void lerBin(FILE* arqR){

    rewind(arqR);
    char status;
    fread(&status, sizeof(char), 1, arqR);
    if(status == '0'){
        printf("Falha no processamento do arquivo.");
        return;
    }
    else{
        int numReg;
        fread(&numReg, sizeof(int), 1, arqR);
        fseek(arqR, 64, SEEK_SET);
        int i=0;
        while(numReg>0){
            fseek(arqR, (i+1)*64, SEEK_SET);
            char removido;
            fread(&removido, sizeof(char), 1, arqR);
            if(removido == '1'){
                struct regPessoa *dados = (struct regPessoa*)calloc(1, sizeof(struct regPessoa));
                //Faz um calloc pra cada registro, eh util porque os dados sao zerados cada vez que vai ler
                fread(&dados->id, sizeof(int), 1, arqR);

                fread(dados->nome, sizeof(char), 40, arqR);

                fread(&dados->idade, sizeof(int), 1, arqR);

                fread(dados->username, sizeof(char), 15, arqR);

                printDados(dados);//Aqui envia pra printar

                free(dados);
                numReg--;
            }
            i++;
            
        }

    }
    
    fseek(arqR, 64, SEEK_SET);

}



void escreveBin(struct regPessoa dados, FILE *arqW, Lista* li){
    /*Essa funcao recebe todos os dados pertinentes de um registro e os 
    insere no arquivo pessoa da forma apropriada*/
    if(arqW == NULL){
        printf("Falha no carregamento do arquivo.\n");
        return;
    }

    rewind(arqW);
    char status = '0';//Agora eh 0, no final da rotina eh 1
    char removido = '1';//Padrao
    char lixo = '$';//Caractere de lixo especificado
    int i;//Para os loops
    int numReg = (dados.RRN + 1);//quantidade de registros

    //Atualiza os campos status e numero de registros do cabecalho
    fwrite(&status, sizeof(char), 1 , arqW);
    fwrite(&numReg, sizeof(int), 1, arqW);

    
    fseek(arqW, (dados.RRN+1)*64, SEEK_SET);//Vai para o RRN do registro a ser inserido
    fwrite(&removido, sizeof(char), 1, arqW);//Campo "removido" = '1' por default
    fwrite(&dados.id, sizeof(int), 1, arqW);//Campo idPessoa
    char endS = '\0';//char nulo

    int tamLixo = 40 - strlen(dados.nome);//A quantidade de lixo que vamos ter q inserir

    fwrite(dados.nome, sizeof(char), strlen(dados.nome), arqW);//Campo nome
    fwrite(&endS, sizeof(char), 1, arqW);//Insere o char nulo
    for(i=0; i < tamLixo - 1; i++){//Preenche o resto do campo de lixo
        fwrite(&lixo, sizeof(char), 1, arqW);
    }
    
    fwrite(&dados.idade, sizeof(int), 1, arqW);//Campo idade

    fwrite(dados.username, strlen(dados.username)+1, 1, arqW);//Campo username
    for(i=0; i < 15-(strlen(dados.username)+1); i++)
        fwrite(&lixo, sizeof(char), 1, arqW);//Preenche o resto do campo com lixo


    //Terminada a insercao no arquivo pessoa, agora insere na lista dinamica
    insere_lista_ordenada(li, dados.id, dados.RRN);
}



int listaToFile(Lista* li, FILE* arqI){//Funcao que transcreve a lista dinamica pro arquivo indice
    if(arqI == NULL){
        printf("Falha no carregamento do arquivo");
        return ERRO;
    }
    if (li == NULL){
        printf("Falha na abertura da lista");
        return ERRO;
    }
    if(*li == NULL){
        printf("Lista vazia\n");
    }
    char lixo = '$';
    char status = '0';
    rewind(arqI);
    fwrite(&status, sizeof(char), 1, arqI);//Status
    for(int i = 0; i < 7; i++)
        fwrite(&lixo, sizeof(char), 1, arqI);//Preenche de lixo
    Elem *no = *li;
    while(no != NULL){
        fwrite(&no->id, sizeof(int), 1, arqI);
        fwrite(&no->RRN, sizeof(int), 1, arqI);
        no = no->prox;
    }//Preenche os registros com os nos da lista dinamica;
    return OK;
}



int main(){
    int func;
    scanf("%d", &func);
    if (func == 1){;//Funcionalidade 1
        char buffer[36];
        fgets(buffer, 36, stdin);
        char *rest = buffer;
        char *nomeArqRead = strtok_r(rest, " ", &rest);
        char *nomeArqWrite = strtok_r(rest, " ", &rest);
        char *nomeArqIndex = strtok_r(rest, " ", &rest);
        trim(nomeArqRead);
        trim(nomeArqWrite);
        trim(nomeArqIndex);


        FILE *arqR = fopen(nomeArqRead, "r");
        FILE *arqW = fopen(nomeArqWrite, "wb");
        
        if (arqR == NULL){
            printf("Falha no carregamento do arquivo de dados.\n");
            return 0;
        }
        if (arqW == NULL){
            printf("Falha no carregamento do arquivo de dados.\n");
            return 0;
        }
        
        //Inicializa o cabecalho do arq Pessoa
        cabecalhoPessoa(arqW);
        //Definindo todas as variaveis uteis para a insercao dos registros

        char lixo;//Um char pra coletar uns lixo do buffer
        Lista* li = cria_lista();
        int id;//porque na condicao do while tem que ter um id alocado
        int RRN = 0;
        fseek(arqR, 45, SEEK_SET);
        while(fscanf(arqR,"%d%*c", &id)>0){
            struct regPessoa *dadosPessoa = (struct regPessoa*)calloc(1,sizeof(struct regPessoa));
            dadosPessoa->id = id;
            char *nomeAux = (char*)calloc(60, sizeof(char));/*Eh util ler o nome todo, evita erros de buffer, mas
            so vamos usar os 39 primeiros caracteres*/
            if(fscanf(arqR, "%[^,]s", nomeAux)>0){//Se nao for nulo
                trim(nomeAux);;/*Essa funcao ta no fornecidos.c, basicamente tira caracteres desnecessarios
            do comeco e do fim da string*/
                strncpy(dadosPessoa->nome, nomeAux, 39);//Copia um numero determinado da segunda string pra primeira
            }

            if(fscanf(arqR, "%*c%d%*c", &dadosPessoa->idade)<=0){//Para campos idadePessoa nulos
                dadosPessoa->idade = -1;
                fscanf(arqR, "%*c", lixo);
            }
            dadosPessoa->RRN = RRN++;//copia o RRN pra struct e incrementa o RRN
            fscanf(arqR, "%s", dadosPessoa->username);/*Le o username (aqui nao precisamos de cuidados extra,
            o username nunca eh nulo nem extrapola os 14 caracteres)*/
            trim(dadosPessoa->username);
            escreveBin(*dadosPessoa, arqW, li);//Funcao que insere um registro no arquivo .bin
            free(dadosPessoa);
            free(nomeAux);
        }

    //Finalizando os arquivos .csv e .bin
    char statusFinal = '1';
    rewind(arqW);
    fwrite(&statusFinal, sizeof(char), 1, arqW);
    fclose(arqR);
    fclose(arqW);


    FILE *arqI = fopen(nomeArqIndex, "wb");
    if(arqI == NULL){
            printf("Falha no carregamento do arquivo index\n");
            return 0;
        }
    listaToFile(li, arqI);//Depois de terminada a lista dinamica, transforma em arquivo
    libera_lista(li);//basicamente um free(lista);

    rewind(arqI);
    fwrite(&statusFinal, sizeof(char), 1, arqI);//Agora o index ta feito
    fclose(arqI);

    //Leitura e insercao termina aqui, agora para saida
    binarioNaTela1(nomeArqWrite, nomeArqIndex);
    }

    //Funcionalidade 2
    else if(func == 2){
        char nomeArq[11];
        scanf("%s", nomeArq);

        FILE *arq = fopen(nomeArq, "rb");
        if(arq==NULL)
            printf("Falha no processamento do arquivo.");

        lerBin(arq);
    }


    return 0;
}





