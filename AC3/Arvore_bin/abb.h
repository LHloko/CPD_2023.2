#ifndef ABB_H    // INCLUDE GUARD
#define ABB_H

// INTERFACE DA ARVORE BINÁRIA DE BUSCA (ABB)

typedef struct no no;

int altura(no *raiz);
bool buscar(no* a, int valor);
no* criar(int valor_raiz);
no* inserir(no* a, int valor);
void largura(no* n);
void liberar(no*& n);
void percorrer(no *n);
no* remover(no* a, int valor);

#endif // ABB_H