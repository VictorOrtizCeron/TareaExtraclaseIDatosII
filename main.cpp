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
            cout<< "delete working"<<endl;
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
        /**
         * if(Collector.size==0){
         *  automatico facilongo
         * }
         * else{
         *  void * p = collector.head;
         *  Collector.deleteFirst();
         *  return p;
         * }
         * 
        */
        void* p = malloc(sizeof(int*));
        std::cout << "Custom new called, size = " << size << ", pointer = " << p << std::endl;
        cout<< Collector.size <<endl;
        return p;
    }

    void operator delete(void* p){
        
        Collector.insertFirst(p);
        cout << "Custom delete called, pointer = " << p << endl;
        //meter en collector xD
        ::operator delete(p);
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
    cout<< "comienza"<<endl;
    //List *newList = new List();//crea nueva lista
    void * prueba ;

    void * prueba2 ;

    Collector.insertFirst(prueba);
    
    Collector.insertFirst(prueba2);

    printCollectorList(Collector.head);

    Collector.deleteFirst();

    printCollectorList(Collector.head);

    Node * Prueba = new Node(5);//Crea un puntero de nodo  para pruebas únicamente.

    delete Prueba;

    //Liberar memoria pls


    //printf("%p\n",Prueba);//imprime dirección del nodo Prueba
    //Collector->insertFirst(Prueba); //inserta puntero del nodo en collector list
    //Inserción de nodos regulares en lista enlazada de ints
    //newList->insertFirst(1);
    //newList->insertFirst(2,Collector);
    //newList->insertFirst(3,Collector);

    //print de elementos de lista
    //printList(newList->head);
    //cout << "\n";
    //eliminación de primer valor de lista
    //newList ->deleteFirst();
    //comprobación de funcionamiento de deleteFirst
    //printList(newList->head);
    //impresión de punteros de lista collector (Nil significa lista Collector vacía :D )
    //printCollectorList(Collector->head);

    return 0;
}