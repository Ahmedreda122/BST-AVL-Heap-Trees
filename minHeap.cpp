#include <iostream>
#include "Student.cpp"
using namespace std;
/*
parent for node => (i-1)/2
left for node   => (2i+1)
right for node  => (2i+2)
*/

class minHeap{
    private:
    int size;
    int capacity = 10;
    Student *heap;
    public:
    minHeap(){
        size = 0;
        heap = new Student[capacity];
    }
    // this function to get child in the left of node
    int left(int node){
        int in = node*2+1;
        return(size <= in?-1:in);
    }
    // this function to get child in the right of node
    int right(int node){
        int in = node*2+2;
        return(size <= in?-1:in);
    }
    // this function to get parent of this node
    int parent(int node){
        int in = (node-1)/2;
        return(size <= in?-1:in);
    }
    void heapifyUp(int childPos){
        int parentPos = parent(childPos);
        if(childPos == 0||heap[parentPos].ID < heap[childPos].ID)return;
        swap(heap[childPos].ID,heap[parentPos].ID);
        heapifyUp(parentPos);
    }
    // insert in heap
    void push(Student student){
        // to recapacity heap to protect memory
         if(capacity == size){
            capacity *= 2;
            Student *newHeap = new Student[capacity];
            for (int i = 0; i < size; i++)newHeap[i] = heap[i];
            delete[] heap;
            heap = newHeap;
        }
        heap[size++] = student;
        heapifyUp(size-1);
    }
    void heapifyDown(int parentPos){
        int childPos = left(parentPos);
        int rightChild = right(parentPos);

        // no children
        if(childPos == -1)return;
        
        // to minimize between left and right child 
        if(rightChild != -1 && heap[childPos].ID > heap[rightChild].ID)
        childPos = rightChild;

        // swap between parent and least child
        if(heap[childPos].ID < heap[parentPos].ID){
            swap(heap[parentPos].ID, heap[childPos].ID);
            heapifyDown(childPos);
        }
    }
    // delete element
    void pop()
    {
        if(size < (capacity/4)){
            capacity = capacity/2;
            Student* newHeap = new Student[capacity];
            for (int i = 0; i < size; i++)newHeap[i] = heap[i];
            delete [] heap;
            heap = newHeap;
        }
        if(isEmpty())return;
        // delete parent then parent -> last child
        heap[0] = heap[--size]; 
        heapifyDown(0);
    }
    bool isEmpty(){
        return(size == 0);
    }
    int sizeHeap(){
        return(size);
    }
    void print(){
        for (int i = 0; i < size; i++)
        {
            cout << heap[i].name << " ";
        }cout << endl;
    }
    ~minHeap(){
        delete[] heap;
    }

};