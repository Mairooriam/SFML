#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <queue>
#include <vector>
#include <functional>

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
    std::priority_queue<T, std::vector<T>, std::greater<T>> elements;
};

#endif // PRIORITY_QUEUE_HPP