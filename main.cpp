#include <iostream>
using namespace std;

//Clase Node para lista de ints
class Node {

public:
    int valor;
    Node* NextPTR;

    Node(int valor) {//constructor de la clase nodo 
        this->valor= valor;
        this->NextPTR = nullptr;
    }
};
//método que imprime lista de ints
void printList(Node*n){
    while(n!= NULL){
        cout<< n->valor << endl;
        n = n-> NextPTR;
    }
}
// Clase de List
class List{

public: 

    Node * head;

    int size;
    
    List(){
        head = NULL;
        size = 0;
    }

    void insertFirst(int valor){
        Node* newNode = new Node(valor);
        newNode -> NextPTR = head;
        head = newNode;
        size ++;
        }

    void deleteFirst(){
        if(head != nullptr){

            Node* Temp = head;
            head = head -> NextPTR;
            delete Temp;
            size--;
        }
    }

};

class collectorNode{
    public:
        Node*NodePTR;
        collectorNode * NextCollectorPTR;

    collectorNode(Node* DeletedNodePTR){

        this -> NodePTR = DeletedNodePTR;
        this -> NextCollectorPTR = nullptr;
    }
};

class collectorList{

public: 

    collectorNode* head;

    int size;
    
    collectorList(){
        head = NULL;
        size = 0;
    }

    void insertFirst( Node* DeletedNodePTR){
        collectorNode* newNode = new collectorNode(DeletedNodePTR);
        newNode -> NextCollectorPTR = head;
        head = newNode;
        size ++;
        }

    void deleteFirst(){
        if(head != nullptr){

            collectorNode* Temp = head;
            head = head -> NextCollectorPTR;
            delete Temp;
            size--;
        }
    }

};
int main(){

    List *newList = new List();

    newList->insertFirst(1);
    newList->insertFirst(2);
    newList->insertFirst(3);

    printList(newList->head);
    cout << "\n";
    newList ->deleteFirst();

    printList(newList->head);

    printf("%p\n",newList);

    return 0;
}