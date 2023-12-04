#include <bits/stdc++.h>

#include "avl.h"

using namespace std;

struct no {
    int info;
    int altura;
    no *sae;    // sub-árvore a esquerda
    no *sad;    // sub-árvore a direita
};

int altura_avl(no *n) {
    if(n == NULL)
        return 0;

    return n->altura;
}

int buscar_avl(no* n, int valor) {
    if(n == NULL)
        return false;
    
    if(valor == n->info)
        return true;
    else if(valor < n->info)
        return buscar_avl(n->sae, valor);
    else
        return buscar_avl(n->sad, valor);
}

int contar(no* raiz,int a, int b){
    if(raiz == NULL)
        return 0;

    int contador = 0;

    //se estiver no intervalo
    if (raiz->info >= a && raiz->info <= b) {
        contador++;  
        cout << "O Valor " << raiz->info << " foi contado" << endl;
    }

    contador += contar(raiz->sae, a, b);
    contador += contar(raiz->sad, a, b);

    return contador; 
}

no* criar_avl(int valor) {
    no* n = (no*) calloc(1, sizeof(no));
    if(n != NULL) {
        n->info = valor;
        n->altura = 1;
    }

    return n;
}

void em_ordem_avl(no *n) {
    if(n == NULL)
        return;

    em_ordem_avl(n->sae);
    cout << n->info << " ";
    em_ordem_avl(n->sad);
}

int fb_avl(no* n){
    if(n == NULL)
        return 0;

    return altura_avl(n->sae) - altura_avl(n->sad);
}

no* inserir_avl(no* n, int valor){
    if (n == NULL)
        return criar_avl(valor);
 
    if (valor < n->info)
        n->sae = inserir_avl(n->sae, valor);
    else
        n->sad = inserir_avl(n->sad, valor);
 
    n->altura = 1 + max(altura_avl(n->sae), altura_avl(n->sad));
 
    int bf = fb_avl(n);
    // LL-imbalance
    if(bf > 1 && valor < n->sae->info)
        return rot_direita(n);

    // RR-imbalance
    if(bf < -1 && valor > n->sad->info)
        return rot_esquerda(n);

    // LR-imbalance
    if(bf > 1 && valor > n->sae->info){
        n->sae = rot_esquerda(n->sae);
        return rot_direita(n);
    }

    // RL-imbalance
    if(bf < -1 && valor < n->sad->info){
        n->sad = rot_direita(n->sad);
        return rot_esquerda(n);
    }

    return n;
}

void largura_avl(no* n) {
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

void liberar_avl(no*& n){
    if(n == NULL)
        return;
    
    liberar_avl(n->sae);
    liberar_avl(n->sad);
    delete n;
    n = NULL;
}

void delet_sad(no*& n){
    if (n == NULL)
        return;
 
    delet_sad(n->sad);
    n->sad = NULL;

    int bf = altura_avl(n);
 
    if(bf > 1 ){
        if(altura_avl(n->sae->sae) >= altura_avl(n->sae->sad))
            n = rot_direita(n);
        else{
            n->sae = rot_esquerda(n->sae);
            n = rot_direita(n);
        }
    }else if( bf < -1)
        if(altura_avl(n->sad->sad) >= altura_avl(n->sad->sae))
            n = rot_esquerda(n);
        else{
            n->sad = rot_direita(n->sad);
            n = rot_esquerda(n);
        }
}

no* proximo_de(no* raiz, int valor){
    no* prox = NULL;
    int diferenca;
    int less = abs(raiz->info - valor);

    while(raiz != NULL){
        //Calula a diferença entre o valor requerido e o do nó atual
        diferenca = abs(raiz->info - valor);

        //Se a diferença for menor salva o menor 
        if(diferenca < less){
            less = diferenca;
            prox = raiz;
        }

        if(raiz->info == valor){
            prox = raiz;
            break;
        }

        if(raiz->info > valor)
            raiz = raiz->sae;
        else
            raiz = raiz->sad;
    }

    cout<<"O valor mais proximo do "<<valor<<" => "<<prox->info<<endl;
    return prox;
}

no* remover_avl(no *n, int valor) {
    if (n == NULL)
        return NULL;

    no *temp = NULL;
    if(valor > n->info) {
        n->sad = remover_avl(n->sad, valor);
        if(fb_avl(n) == 2) {
            if(fb_avl(n->sae) >= 0)
                n = rot_direita(n);
            else {
                n->sae = rot_esquerda(n->sae);
                n = rot_direita(n);
            }
        }
    } else if(valor < n->info) {
        n->sae = remover_avl(n->sae, valor);
        if(fb_avl(n) == -2)  {
            if(fb_avl(n->sad) <= 0)
                n = rot_esquerda(n);
            else {
                n->sad = rot_direita(n->sad);
                n = rot_esquerda(n);
            }
        }
    } else {
        if(n->sad != NULL) { 
            temp = n->sad;
            while(temp->sae != NULL)
                temp = temp->sae;
 
            n->info = temp->info;
            n->sad = remover_avl(n->sad, temp->info);
            if(fb_avl(n) == 2) {
                if(fb_avl(n->sae) >= 0)
                    n = rot_direita(n);
                else {
                    n->sae = rot_esquerda(n->sae);
                    n = rot_direita(n);
                }
            }
        } else {
            return n->sae;
        }
    }
    n->altura = altura_avl(n);
    return n;
}

// LL-rotation
no* rot_direita(no* n){
    no* E = n->sae;
 
    n->sae = E->sad;
    E->sad = n;
 
    n->altura = 1 + max(altura_avl(n->sad), altura_avl(n->sae));
    E->altura = 1 + max(altura_avl(E->sad), altura_avl(E->sae));
 
    return E;
}
 
// RR-rotation
no* rot_esquerda(no* n) {
    no* D = n->sad;
 
    n->sad = D->sae;
    D->sae = n;
 
    n->altura = max(altura_avl(n->sad), altura_avl(n->sae)) + 1;
    D->altura = max(altura_avl(D->sad), altura_avl(D->sae)) + 1;
 
    return D;
}