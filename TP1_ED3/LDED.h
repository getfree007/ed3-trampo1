// Arquivo LDED.h - Lista Dinamica Encadeada Dupla
// LDED para dados tipo Void * [Multiplos tipos de dados diferentes em um só TAD]

#define FALSO      0
#define VERDADEIRO 1

#define OK         1
#define ERRO       0


struct regPessoa{
    int existencia;
    int idPessoa;
    char nomePessoa[40];
    int idadePessoa;
    char twitterPessoa[15];
};

// TAD já pronta de desenvolvida em ED1 
//SSC0603 - Estrutura de Dados 1 (ED1 - 2020 2o. Sem - Prof. Fernando Santos OSÓRIO )
// http://wiki.icmc.usp.br/index.php/SSC0603_Material_Aulas_2020(fosorio)


struct registroPessoa{
    int RRN;
    int idPessoa;
    char nomePessoa[40];
    int idadePessoa;
    char twitterPessoa[15];
};

//Definição do tipo lista
struct elemento{
    struct elemento *ant;
    void *dado;
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
