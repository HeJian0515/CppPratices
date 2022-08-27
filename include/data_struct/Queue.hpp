#include <vector>

using namespace std;

namespace _lc_622 //设计循环队列
{
class MyCircularQueue {
private:
    int front_;
    int rear_;
    int capacity_;
    vector<int> elements_;
    

public:
    MyCircularQueue(int k) {
        capacity_ = k + 1;
        elements_ = vector<int>(capacity_);
        rear_ = front_ = 0;
    }

    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        elements_[rear_] = value;
        rear_ = (rear_ + 1) % capacity_;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        front_ = (front_ + 1) % capacity_;
        return true;
    }

    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return elements_[front_];
    }

    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return elements_[(rear_-1+capacity_) % capacity_];
    }

    bool isEmpty() {
        return rear_ == front_;
    }

    bool isFull() {
        return ((rear_+1) % capacity_) == front_;
    }

};

} // namespace _lc_622 //设计循环队列
