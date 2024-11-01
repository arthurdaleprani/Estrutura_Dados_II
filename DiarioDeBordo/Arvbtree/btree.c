#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 3

struct NoArvoreB {
    int num_chaves;
    int chaves[M-1];
    struct NoArvoreB *filhos[M];
    bool folha;
};

struct NoArvoreB *criarNo(bool folha) {
    struct NoArvoreB *novoNo = (struct NoArvoreB *)malloc(sizeof(struct NoArvoreB));
    if (novoNo == NULL) {
        perror("Erro na memoria");
        exit(EXIT_FAILURE);
    }
    novoNo->num_chaves = 0;
    novoNo->folha = folha;
    for (int i = 0; i < M; i++) {
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

void dividirFilho(struct NoArvoreB *pai, int indice) {
    struct NoArvoreB *filho = pai->filhos[indice];
    struct NoArvoreB *novoNo = criarNo(filho->folha);
    novoNo->num_chaves = M/2 - 1;

    for (int i = 0; i < M/2 - 1; i++) {
        novoNo->chaves[i] = filho->chaves[i + M/2];
    }

    if (!filho->folha) {
        for (int i = 0; i < M/2; i++) {
            novoNo->filhos[i] = filho->filhos[i + M/2];
        }
    }

    filho->num_chaves = M/2 - 1;

    for (int i = pai->num_chaves; i > indice; i--) {
        pai->filhos[i + 1] = pai->filhos[i];
    }

    pai->filhos[indice + 1] = novoNo;

    for (int i = pai->num_chaves - 1; i >= indice; i--) {
        pai->chaves[i + 1] = pai->chaves[i];
    }

    pai->chaves[indice] = filho->chaves[M/2 - 1];
    pai->num_chaves++;
}

void inserirNaoCheio(struct NoArvoreB *no, int chave) {
    int i = no->num_chaves - 1;

    if (no->folha) {
        while (i >= 0 && no->chaves[i] > chave) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->num_chaves++;
    } else {
        while (i >= 0 && no->chaves[i] > chave) {
            i--;
        }
        i++;

        if (no->filhos[i]->num_chaves == M - 1) {
            dividirFilho(no, i);

            if (no->chaves[i] < chave) {
                i++;
            }
        }
        inserirNaoCheio(no->filhos[i], chave);
    }
}

void inserir(struct NoArvoreB **raiz, int chave) {
    struct NoArvoreB *no = *raiz;

    if (no == NULL) {
        *raiz = criarNo(true);
        (*raiz)->chaves[0] = chave;
        (*raiz)->num_chaves = 1;
    } else {
        if (no->num_chaves == M - 1) {
            struct NoArvoreB *nova_raiz = criarNo(false);
            nova_raiz->filhos[0] = no;
            dividirFilho(nova_raiz, 0);
            *raiz = nova_raiz;
        }
        inserirNaoCheio(*raiz, chave);
    }
}

void percorrer(struct NoArvoreB *raiz) {
    if (raiz != NULL) {
        int i;
        for (i = 0; i < raiz->num_chaves; i++) {
            percorrer(raiz->filhos[i]);
            printf("%d ", raiz->chaves[i]);
        }
        percorrer(raiz->filhos[i]);
    }
}

int main() {
    struct NoArvoreB *raiz = NULL;

    inserir(&raiz, 10);
    inserir(&raiz, 20);
    inserir(&raiz, 5);
    inserir(&raiz, 6);
    inserir(&raiz, 12);
    inserir(&raiz, 30);

    printf("Percurso em ordem da árvore B: ");
    percorrer(raiz);
    printf("\n");

    return 0;
}
