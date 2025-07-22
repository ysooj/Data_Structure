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
    int count;      // 현재 스택에 들어있는 데이터 개수
    int capacity;   // 스택이 저장할 수 있는 최대 데이터 개수
    int highset;    // 스택에서 가장 위에 있는 데이터의 위치를 나타내는 인덱스
                    // 스택이 비어있을 때는 '위에 있는 데이터가 없음'을 표시하기 위해 -1로 초기화한다.
    T * container;  // 실제 데이터를 저장하는 배열 포인터

public:
    Stack()
    {
        count = 0;              // 데이터가 없으니 개수는 0
        capacity = 0;           // 초기 용량도 0
        highset = -1;           // 스택이 비어있음을 의미하기 위해 -1로 설정
                                // (즉, 유효한 인덱스는 0부터 시작하므로 -1은 '아무것도 없다'는 뜻)
        container = nullptr;    // 배열 포인터는 아직 할당된 게 없으니 nullptr로 초기화
    }

    ~Stack()
    {
        if (container != nullptr)
        {
            delete [] container;
        }
    }
};

int main()
{

    return 0;
}