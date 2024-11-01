#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct NoTreap {
    int chave;
    int prioridade;
    struct NoTreap *esquerda, *direita;
};

//cria um novo no da Treap
struct NoTreap* criarNo(int chave) {
    struct NoTreap* novoNo = (struct NoTreap*)malloc(sizeof(struct NoTreap));
    if (!novoNo) {
        perror("Falha na alocação de memória");
        exit(EXIT_FAILURE);
    }
    novoNo->chave = chave;
    novoNo->prioridade = rand() % 100; 
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

// Rotação a direita
struct NoTreap* rotacaoDireita(struct NoTreap* y) {
    struct NoTreap* x = y->esquerda;
    struct NoTreap* T = x->direita;

    x->direita = y;
    y->esquerda = T;

    return x;
}

// Rotação a esquerda
struct NoTreap* rotacaoEsquerda(struct NoTreap* x) {
    struct NoTreap* y = x->direita;
    struct NoTreap* T = y->esquerda;

    y->esquerda = x;
    x->direita = T;

    return y;
}

// Insercao
struct NoTreap* inserir(struct NoTreap* raiz, int chave) {
    if (raiz == NULL)
        return criarNo(chave);

    if (chave < raiz->chave) {
        raiz->esquerda = inserir(raiz->esquerda, chave);
        if (raiz->esquerda->prioridade > raiz->prioridade)
            raiz = rotacaoDireita(raiz);
    } else {
        raiz->direita = inserir(raiz->direita, chave);
        if (raiz->direita->prioridade > raiz->prioridade)
            raiz = rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Percurso em ordem para exibir a Treap
void percursoEmOrdem(struct NoTreap* raiz) {
    if (raiz != NULL) {
        percursoEmOrdem(raiz->esquerda);
        printf("Chave: %d, Prioridade: %d\n", raiz->chave, raiz->prioridade);
        percursoEmOrdem(raiz->direita);
    }
}


int main() {
    srand(time(0)); 

    struct NoTreap* raiz = NULL;
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("Percurso em ordem da Treap:\n");
    percursoEmOrdem(raiz);

    return 0;
}
