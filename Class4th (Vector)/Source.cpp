#include <iostream>

using namespace std;

// --------------------------
// [stl의 vector] ; 동적 배열
// --------------------------

template <typename T>

class Vector
{
private:
    int count;      // 현재 저장된 원소의 개수
    int capacity;   // 할당된 메모리 공간의 크기 (즉, 배열의 최대 크기)

    T* container;  // 실제 데이터를 저장할 동적 배열의 포인터  

public:
    Vector()
    {
        count = 0;
        capacity = 0;
        container = nullptr;
    }

    // capacity보다 count가 커지면 이 함수를 불러와야 한다.
    void resize(int newSize)
    {
        // 1. capacity에  새로운 size 값을 저장합니다.
        capacity = newSize;

        // 2. 새로운 포인터 변수를 생성해서 새롭게 만들어진 메모리 공간을 가리키도록 합니다.
        T * temporary = new T[capacity];

        // 3. 새로운 메모리 공간의 값을 초기화합니다.
        for (int i = 0; i < capacity; i++)
        {
            temporary[i] = NULL;
        }

        // 4. 기존 배열에 있는 값을 복사해서 새로운 배열에 넣어줍니다.
        for (int i = 0; i < count; i++)
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

    void push_back(T data)
    {
        if (capacity <= 0)
        {
            resize(1);  // 최초 할당: 배열이 비어 있을 경우, 용량을 1로 설정
        }

        else if (count >= capacity)
        {
            resize(capacity * 2);   // 용량 부족 시 2배 확장 (동적 배열의 일반적 전략)
        }

        container[count++] = data;  // 현재 count 인덱스에 data 삽입 후 count 증가
    }

    void pop_back()
    {
        // data가 하나도 없을 때 : "Vector is empty"
        if (count <= 0)
        {
            cout << "Vector is empty" << endl;
        }

        // data가 있을 때 : 지울 인덱스에 접근해서 NULL로 값을 바꿔준다.
        else
        {
            container[--count] = NULL;
        }
    }

    const int& size()
    {
        return count;
    }

    const T& operator [] (const int& index)
    {
        return container[index];
    }

    ~Vector()
    {
        if (container != nullptr)
        {
            delete[] container;
        }
    }
};

int main()
{
    Vector <int> vector;

    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);
    vector.push_back(40);

    vector.pop_back();

    for (int i = 0; i < vector.size(); i++)
    {
        cout << vector[i] << endl;
    }

    vector.pop_back();
    vector.pop_back();
    vector.pop_back();
    vector.pop_back();

    return 0;
}