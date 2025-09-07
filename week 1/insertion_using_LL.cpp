#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val): data(val), next(nullptr) {}
};

Node* insertionSort(Node* head) {
    if(!head || !head-> next) {
        return head;
    }
    Node* sorted = nullptr;

    while(head) {
        Node* curr = head;
        head = head-> next;
        if(!sorted || curr-> data< sorted->data){
            curr->next = sorted;
            sorted = curr;
        } else{
            Node* temp = sorted;

            while(temp->next && temp->next->data < curr-> data){
                temp = temp->next;
            }
            curr->next = temp->next;
            temp->next = curr;
        }
    }
    return sorted;
}

void printList(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

void insertAtEnd(Node*& head, int val) {
    Node* newNode = new Node(val);
    if(!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while(temp->next) temp = temp->next;
    temp->next = newNode;
}

int main(){
    Node* head = nullptr;
    cout << "enter n: ";
    int n;
    cin >> n;
    cout << "enter elements: ";
    int num;
    for(int i = 0; i<n; i++){
        cin >> num;
        insertAtEnd(head, num);
    }
    cout << "Original List: ";
    printList(head);
    head = insertionSort(head);

    cout << "Sorted List: ";
    printList(head);
}