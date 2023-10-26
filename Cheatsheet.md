## Tipos abstratos de dados
### Lista Ligada
```cpp
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
```
### Pilha (Estática)
O vector já se comporta como pilha <br>
insert() – It inserts new elements before the element at the specified position <br>
erase() – It is used to remove elements from a container from the specified position or range.
```cpp
#include <iostream>
#include <vector>
#define MAX 100

using namespace std;

ostream& operator<<(ostream& stream, vector<int> pile){
    for(int i = 0; i < pile.size(); i++){ stream << pile[i]; }
    return stream;
}
int main(){
    vector<int> pile;
    pile.push_back(1);
    pile.push_back(2);
    pile.push_back(3);
    cout << pile << endl;  //123
    pile.pop_back();
    cout << pile << endl;  //12
    return 0;
}
```
### Fila

## Arvores
### Arvore Binaria de Busca (BST)
```cpp
class BST{
  private:
    int key;
    BST* left;
    BST* right;
  public:
    BST(int key) : key(key), left(NULL), right(NULL) {}
    void insert(int value) {
        if(value > key) right = insert(value, right);
        if(value < key) left = insert(value, left);
    }
    BST* insert(int value, BST* root){
        if (root == NULL){
            root = new BST(value);
            return root;
        }
        if(value > root->key) root->right = insert(value, root->right);
        if(value < root->key) root->left = insert(value, root->left);
        return root;
    }
    void printInOrder(){
        printInOrder(this);
    }
    void printInOrder(BST* root){
        if(root == NULL) return;
        printInOrder(root->left);
        cout << "[" << root->key << "]";
        printInOrder(root->right);
    }
    bool search(int value){
        return search(value, this);
    }
    bool search(int value, BST* root){
        if(root == NULL) return false;
        if(root->key == value) return true;
        if(value < root->key) return search(value, root->left);
        if(value > root->key) return search(value, root->right);
    }
};
```

### Arvore AVL
### Arvore B

## Grafos
### Matriz de Adjacência
### Lista de Adjacência
OBS: Precisa usar a Lista de Adjacência
```cpp
class Graph{
    vector<LinkedList*> adjacencyList;
    int nVertices;
  public:
    Graph() : adjacencyList(0), nVertices(0) {};
    void addVertices(int quant){
        for(int i = 0; i < quant; i++){
            LinkedList* novo = new LinkedList();
            adjacencyList.push_back(novo);
        }
    }
    void addEdge(int A, int B){
        adjacencyList[A]->insert(B);
    }
    void printAdjacencyList(){
        for(int i = 0; i < adjacencyList.size(); i++){
            cout << i << ": " << *adjacencyList[i] << endl;
        }
    }
};
```
### Matriz de Incidência
### Caminhamento
#### Busca em Profundidade
Usa pilha
#### Busca em Largura
Usa fila
### Distancia em Grafos
Sem peso: Busca em Largura <br>
Com peso: Dijkstra
### Tabela Hash

## Sorting

## Search
### Pesquisa Sequencial
### Pesquisa Binária
### Arvores de Pesquisa
### Trie e Patricia

## Automatos
### Automato de Estado Finito
### Linguagem contavel
