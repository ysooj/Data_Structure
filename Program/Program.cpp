#include <iostream>

using namespace std;

// --------------------------
// [stl의 vector] ; 동적 배열
// --------------------------

template <typename T>

class Vector
{
private:
    int count;
    int capacity;

    T * array;

public:
    Vector()
    {
        count = 0;
        capacity = 1;

        array = T[capacity];
    }
};

int main()
{

    return 0;
}