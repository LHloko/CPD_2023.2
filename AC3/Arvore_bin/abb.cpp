#include <bits/stdc++.h>
#include "abb.h"

using namespace std;

struct no {
    int info;
    no *sae;    // sub-árvore a esquerda
    no *sad;    // sub_árvore a direita
};

int altura(no *raiz){
    if(raiz == NULL) {
        return -1; // A altura de uma árvore vazia é -1
    }

    int altura_esq = altura(raiz->sae);
    int altura_dir = altura(raiz->sad);

    return 1 + max(altura_esq, altura_dir);
}

bool buscar(no* a, int valor) {
    if(a == NULL)
        return false;
    
    if(valor == a->info)
        return true;
    else if(valor < a->info)
        return buscar(a->sae, valor);
    else
        return buscar(a->sad, valor);
}

no* criar(int valor_raiz) {
    no *raiz = (no*) calloc(1, sizeof(no));
    if(raiz != NULL)
        raiz->info = valor_raiz;
    
    return raiz;
}

no* inserir(no* n, int valor) {
    if(n == NULL)
        return criar(valor);

    if(valor < n->info)
        n->sae = inserir(n->sae, valor);
    else
        n->sad = inserir(n->sad, valor);
    
    return n;
}

void largura(no* n) {
    queue<no*> f;
    f.push(n);
    while(!f.empty()) {
        no* atual = f.front();
        cout << atual->info << " ";
        f.pop();
        if(atual->sae)
            f.push(atual->sae);
        if(atual->sad)
            f.push(atual->sad);
    }
}

void liberar(no*& n) {
    if(n == NULL)
        return;
    
    liberar(n->sae);
    liberar(n->sad);
    delete n;
    n = NULL;
}

void percorrer(no *n) {
    if(n == NULL)
        return;

    percorrer(n->sae);
    cout << " " << n->info;
    percorrer(n->sad);
}

no* minimo(no* n) {
    if(n->sae != NULL)
        return minimo(n->sae);

    return n;
}

no* remover(no* n, int valor) {
    if(n == NULL)
        return NULL;
    
    if(valor < n->info) {
        n->sae = remover(n->sae, valor);
    } else if(valor > n->info) {
        n->sad = remover(n->sad, valor);
    } else {
        no* temp = NULL;
        if(n->sae == NULL && n->sad == NULL) {
            free(n);
            return NULL;
        } else if(n->sae == NULL) {
            temp = n->sad;
            free(n);
            return temp;
        } else if(n->sad == NULL) {
            temp = n->sae;
            free(n);
            return temp;
        } else {
            temp = minimo(n->sad);
            n->info = temp->info;
            n->sad = remover(n->sad, temp->info);
        }
    }

    return n;
}
