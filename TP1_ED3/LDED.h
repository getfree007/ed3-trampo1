// Arquivo LDED.h - Lista Dinamica Encadeada Dupla

#define FALSO      0
#define VERDADEIRO 1

#define ERRO         1
#define OK           0


typedef struct indexaPessoa{

    int idPessoa;
    int RRN;

}indexaPessoa;

/*

    TAD já pronta de desenvolvida em ED1 
    SSC0603 - Estrutura de Dados 1 (ED1 - 2020 2o. Sem - Prof. Fernando Santos OSÓRIO )
    http://wiki.icmc.usp.br/index.php/SSC0603_Material_Aulas_2020(fosorio)

*/

struct elemento{
    struct elemento *ant;
    indexaPessoa dado;
    struct elemento *prox;
};


typedef struct elemento Elem;

typedef struct elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, void *dt);
int insere_lista_inicio(Lista* li, void *dt);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
void imprime_lista(Lista* li, int tipo);
