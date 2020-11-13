// Arquivo LDED.h - Lista Dinamica Encadeada Dupla
// LDED para dados tipo Void * [Multiplos tipos de dados diferentes em um só TAD]

#define FALSO      0
#define VERDADEIRO 1

#define OK         1
#define ERRO       0

// 3 tipos de dados diferentes para uso nas listas

// Tipo 1
typedef struct {
    int Num;
}  Tipo_Dado_Int;

// Tipo 2
typedef struct {
    double Valor;
}  Tipo_Dado_Double;

// Tipo 3
typedef struct {
    int N;
    double V;
    char Txt[10];
}  Tipo_Dado_Reg;

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
