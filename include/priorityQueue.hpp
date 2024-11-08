#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <queue>
#include <vector>
#include <functional>
struct CompareNode {
    bool operator()(Node* a, Node* b) const {
        return a->fCost() > b->fCost(); // Min-heap based on fCost
    }
};
template<typename T>
class PriorityQueue {
public:
    void push(const T& item) {
        elements.push(item);
    }

    void pop() {
        elements.pop();
    }

    T top() const {
        return elements.top();
    }

    bool empty() const {
        return elements.empty();
    }

private:
    //std::priority_queue<T, std::vector<T>, std::greater<T>> elements;
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> elements;
};

#endif // PRIORITY_QUEUE_HPP