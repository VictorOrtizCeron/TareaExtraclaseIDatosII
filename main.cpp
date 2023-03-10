#include <iostream>
using namespace std;

class Node;//Inicialización de clase node que previene un problema de dependencias circulares
//Clase de nodos de Collector
class collectorNode{
    public:
        Node * NodePTR;
        collectorNode * NextCollectorPTR;

    collectorNode(Node* DeletedNodePTR){

        this -> NodePTR = DeletedNodePTR;
        this -> NextCollectorPTR = nullptr;
    }
};
//Clase de lista Collector
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
//Clase Node para lista de ints
class Node {

public:
    int valor;
    Node* NextPTR;

    Node(int valor) {//constructor de la clase nodo 
        this->valor= valor;
        this->NextPTR = nullptr;
    }
    //Sobrecarga del método New para el Nodo regular. Aqui se debe validar el caso del nuevo nodo y asignar la memoria correspondiente
    void* operator new(size_t size, collectorList *Collector) {
        void* p = ::operator new(size);
        std::cout << "Custom new called, size = " << size << ", pointer = " << p << std::endl;
        printf("%p \n", Collector -> head);
        return p;
    }
};
// Clase de List
class List{

public: 

    Node * head;

    int size;
    
    List(){
        head = NULL;
        size = 0;
    }

    void insertFirst(int valor , collectorList* Collector){
        Node* newNode = new (Collector) Node(valor);
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
//método que imprime lista de ints
void printList(Node*n){
    while(n!= NULL){
        cout<< n->valor << endl;
        n = n-> NextPTR;
    }
}
//método que imprime lista de direcciones de nodos en Collector List
void printCollectorList(collectorNode*n){
    while(n!= NULL){
        cout<< n->NodePTR << endl;
        n = n-> NextCollectorPTR;
    }
}
//Main de pruebas
int main(){

    List *newList = new List();//crea nueva lista

    collectorList*Collector = new collectorList();//crea nueva lista collector
    Node * Prueba = new (Collector) Node(5);//Crea un puntero de nodo  para pruebas únicamente.

    printf("%p\n",Prueba);//imprime dirección del nodo Prueba
    Collector->insertFirst(Prueba); //inserta puntero del nodo en collector list
    //Inserción de nodos regulares en lista enlazada de ints
    newList->insertFirst(1,Collector);
    newList->insertFirst(2,Collector);
    newList->insertFirst(3,Collector);

    //print de elementos de lista
    printList(newList->head);
    cout << "\n";
    //eliminación de primer valor de lista
    newList ->deleteFirst();
    //comprobación de funcionamiento de deleteFirst
    printList(newList->head);

    //impresión de punteros de lista collector (Nil significa lista vacía :D )
    printCollectorList(Collector->head);

    return 0;
}