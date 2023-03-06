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

void xd(int){

}

int main(){

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