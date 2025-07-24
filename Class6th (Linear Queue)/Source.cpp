#include <iostream>

#define SIZE 5

using namespace std;

// --------------------------------------------------------
// [Linear Queue] ; 선형 큐. 
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
        rear = 0;
        front = 0;

        for (int i = 0; i < SIZE; i++)
        {
            container[i] = NULL;
        }
    }

    void push(T data)
    {
        // 다 차면 오버플로우 문구 출력
        if (rear >= SIZE)
        {
            cout << "Linear queue overflow" << endl;
        }

        // data 넣고 rear 값을 증가
        else
        {
            container[rear++] = data;
        }

    }

    void pop()
    {
        if (empty())
        {
            cout << "Linear queue is empty" << endl;
        }

        else
        {
            container[front++] = NULL;
        }
    }

    const int& size()
    {
        return rear - front;
    }

    const bool& empty()
    {
        return front == rear;
    }

    // 가장 앞에 있는 데이터를 출력할 때는 peek이라는 함수명을 사용한다.(front보다는 peek을 씀)
    const T& peek()
    {
        // 비어있으면 exit(1) 해준다.
        if (empty())
        {
            exit(1);
        }

        else
        {
            return container[front];
        }
    }
};

int main()
{
    Queue <int> queue;

    queue.push(10);
    queue.push(20);
    queue.push(30);
    queue.push(40);
    queue.push(50);
    queue.push(100000);
    queue.empty();

    cout << queue.size() << endl;

    while (queue.empty() == false)
    {
        cout << queue.peek() << endl;
        queue.pop();

        cout << "----------------" << endl;
    }

    cout << queue.size() << endl;
    queue.empty();

    return 0;
}

// stack이 비워진 다음에 다시 data를 넣으려 하면 터진다. 왜 그런 지는 집 가서 다시 영상으로 확인하자.