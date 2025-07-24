#include <iostream>

#define SIZE 4  // 큐의 최대 크기 정의

using namespace std;

// --------------------------------------------------------
// [Queue]
// 원형 큐 (Circular Queue)의 구현
// 정적 배열을 사용하여 고정 크기의 큐 생성
// 먼저 넣은 데이터가 먼저 나오는 구조 (FIFO: First In, First Out)
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
        if ((rear + 1) % SIZE == front)
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

};

int main()
{
   

    return 0;
}