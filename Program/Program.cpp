#include <iostream>

#define SIZE 4

using namespace std;

// --------------------------------------------------------
// [Queue]
// 원형 큐. Linear
// 정적 배열
// 먼저 넣은 것이 먼저 나오는 구조. (FIFO: First In, First Out)
// --------------------------------------------------------

template <typename T>

class Queue
{
private:
    int rear;
    int front;

    T container[SIZE];

public:
    Queue()
    {
        rear = SIZE - 1;
        front = SIZE - 1;

        for (int i = 0; i < SIZE; i++)
        {
            container[i] = NULL;
        }
    }

    void push(T data)
    {
        if ((rear + 1) % SIZE == front)
        {
            cout << "Circular Queue overflow" << endl;
        }

        else
        {
            rear = (rear + 1) % SIZE;
            container[rear] = data;
        }
    }

};

int main()
{
   

    return 0;
}