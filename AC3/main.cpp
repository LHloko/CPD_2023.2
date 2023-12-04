#include <bits/stdc++.h>
#include "./Arvore_bin/abb.h"
#include "./Arvore_AVL/avl.h"

using namespace std;

int mod = 10000;

int preencher_avl(no* raiz);
int preencher_bin(no* raiz);

int main() {
    //Sementinha do mal (gerador de valores aleatórios)
    random_device rd;
    mt19937 gen(rd());

    //Criar duas arvores
    no* arv_bin = criar(gen()%mod);
    no* arv_avl = criar_avl(gen()%mod);

    double avg_bin = 0, avg_avl = 0;

    for(int i=0; i<500; i++){
        avg_bin += preencher_bin(arv_bin);
        avg_avl += preencher_avl(arv_avl);

        //Limpar a arvore 
        liberar(arv_bin);
        liberar_avl(arv_avl);

        //Reiniciando a arvore
        arv_bin = criar(gen()%mod);
        arv_avl = criar_avl(gen()%mod);
    }

    cout<<fixed<<setprecision(3);
    cout<<"MEDIA DA ARVORE AVL = "<< avg_avl/500 <<endl;
    cout<<"MEDIA DA ARVORE BIN = "<< avg_bin/500 <<endl;

    return 0;
}

int preencher_avl(no* raiz){
    //Sementinha do mal (gerador de valores aleatórios)
    random_device rd;
    mt19937 gen(rd());

    //Insere na arvore binaria 
    int i=0;
    while(i<1000){
        int aleatorio = gen()%mod;
        if(!buscar_avl(raiz, aleatorio)){
            inserir_avl(raiz, aleatorio);
            i+=1;
        }
    }

    
    return altura_avl(raiz);
}

int preencher_bin(no* raiz){
    //Sementinha do mal (gerador de valores aleatórios)
    random_device rd;
    mt19937 gen(rd());

    int i=0;
    while(i<1000){
        int aleatorio = gen()%mod;
        if(!buscar(raiz, aleatorio)){
            inserir(raiz, aleatorio);
            i+=1;
        }
    }

    return altura(raiz);
}