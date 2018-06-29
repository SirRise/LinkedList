#include <array>
#include <memory>
#include <string>
#include <iostream>

template<typename T>
class DLL {

    unsigned int nodes;

    struct Node {
        T value;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;
        Node(T val) : value(val), next(nullptr) {}
        Node() {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

public:
    DLL(T val) {
        head = std::make_shared<Node>();
        tail = std::make_shared<Node>();
    }

    ~DLL() {
        delete head;
        delete tail;
    }

    void push(T val) {
        std::shared_ptr<Node> node = std::make_shared<Node>(val);
        node->prev = tail;
        tail->next = node;
        nodes++;
        if (nodes == 1) head = node;    
    }

    T pop() {
        if (tail == nullptr) throw ("No value inside list");
        T t_val = tail->value;
        tail = tail->prev;
        tail->next = nullptr;
        nodes--;
        return t_val;
    }

    T index(int index) const {
        if (index > nodes-1 || index < 0) throw("Index out of bounds");
        std::shared_ptr<Node> p_node;
        while (index --> 0) {
            p_node = p_node->next;
        }
        return p_node->value;
    }

    template<typename R, typename I>
    R forEach(I&& lambda) const {
        std::shared_ptr<Node> p_node = std::make_shared<Node>(this->head);
        for (unsigned int x = 0; x < nodes; x++) {
            lambda(*p_node);
            p_node = p_node->next;
        }
    }

    void operator<<(T val) {
        this->push(val);
    }

    T operator[](int index) const {
        this->index(index);
    }

};

auto main() -> int {
    auto list = new DLL<int>(5);
    std::cout << list->index(0);
}