#include <stdio.h>

typedef struct arv{
    int num;
    struct arv *esq;
    struct arv *dir;
    struct arv *pai;
} no;


no* inserir(no *raiz, int num) {
    if (raiz == NULL) {
        no *novo = (no*)malloc(sizeof(no)); 
        novo->num = num;
        return novo;
    }//verifica se a raiz é null se for insere o num como raiz

    if (num < raiz->num) {
        raiz->esq = inserir(raiz->esq, num);
        raiz->esq->pai = raiz;//se o num for menor que a raiz vai pra esquerda
    } else {
        raiz->dir = inserir(raiz->dir, num);
        raiz->dir->pai = raiz;//se o num for maior que a raiz vai pra direita
    }

    return raiz;
}

no* buscar(no *raiz, int num) {
    if (raiz == NULL || raiz->num == num) {//verifica se o a raiz existe e se o numero que ta sendo buscado é igual a raiz
        return raiz;
    }
    if (num <= raiz->num) {
   return buscar(raiz->esq, num);//se o numero for menor ou igual a raiz ele busca pra esquerda

    } else {
        return buscar(raiz->dir, num);// se nao busca para a direita da raiz
    }
}

no* excluir(no *raiz, int num){
  if(raiz == NULL){
      return  0;
  }  // olha se existe raiz
    else{
        if(num > raiz->num){
            raiz -> dir = excluir(raiz->dir, num);//caso o num for maior ele vai pra dir
        }else if(num < raiz->num){
            raiz -> esq = excluir(raiz->esq, num);//caso o num for menor ele vai pra esq
        }else{
            if(raiz->esq == NULL){//se não houver filho na esq
                no *temp = raiz->dir;
                free(raiz);
                return 0;
            }else{//se não houver filho na dir
                no *temp = raiz->esq;
                free(raiz);
                return 0;
            }
        }
    }
}

void imprimeNo(int c, int b)
{
    int i;
    for (i = 0; i < b; i++)
        printf("   ");
    printf("%i\n", c);
}

void mostraArvore(no *a, int b)
{
    if (a == NULL)
    {
        return;
    }
    mostraArvore(a->dir, b + 1);
    imprimeNo(a->num, b); 
    mostraArvore(a->esq, b + 1);
}

int main(void) {
  no *raiz = NULL;

  raiz = inserir(raiz, 50);
  raiz = inserir(raiz, 30);
  raiz = inserir(raiz, 20);
  raiz = inserir(raiz, 40);
  raiz = inserir(raiz, 70);
  raiz = inserir(raiz, 60);
  raiz = inserir(raiz, 80);
  mostraArvore(raiz, 3)  ;
  return 0;
}