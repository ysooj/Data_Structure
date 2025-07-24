#include <iostream>

#define SIZE 4  // 큐의 최대 크기 정의

using namespace std;

// --------------------------------------------------------
// [Circular Queue] ; 원형 큐 구현
// 정적 배열을 사용하여 고정 크기의 큐 생성
// 먼저 넣은 데이터가 먼저 나오는 구조 (FIFO: First In, First Out)
// 하나를 비워놓는다. 이유는
// front와 rear가 같을 때 큐가 비어있는지 또는 가득 찼는지를 구분하기 위해서이다.
// 즉, 큐가 가득 찬 상태와 비어있는 상태를 구분하려면 항상 한 칸을 비워두어야 한다.
// --------------------------------------------------------

template <typename T>

class Queue
{
private:
    int rear;           // 데이터가 마지막으로 들어간 위치
    int front;          // 데이터가 처음으로 나오는 위치

    T container[SIZE];  // 큐를 저장할 배열

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
        // 큐가 가득 찼는지 확인 (원형 큐의 조건)
        if (front == (rear + 1) % SIZE)
            // (rear + 1) % SIZE  =>  현재 rear 위치에서 한 칸 앞으로 이동한 인덱스를 구하되, 배열 범위를 넘으면 다시 0부터 시작하도록 순환시킨다는 뜻
        {
            cout << "Circular Queue overflow" << endl;
        }

        else
        {
            // rear를 다음 위치로 이동시키고 데이터 삽입
            rear = (rear + 1) % SIZE;
            container[rear] = data;
        }
    }

    void pop()
    {
        if (empty())
        {
            cout << "Circular Queue is empty" << endl;
        }

        else
        {
            front = (front + 1) % SIZE;

            container[front] = NULL;
        }
    }

    const bool& empty()
    {
        return front == rear;
    }

    const T& peek()
    {
        if (empty())
        {
            exit(1);    // 큐가 비어 있으면 프로그램을 강제 종료
        }
        else
        {
            return container[(front + 1) % SIZE];
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

    cout << queue.empty() << endl;

    while (queue.empty() == false)
    {
        cout << queue.peek() << endl;
        queue.pop();
        cout << "---------------" << endl;
    }

    cout << queue.empty() << endl;

    queue.push(50);
    queue.push(60);
    queue.push(70);

    cout << queue.peek() << endl;

    return 0;
}