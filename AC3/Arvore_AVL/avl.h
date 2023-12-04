#ifndef AVL_H
#define AVL_H

typedef struct no no;

//Funções Adicionais (by: LH) 

/*
Entrada: nó raiz, e dois inteiros a e b;
Saída: quantidade de elementos dentro do intervalo [a,b]
*/
int contar(no* raiz,int a, int b);

/*
Entrada: Nó raiz da arvore e elemento a ser buscado
Saída: Retorna o nó com valor mais proximo ou igual ao passado
*/
no* proximo_de(no* raiz, int valor);

/*
Entrada: Nó raiz da arvore 
Saída: não tem 
*/
void delet_sad(no*& n);
 
 
int altura_avl(no *n);
int buscar_avl(no* n, int valor);
no* criar_avl(int valor);
void em_ordem_avl(no *n);
int fb_avl(no* n);
no* inserir_avl(no* n, int valor);
void largura_avl(no* n);
void liberar_avl(no*& n);
no* remover_avl(no* n, int valor);
no* rot_direita(no* n); 
no* rot_esquerda(no* n); 

#endif // AVL_H