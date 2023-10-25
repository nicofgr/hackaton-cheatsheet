#include <iostream>
#include <stdexcept>

using namespace std;

class Nodo{
  private:
    int valor;
    Nodo* prox;
  public:
    //INITIALIZERS
    Nodo(int val) : valor(val), prox(NULL) {}
    //GETTERS
    int getValue(){ return valor; }
    Nodo* getProx(){ return prox; }
    //SETTERS
    void setProx(Nodo& nodo){ prox = &nodo; }
};

class ListaLigada{
  private:
    Nodo* topo;
  public:
    //INITIALIZERS
    ListaLigada() : topo(NULL){};
    //GETTERS
    int getValue(int position = 0){
        Nodo* node = getPosition(position);
        return node->getValue();
    }    
    Nodo* getPosition(int position){
        checkPosition(position);
        if (isEmpty() and position == 0) { return NULL; }
        Nodo* top = topo; 
        for(int i = 0; i < position; i++){ top = top->getProx(); }
        return top;
    }
    int removePosition(int position = 0){
        if(isEmpty()) { throw invalid_argument("List is empty"); }
        checkPosition(position);
        Nodo* node = getPosition(position);
        int value = node->getValue();
        if(size() == 1){
            topo = NULL;
            delete(node);
            return value;
        }
        if(position == 0){
            topo = node->getProx();
            delete(node);
            return value;
        }
        Nodo* anterior = getPosition(position - 1);
        Nodo* proximo = getPosition(position + 1);
        anterior->setProx(*proximo);
        delete(node);
        return value;
    }
    //SETTERS
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
    //OUTROS
    bool isEmpty() {
        if(topo == NULL) return true; 
        return false;
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
    void checkPosition(int position){
        if(size() < position) { throw invalid_argument("Invalid Position: Position greater than size"); }
        if(position < 0) { throw invalid_argument("Invalid Position: Negative position"); }
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
    lista.removePosition(1);
    cout << lista << endl;
    lista.removePosition();
    cout << lista << endl;
    lista.removePosition();
    cout << lista << endl;
    lista.removePosition(50);
    cout << lista << endl;
    return 0;
}
