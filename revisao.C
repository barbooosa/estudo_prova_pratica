#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;
    struct No *esq;
    struct No *dir;
    int altura;
} No;

int altura(No* n) {
    if (n == NULL)
        return 0;
    return n->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

No* novoNo(int chave) {
    No* no = (No*)malloc(sizeof(No));
    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 1;
    return no;
}

No* rotacaoDireita(No* y) {
    No* x = y->esq;
    No* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->dir;
    No* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

int fatorBalanceamento(No* n) {
    if (n == NULL)
        return 0;
    return altura(n->esq) - altura(n->dir);
}

No* inserir(No* no, int chave) {
    if (no == NULL)
        return novoNo(chave);

    if (chave < no->chave)
        no->esq = inserir(no->esq, chave);
    else if (chave > no->chave)
        no->dir = inserir(no->dir, chave);
    else 
        return no;

    no->altura = 1 + max(altura(no->esq), altura(no->dir));

    int balance = fatorBalanceamento(no);

    if (balance > 1 && chave < no->esq->chave)
        return rotacaoDireita(no);

    if (balance < -1 && chave > no->dir->chave)
        return rotacaoEsquerda(no);

    if (balance > 1 && chave > no->esq->chave) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }

    if (balance < -1 && chave < no->dir->chave) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

int main() {
    No* raiz = NULL;
    int numeros[] = {30, 40, 24, 58, 48, 26, 11, 13, 14};
    int n = sizeof(numeros) / sizeof(numeros[0]);

    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, numeros[i]);
    }

    printf("Pre-ordem da árvore AVL construída: \n");
    preOrdem(raiz);

    return 0;
}
