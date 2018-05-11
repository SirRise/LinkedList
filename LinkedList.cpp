#include <iostream>
#include <memory>
template<typename T>
class LinkedList{
    struct Node {
        T value;
        Node *next;
        int index;
        std::weak_ptr<Node> prev;
    };

    int nodeIndex;
    Node *start;
    Node *head;

public:
    LinkedList(){
        head = NULL;
    }

    ~LinkedList(){
        Node *next = head;
        while(next) {
            Node *deleteMe = next;
            next = next->next;
            delete deleteMe;
        }
    }

    void push(T val){
        Node *n = new Node();
        n->value = val;
        n->index = nodeIndex++;
        if (n->index == 0) start = n;
        n->next = head;
        head = n;
    }

    T pop(){
        Node *n = head;
        T ret = n->value;
        head = head->next;
        delete n;
        return ret;
    }

    T operator[](int &x) const {
        if (x < 0 ||x > nodeIndex) return NULL;
        Node *currentNode = start;
        while (currentNode->index != x) {
            currentNode = currentNode->next;
        }
        return currentNode->value;
    }

    void operator<<(T x) {
        push(x);
    }
};

int main() {
    LinkedList<int> list;

    list << 5;
    list << 10;
    list << 20;

    std::cout << list.pop() << std::endl;
    std::cout << list.pop() << std::endl;
    std::cout << list.pop() << std::endl;
    std::cin.get();
    return 0;
}