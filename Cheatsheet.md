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
#### Busca em Profundidade (Codigo em C)
Usa pilha
```c
lista* depth_first_search(grafo* g, int startV){
    pilha* visitado = cria_pilha();
    visitado = _dfs_recursion(g, startV, visitado);    //  Chama a componente recursiva

    lista* dfs = stack_to_list_transfer(visitado);    //Transfere da pilha pra uma lista
    free_stack(visitado);
    return dfs;
}

pilha* _dfs_recursion(grafo* g, int currentVertice, pilha* visitado){    //  MUDAR AQUI PRA CONTINUE
    push_pilha(visitado, currentVertice);    //  Marcando vértice atual como visitado
    nodo* neighboursList = g->adjacencyList[currentVertice - 1]->head;    //  Vizinhos do vértice atual

    while(neighboursList != NULL){
        if(is_in_stack(visitado, neighboursList->info1) == 0){    //  Se vizinho não visitado
            if(neighboursList->info2 > g->weightOffset){    //  Se a ponte estiver acima do nivel da água então
                visitado = _dfs_recursion(g, neighboursList->info1, visitado);    //  Visita os vizinhos do vizinho
            }else
                neighboursList = neighboursList->prox;      //  Senão passa pro próximo vizinho
        }else
            neighboursList = neighboursList->prox;    // Senão passa pro próximo vizinho
    }
    return visitado;
}
```
#### Busca em Largura (Codigo em C)
Usa fila
```c
lista* breath_first_search(grafo* g, int startV){
    fila* aux = cria_fila();
    lista* enfilerado = cria_lista();

    push_fila(aux, startV);
    enfilerado = lista_insere_final(enfilerado, startV, 0);    //  Enfilera o vértice inicial
    while(get_queue_size(aux) > 0){    //  Enquanto a fila tiver vértices
        int currentVertice = pop_fila(aux);     // Pega um vertice da fila
        nodo* neighboursList = g->adjacencyList[currentVertice-1]->head;    // Vizinhos do vertice atual

        while(neighboursList != NULL){      // Ainda tem vizinhos não verificados
            if(is_in_list(enfilerado, neighboursList->info1) == 0){    // Verifica se o vizinho não foi enfileirado
                push_fila(aux, neighboursList->info1);      // Senão, enfilera
                enfilerado = lista_insere_final(enfilerado, neighboursList->info1, 0);   // Marca como enfilerado
            }
            neighboursList = neighboursList->prox;     //  Passa pro proximo vizinho
        }
    }
    free_queue(aux);
    return enfilerado;
}

```
### Distancia em Grafos (Codigo em C)
Dijkstra: Cria outro grafo com os menores caminhos entre vértices.
```c
void menor_caminho_bfs(grafo* g, int startV, int finishV){    //  BFS modificada para criar um vetor dos pais
    int* pai = (int*)malloc(g->nVertices*sizeof(int));
    fila* aux = cria_fila();
    fila* enfilerado = cria_fila();

    push_fila(aux, startV);
    push_fila(enfilerado, startV);
    while(get_queue_size(aux) > 0){
        int currentVertice = pop_fila(aux);    //  Vertice atual
        nodo* neighboursList = g->adjacencyList[currentVertice-1]->head;    //  Vizinhos do vertice atual
        
        while(neighboursList != NULL){    //  Enquanto não chega no fim dos vizinhos
            if(is_in_queue(enfilerado, neighboursList->info1) == 0){    //  Se o vizinho não foi enfileirado
                if(neighboursList->info2 > g->weightOffset){    //  Se tiver conexão com o vizinho
                    push_fila(aux, neighboursList->info1);    //  Enfileira
                    push_fila(enfilerado, neighboursList->info1);    //  Marca como enfilerado
                    pai[neighboursList->info1] = currentVertice;    //  Marca o pai do vizinho como o vert atual
                }
            }
            neighboursList = neighboursList->prox;    //  Proximo vizinho
        }
    }
    free_queue(aux);

    if(is_in_queue(enfilerado, finishV) == 0){    //  Se os vértices não tiverem no mesmo grafo conexo (sem caminho)
        printf("sem caminho entre %d e %d", startV, finishV);
        free_queue(enfilerado);
        free(pai);
        return;
    }
    int nPontes = 0;
    nPontes = _print_menor_caminho(pai, startV, finishV);
    printf(" (%d pontes)", nPontes);
    free_queue(enfilerado);
    free(pai);
}

int _print_menor_caminho(int* pai, int startV, int finishV){
    int nPontes = 0;
    if(startV != finishV){
        nPontes = 1 + _print_menor_caminho(pai, startV, pai[finishV]);
        printf(" -> ");
    }
    printf("%d", finishV);
    return nPontes;
}
```
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
