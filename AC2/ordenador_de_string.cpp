#include <bits/stdc++.h>
using namespace std;

void imprimir(auto v);
int maior(string texto);
void coutingsort(string &text);
bool is_sort(string text);

int main(){
    string txt; cin>> txt;

    coutingsort(txt);
    cout<<"Ordenada: ";
    if(is_sort(txt))
        cout<<"sim"<<endl;
    else
        cout<<"nao"<<endl;
    
    imprimir(txt);

    return 0;
}

void imprimir(auto v){
    for(auto i: v)
        cout<<i;
    cout<<endl;
    return;
}

int maior(string texto){
    int m = texto[0];
    for(int i=1; i<texto.size(); i++)
        if(texto[i]> m)
            m = texto[i];
    return m;
}

void coutingsort(string &text){
    int tam = maior(text) - 97;
    int freq[tam+1] = {0};

    //Vetor de frequência
    for(int i=0; i<text.size(); i++){
        int num = text[i] - 97;
        freq[num] += 1;
    }

    //Vetor de frequência acumulado
    for(int i=1; i<=tam; i++)
        freq[i] += freq[i-1];

    //Ordenando de traz para frente
    int ord[text.size()] = {0};

    for(int i = text.size()-1; i>=0; i--){
        int letra = text[i];
        ord[freq[letra-97]-1] = letra;
        freq[letra-97] -= 1;
    }

    for(int i=0; i<text.size(); i++){
        char l = ord[i];
        text[i] = l;
    }

    return;
}

bool is_sort(string text){
    for(int i=1; i<text.size(); i++)
        if(text[i-1] > text[i])
            return false;
    return true;
}
