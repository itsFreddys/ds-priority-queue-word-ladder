#ifndef _PRIORITY_QUEUE_HPP
#define _PRIORITY_QUEUE_HPP

#include <stdexcept>
#include <iostream>
#include <vector>

class PriorityQueueEmptyException : public std::runtime_error {
public:
    PriorityQueueEmptyException(const std::string &err) : std::runtime_error(err) {}
};

template <typename Object>
class MyPriorityQueue {
private:
    // fill in private member data here
    struct Item {
        Object ob;
        int hvalue = 0;
        bool hExists = false;

        Item() {};
        Item(Object o) {ob = o;};
        Item(Object o, const int h) {ob = o; hvalue = h; hExists = true;};

        bool operator<(const Item& other) const {
//            std::cout<<hvalue<<" "<<other.hvalue<<std::endl;
            if (hExists || other.hExists){
                return hvalue < other.hvalue;
            }
            return ob < other.ob;
        }

        bool operator>(const Item& other) const {
//            std::cout<<hvalue<<" "<<other.hvalue<<std::endl;
            if (hExists || other.hExists){
                return hvalue > other.hvalue;
            }
            return ob > other.ob;
        }
    };
    size_t queue_size = 0;
    std::vector<Item> vect;

    const int left_child_index(int index);
    const int right_child_index(int index);
    const int parent_index(int index);

    void insertion();
    void extraction();
    // create a struct that holds the string/object and holds its huerstic val
    // create an operator overload inside of the struct


public:
    // You also need a constructor and a destructor.
    MyPriorityQueue();
    ~MyPriorityQueue();

    size_t size() const noexcept;
    bool isEmpty() const noexcept;

    void insert(const Object &elem);
    void insert(const Object &elem, int h);

    // Note:  no non-const version of this one.  This is on purpose because
    // the interior contents should not be able to be modified due to the
    // heap property.  This isn't true of all priority queues but
    // for this project, we will do this.
    // min and extractMin should throw PriorityQueueEmptyException if the queue is
    // empty.
    const Object &min() const;

    void extractMin();
};

template <typename Object> MyPriorityQueue<Object>::MyPriorityQueue()
{

}

template <typename Object> MyPriorityQueue<Object>::~MyPriorityQueue()
{

}

template <typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
    return queue_size; // stub
}

template <typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
    return queue_size == 0; // stub
}

template <typename Object>
void MyPriorityQueue<Object>::insert(const Object &elem)
{   struct Item item(elem);
    if (isEmpty()) { vect.push_back(item); queue_size++; return;}

    vect.push_back(item);
    queue_size++;
    // performs the swaps
    insertion();
}

template <typename Object>
void MyPriorityQueue<Object>::insert(const Object &elem, int h)
{   struct Item item(elem, h);
    if (isEmpty()) { vect.push_back(item); queue_size++; return;}

    vect.push_back(item);
    queue_size++;
    // performs the swaps
    insertion();
}

template <typename Object>
void MyPriorityQueue<Object>::insertion(){
    int child = vect.size() - 1;
    int parent = parent_index(child);
    struct Item temp;

    while (child > 0 && vect[child] < vect[parent]){
        temp = vect[parent];
        vect[parent] = vect[child];
        vect[child] = temp;
        child = parent;
        // update parent and child indexes
        parent = parent_index(child);
    }
}

template <typename Object> 
const Object &MyPriorityQueue<Object>::min() const
{
    if (isEmpty()){ throw PriorityQueueEmptyException("empty queue.");}
    return vect[0].ob; // terrible idea, don't actually do this.
}

template <typename Object>
void MyPriorityQueue<Object>::extractMin()
{
    if (isEmpty()) { throw PriorityQueueEmptyException("empty queue."); /*raise error*/ }
    if (queue_size == 1) { vect.pop_back(); queue_size--; return;}
    // delete min
    vect[0] = vect[vect.size() - 1];
    vect.pop_back();
    queue_size--;
    // performs the swaps
    extraction();
}

template <typename Object>
void MyPriorityQueue<Object>::extraction(){
    int current = 0;
    struct Item temp;
    while (current <= static_cast<int>(vect.size())) {
        // check which side is the smallest
        int left = left_child_index(current);
        int right = right_child_index(current);
        int smallest = current;

        if (left < static_cast<int>(queue_size) && vect[left] < vect[smallest]) { smallest = left;}
        if (right < static_cast<int>(queue_size) && vect[right] < vect[smallest]) { smallest = right;}
        if (smallest == current) { break;}

        // std::cout<<"size: "<<queue_size<<" smallest: "<<smallest<<"current: "<<current<<std::endl;
        temp = vect[smallest];
        vect[smallest] = vect[current];
        vect[current] = temp;
        current = smallest;
        // std::cout<<"current: "<<vect[current].ob<<" "<<current<<" size: "<<queue_size<<std::endl;
    }
}

template <typename Object>
const int MyPriorityQueue<Object>::left_child_index(int index)
{
    return (2*index) + 1;
}

template <typename Object>
const int MyPriorityQueue<Object>::right_child_index(int index)
{
    return (2*index) + 2;
}

template <typename Object>
const int MyPriorityQueue<Object>::parent_index(int index){
    return (index - 1) / 2;
}


#endif
