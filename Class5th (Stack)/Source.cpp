#include <iostream>

using namespace std;

// ------------------------
// [Stack] ; 컨테이너 어댑터.
// 마지막에 넣은 것이 가장 먼저 나오는 구조. (LIFO: Last In, First Out)
// ------------------------

template <typename T>

class Stack
{
private:
    int capacity;   // 스택이 저장할 수 있는 최대 데이터 개수
    int highset;    // 스택에서 가장 위에 있는 데이터의 위치를 나타내는 인덱스
    // 스택이 비어있을 때는 '위에 있는 데이터가 없음'을 표시하기 위해 -1로 초기화한다.
    T* container;  // 실제 데이터를 저장하는 배열 포인터

public:
    Stack()
    {
        capacity = 0;           // 초기 용량도 0
        highset = -1;           // 스택이 비어있음을 의미하기 위해 -1로 설정
        // (즉, 유효한 인덱스는 0부터 시작하므로 -1은 '아무것도 없다'는 뜻)
        container = nullptr;    // 배열 포인터는 아직 할당된 게 없으니 nullptr로 초기화
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
        for (int i = 0; i < highset + 1; i++)
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

        // capacity 값보다 highset + 1 값이 더 크거나 같을 때 resize 함수 호출
        else if (highset + 1 >= capacity)
        {
            resize(capacity * 2);
        }

        container[++highset] = data;
    }

    void pop()
    {
        // 값이 없는 상태(비어있는 상태)면 문구 출력
        if (empty())
        {
            cout << "Stack is empty" << endl;
        }

        // 가장 마지막에 들어간 data를 NULL로 만들고, highset 값을 줄인다.
        else
        {
            container[highset--] = NULL;
        }
    }

    const bool& empty()
    {
        return highset <= -1;
    }

    const int& size()
    {
        return highset + 1;
    }

    const T& top()
    {
        return container[highset];
    }

    ~Stack()
    {
        if (container != nullptr)
        {
            delete[] container;
        }
    }
};

int main()
{
    Stack <int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);

    cout << stack.size() << endl;

    // stack이 비어있지 않다면
    while (stack.empty() == false)
    {
        cout << stack.top() << endl;

        stack.pop();
    }

    stack.pop();

    return 0;
}