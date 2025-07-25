#include <iostream>

using namespace std;

// --------------------------------------------------------
// [Priority Queue] ; 우선순위 큐
// 일반적인 큐(FIFO)와는 달리, 요소들이 우선순위에 따라 처리됨
// 가장 높은 우선순위를 가진 요소가 가장 먼저 나감
// 내부적으로 보통 힙(Heap)을 사용하여 구현 (최대 힙 또는 최소 힙)
// 부모 노드의 우선순위가 자식 노드보다 높도록 구성
// 동적 배열(또는 벡터)을 통해 힙 트리를 구성할 수 있음
// --------------------------------------------------------

template <typename T>

class PriorityQueue
{
private:
    int index;
    int capacity;

    T* container;
public:
    PriorityQueue()
    {
        index = 0;
        capacity = 0;
        container = nullptr;
    }

    void resize(int newSize)
    {
        // 1. capacity에  새로운 size 값을 저장합니다.
        capacity = newSize;

        // 2. 새로운 포인터 변수를 생성해서 새롭게 만들어진 메모리 공간을 가리키도록 합니다.
        T* temporary = new T[capacity];

        // 3. 새로운 메모리 공간의 값을 초기화합니다.
        for (int i = 0; i < capacity; i++)
        {
            temporary[i] = NULL;
        }

        // 4. 기존 배열에 있는 값을 복사해서 새로운 배열에 넣어줍니다.
        for (int i = 0; i < index; i++)
        {
            temporary[i] = container[i];
        }

        //5. 기존 배열의 메모리를 해제합니다. (if문을 쓰지 않고 그냥 'delete [] container;' 이라고 해도 된다고 한다.)
        if (container != nullptr)
        {
            delete[] container;
        }

        // 6. 기존에 배열을 가리키던 포인터 변수의 값을 새로운 배열의 시작 주소로 가리킵니다.
        container = temporary;
    }

    void push(T data)
    {
        if (capacity <= 0)
        {
            resize(1);
        }

        else if (index >= capacity)
        {
            resize(capacity * 2);
        }

        container[index++] = data;

        int child = index - 1;
        int parent = (child - 1) / 2;

        while (child > 0)
        {

            if (container[child] > container[parent])
            {
                std::swap(container[child], container[parent]);
            }
            child = parent;
            parent = (child - 1) / 2;
        }
    }

    void pop()
    {
        if (index <= 0)
        {
            cout << "Priority Queue is empty" << endl;
        }

        else
        {
            container[0] = container[--index];
            container[index] = NULL;

            int parent = 0;

            while (parent * 2 + 1 < index)
            {
                int child = parent * 2 + 1;

                if (container[child] < container[child + 1])
                {
                    child++;
                }

                if (container[child] < container[parent])
                {
                    break;
                }

                else
                {
                    std::swap(container[parent], container[child]);

                    parent = child;
                }
            }
        }
    }

    const bool& empty()
    {
        return index <= 0;
    }

    const int& size()
    {
        return index;
    }

    const T& top()
    {
        if (empty())
        {
            exit(1);
        }
        else
        {
            return container[0];
        }
    }

    ~PriorityQueue()
    {
        if (container != nullptr)
        {
            delete[] container;
        }
    }
};

int main()
{
    PriorityQueue <int> priorityQueue;

    priorityQueue.push(17);
    priorityQueue.push(31);
    priorityQueue.push(9);
    priorityQueue.push(15);

    while (priorityQueue.empty() == false)
    {
        cout << priorityQueue.top() << endl;

        priorityQueue.pop();
    }

    priorityQueue.pop();

    return 0;
}