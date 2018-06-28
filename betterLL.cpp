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
    }

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

public:
    DLL(T val) {
        head = std::make_shared<Node>(val);
        tail = head;
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
    }

    T pop() {
        T t_val = tail->value;
        tail = tail->prev;
        tail->next = nullptr;
        return t_val;
    }

    template<typename I, typename R>
    R forEach(I&& lambda) {
        std::shard_ptr<Node> p_node = std::make_shared<Node>(head);
        for (unsigned int x = 0; x < nodes; x++) {
            lambda(*p_node);
            p_node = p_node->next;
        }
    }

    void operator<<(T val) {
        push(val);
    }

    T operator[](int index) const {
        if (index > nodes-1) throw("Index out of bounds");
        std::shared_ptr<Node> p_node;
        while (index) {
            p_node = p_node->next;
        }
        return p_node->val;
    }

};

auto main() -> int {
    auto list = *(new DLL<int>(5));
    std::cout << list[0];
}