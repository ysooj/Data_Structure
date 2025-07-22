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

    T * array;      // 실제 데이터를 저장할 동적 배열의 포인터  

public:
    Vector()
    {
        // 초기화
        count = 0;                  // 아직 아무 원소도 없음
        capacity = 1;               // 1개의 원소 저장 가능

        array = new T[capacity];    // 동적 배열 할당
        // 타입 T의 연속된 메모리 공간을 capacity만큼 힙(heap)에 할당한 것.
        // 동적 배열을 만들려면 몇 개의 요소를 저장할지를 미리 알려줘야 한다.
        // 그래야 운영체제가 그만큼의 연속된 메모리 공간을 할당할 수 있다.
    }
};

int main()
{

    return 0;
}