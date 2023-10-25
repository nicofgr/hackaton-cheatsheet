#include <iostream>

using namespace std;

class Nodo{
  private:
    int valor;
    Nodo* prox;
  public:
    Nodo(int val) : valor(val), prox(NULL) {}
    void setProx(Nodo& nodo){ prox = &nodo; }
    Nodo* getProx(){ return prox; }
    int getValue(){ return valor; }
};
class ListaLigada{
  private:
    Nodo* topo;
  public:
    ListaLigada() : topo(NULL){};
    bool isEmpty() {
        if(topo == NULL) return true; 
        return false;
    }
    void insert(int valor, int position = 0){
        Nodo* novo = new Nodo(valor);
        if(position == 0){
            Nodo* posterior = getPosition(position);
            novo->setProx(*posterior);
            topo = novo;
            return;
        }
        Nodo* anterior = getPosition(position - 1);
        Nodo* posterior = anterior->getProx();
        anterior->setProx(*novo);
        novo->setProx(*posterior);
    }
    void insertStart(int value) { insert(value); }
    void insertFim(int valor){
        int end = size();
        insert(valor, end);
    }
    int getValue(int position = 0){
        Nodo* node = getPosition(position);
        return node->getValue();
    }    
    Nodo* getPosition(int position){
        if (isEmpty() and position == 0) { return NULL; }
        int tam = size();
        if(tam < position + 1) { throw invalid_argument(" Position greater than size"); }
        Nodo* top = topo; 
        for(int i = 0; i < position; i++){
            top = top->getProx();
        }
        return top;
    }
    int size(){
        if( isEmpty() ) { return 0; }
        Nodo* top = topo;
        int n = 0;
        while(top->getProx() != NULL){
            top = top->getProx();
            n++;
        }
        return ++n;
    }
};
ostream& operator<<(ostream& stream, ListaLigada lista){
    int tam = lista.size();
    for(int i = 0; i < tam; i++){
       stream << "[" << lista.getValue(i) << "]";   
    }
    return stream;
}
int main(){
    ListaLigada lista;
    lista.insertFim(1);
    lista.insertFim(2);
    lista.insertFim(3);
    lista.insertStart(0);
    cout << lista << endl;
    lista.insert(4,1);
    cout << lista << endl;
    return 0;
}
