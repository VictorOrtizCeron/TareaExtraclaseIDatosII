#include <iostream>
using namespace std;


class Node {


private:
    int valor;
    Node* NextPTR;
public:
    int getValor(){
        return valor;
    }
    void setValor(int num){
        valor = num; 
    }
    Node* getNext(){
        return NextPTR;
    }
    void setNext(Node* Next){
        NextPTR = Next;
    }
};

void printList(Node*n){
    while(n!= NULL){
        cout<< n->getValor()<< endl;
        n = n->getNext();
    }
}

int main(){

    Node*head = new Node();
    Node*second = new Node();
    Node*third = new Node();

    head->setValor(1); 
    head -> setNext(second);
    second->setValor(2);
    second -> setNext(third);
    third -> setValor(3);
    third -> setNext(NULL);

    printList(head);
    cout << "ay lmaoo";
    return 0;
}