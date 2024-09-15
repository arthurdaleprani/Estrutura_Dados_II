/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *dir;
    struct No *esq;
    int altura;
} No;

typedef No* ArvAVL;

ArvAVL* cria_ArvAVL() {
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(No* no) {
    if (no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
}

int altura_NO(No* no) {
    if (no == NULL)
        return -1;
    return no->altura;
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

void rotacaoEsq(ArvAVL* A) {
    No* B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;

    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq), (*A)->altura) + 1;
    *A = B;
}

void rotacaoDir(ArvAVL* A) {
    No* B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;

    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir), (*A)->altura) + 1;
    *A = B;
}

void rotacaoLD(ArvAVL* A) {
    rotacaoDir(&(*A)->esq);
    rotacaoEsq(A);
}

void rotacaoRD(ArvAVL* A) {
    rotacaoEsq(&(*A)->dir);
    rotacaoDir(A);
}

int fatorBalanceamento_NO(No* no) {
    if (no == NULL)
        return 0;
    return altura_NO(no->dir) - altura_NO(no->esq);
}

int insereArvAVL(ArvAVL* raiz, int valor) {
    int res;
    if (*raiz == NULL) {
        No* novo = (No*) malloc(sizeof(No));
        if (novo == NULL) {
            return 0;
        }
        novo->dado = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    No* atual = *raiz;
    if (valor < atual->dado) {
        if ((res = insereArvAVL(&(atual->esq), valor)) == 1) {
            if (fatorBalanceamento_NO(atual) >= 2) {
                if (valor < (*raiz)->esq->dado) {
                    rotacaoEsq(raiz);
                } else {
                    rotacaoLD(raiz);
                }
            }
        }
    } else if (valor > atual->dado) {
        if ((res = insereArvAVL(&(atual->dir), valor)) == 1) {
            if (fatorBalanceamento_NO(atual) >= 2) {
                if (valor > (*raiz)->dir->dado) {
                    rotacaoDir(raiz);
                } else {
                    rotacaoRD(raiz);
                }
            }
        }
    } else {
        printf("Valor duplicado\n");
        return 0;
    }

    atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;
    return res;
}

No* procuraMenor(No* no) {
    while (no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

int removeNO(ArvAVL* raiz, int valor) {
    if (*raiz == NULL) {
        printf("Valor não existe!\n");
        return 0;
    }

    int res;
    if (valor < (*raiz)->dado) {
        if ((res = removeNO(&(*raiz)->esq, valor)) == 1) {
            if (fatorBalanceamento_NO(*raiz) >= 2) {
                if (altura_NO((*raiz)->dir->esq) < altura_NO((*raiz)->dir->dir)) {
                    rotacaoDir(raiz);
                } else {
                    rotacaoRD(raiz);
                }
            }
        }
    } else if (valor > (*raiz)->dado) {
        if ((res = removeNO(&(*raiz)->dir, valor)) == 1) {
            if (fatorBalanceamento_NO(*raiz) >= 2) {
                if (altura_NO((*raiz)->esq->dir) < altura_NO((*raiz)->esq->esq)) {
                    rotacaoEsq(raiz);
                } else {
                    rotacaoLD(raiz);
                }
            }
        }
    } else {
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
            No* oldNode = *raiz;
            if ((*raiz)->esq != NULL) {
                *raiz = (*raiz)->esq;
            } else {
                *raiz = (*raiz)->dir;
            }
            free(oldNode);
        } else {
            No* temp = procuraMenor((*raiz)->dir);
            (*raiz)->dado = temp->dado;
            removeNO(&(*raiz)->dir, temp->dado);
        }
    }

    if (*raiz != NULL) {
        (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    }

    return 1;
}






int main()
{
 ArvAVL* minhaArvore = cria_ArvAVL();
 insereArvAVL(minhaArvore, 50);
    insereArvAVL(minhaArvore, 30);
    insereArvAVL(minhaArvore, 70);
    insereArvAVL(minhaArvore, 20);

    removeNO(minhaArvore, 20);

    return 0;
}
