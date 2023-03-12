#include <iostream>
using namespace std;

class Node;//Inicialización de clase node que previene un problema de dependencias circulares
//Clase de nodos de Collector
class collectorNode{
    public:
        void * NodePTR;
        collectorNode * NextCollectorPTR;

    collectorNode(void* DeletedNodePTR){

        this -> NodePTR = DeletedNodePTR;
        this -> NextCollectorPTR = NULL;
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

    void insertFirst( void* DeletedNodePTR){
        
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

collectorList Collector;

class Node {

public:
    int valor;
    Node* NextPTR;

    Node(int valor) {//constructor de la clase nodo 
        this->valor= valor;
        this->NextPTR = nullptr;
    }

    //Sobrecarga del método New para el Nodo regular. Aqui se debe validar el caso del nuevo nodo y asignar la memoria correspondiente
    void* operator new(size_t size) {
        
        //Si collector.size == o ; no mames malloc. Else, asignar de collector.
        if(Collector.size == 0){
            
            void* p = malloc(sizeof(size));
            return p;
        }else{
            
            void* p = Collector.head ->NodePTR;
            Collector.deleteFirst();
            return p;
        }
        
    }

    void operator delete(void* p){
        
        Collector.insertFirst(p);
        free(p);
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

    void insertFirst(int valor){
        Node* newNode = new  Node(valor);
        newNode -> NextPTR = head;
        head = newNode;
        size ++;
        }

    void deleteFirst(){
        if(head != nullptr){
            //Node* Temp = new (Collector) Node(head->valor);
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
        cout<< "Número almacenado en el nodo: "<<n->valor<< "  , Puntero del nodo: "<< n << endl;
        n = n-> NextPTR;
    }
}
//método que imprime lista de direcciones de nodos en Collector List
void printCollectorList(collectorNode*n){
    if(Collector.size == 0){
        cout<< "Collector vacio"<<endl;
    }
    else{
        while(n!= NULL){
            cout<< n->NodePTR << endl;
            n = n-> NextCollectorPTR;
        }
    }
}
//Main de pruebas
int main(){
    
    cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<< "Test con nodos"<<endl;
    cout<<""<<endl;

    void * prueba = malloc(sizeof(Node*));

    void * prueba2 = malloc(sizeof(Node*));

    Collector.insertFirst(prueba);
    
    Collector.insertFirst(prueba2);

    cout<< "Print 1 de Collector list:"<<endl;

    printCollectorList(Collector.head);
    cout<<""<<endl;
    cout<<"Creación primer nodo"<<endl;
    Node * NodoTest1 = new Node(1);
    cout<< "Puntero de primer nodo: "<<NodoTest1<<endl;
    cout<<""<<endl;
    cout<< "Print 2 de Collector list:"<<endl;
    printCollectorList(Collector.head);
    cout<<""<<endl;
    cout<<"Creación segundo nodo"<<endl;
    Node * NodoTest2 = new Node(2);
    cout<< "Puntero de segundo nodo: "<<NodoTest2<<endl;
    cout<<""<<endl;
    cout<< "Print 3 de Collector list:"<<endl;
    printCollectorList(Collector.head);
    cout<<""<<endl;
    cout<<"Creacion de tercer nodo cuando collector está vacío"<<endl;
    Node*NodoTest3 = new Node(3);
    cout<<"Puntero de tercer nodo: "<< NodoTest3<<endl;
    cout<<""<<endl;
    cout<<"delete tercer nodo:"<< NodoTest3<<endl;
    delete NodoTest3;
    cout<<""<<endl;
    cout<< "Print 4 de Collector list:"<<endl;
    printCollectorList(Collector.head);
    cout<<""<<endl;
    cout<<""<<endl;
    //Inicio de test con lista enlazada
    Collector.deleteFirst();
    cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<< "Test con Lista Enlazada"<<endl;

    cout<<""<<endl;
    
    List * listaEnlazada = new List();

    listaEnlazada->insertFirst(1);
    listaEnlazada->insertFirst(2);
    listaEnlazada->insertFirst(3);

    printCollectorList(Collector.head);
    cout<<""<<endl;
    cout<< "Print de elementos int en lista enlazada"<< endl;
    printList(listaEnlazada->head);
    cout<<""<<endl;

    cout<< "Print de elementos int en lista enlazada despues de un deleteFirst()"<< endl;
    listaEnlazada->deleteFirst();
    printList(listaEnlazada->head);
    cout<<""<<endl;

    cout<<"Print de Collector:"<< endl;
    printCollectorList(Collector.head);
    cout<<""<<endl;

    cout<< "Print de elementos int en lista enlazada despues de agregar un 4"<< endl;
    listaEnlazada->insertFirst(4);
    printList(listaEnlazada->head);
    cout<<""<<endl;

    cout<<"Print de Collector:"<< endl;
    printCollectorList(Collector.head);
    cout<<""<<endl;

    return 0;
}