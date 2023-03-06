#include <iostream>
using namespace std;

class Node {

public:
    int valor;
    Node* NextPTR;

};

void printList(Node*n){
    while(n!= NULL){
        cout<< n->valor << endl;
        n = n-> NextPTR;
    }
}

class List{

public: 
    void insertarLista(Node* &lista, int n){
        Node* nuevo_nodo = new Node();
        nuevo_nodo -> valor = n;

        Node* aux1 = lista;
        Node* aux2;

        while((aux1 != NULL) && (aux1 -> valor < n)){
            aux2 = aux1;
            aux1 = aux1 -> NextPTR;
        }
        //Este while y condicional es simplemente para que la lista quede en orden de valor creciente.
        if(lista == aux1){
            lista = nuevo_nodo;
        }else{
            aux2 -> NextPTR = nuevo_nodo;
        }
        nuevo_nodo -> NextPTR = aux1;
    }

};

int main(){

    Node*lista = NULL;
    Node*head = new Node();
    Node*second = new Node();
    Node*third = new Node();

    head->valor = 1; 
    head -> NextPTR = second;
    second-> valor = 2;
    second -> NextPTR = third;
    third -> valor = 3;
    third -> NextPTR = NULL;

    printList(head);
    cout << "ay lmaoo";
    return 0;
}