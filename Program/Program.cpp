#include <iostream>

using namespace std;

// --------------------------------------------------------
// [Hash Table] ; 해시 테이블
// 기본적으로 8개의 bucket이 있다.
// 키(key)와 값(value)을 저장하는 자료구조
// 해시 함수를 통해 키를 배열의 인덱스로 변환
// 평균적으로 검색, 삽입, 삭제가 매우 빠름 (O(1))
// 충돌 발생 시 체이닝 또는 오픈 어드레싱으로 해결
// --------------------------------------------------------

template <typename KEY, typename VALUE>

class HashTable
{
private:
    struct Node
    {
        KEY key;
        VALUE value;

        Node * next;
    };

    struct Bucket
    {
        int count;
        Node * head;
    };

    int size;           // bucket의 size
    Bucket * bucket;    // 동적 배열을 만들기 위해 선언.

public:
    HashTable()
    {
        size = 8;

        bucket = new Bucket[size];
    }

    const int & hash_function(unsigned key)  // hashtable의 key는 size 값보다 작아야 하므로.
    {
        int index;

        index = key % size;

        return index;
    }
};

int main()
{
    HashTable <const char *, int> hashtable;

    hashtable.hash_function(10);

    return 0;
}

// 해시 충돌 처리 기법
// 1. 체이닝 (Chaining)
//    - 각 버킷에 리스트를 두어 충돌한 데이터를 저장
// 2. 오픈 어드레싱 (Open Addressing)
//    - 충돌 시 빈 버킷을 찾아 데이터를 저장
//    - 선형 탐사 (Linear Probing): 인접한 다음 버킷부터 순서대로 검사
//    - 제곱 탐사 (Quadratic Probing): 점차 간격을 늘려가며 검사
//    - 이중 해싱 (Double Hashing): 두 번째 해시 함수로 이동 간격 결정


// [다음 주에 할 것]
// - 그래프
// - 레드 블랙 ; 이진 탐색 트리