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

        Node* next;
    };

    struct Bucket
    {
        int count;
        Node* head;
    };

    int size;           // bucket의 size
    Bucket* bucket;    // 동적 배열을 만들기 위해 선언. 포인터. Bucket 구조체를 요소로 갖는 배열

public:
    HashTable()
    {
        size = 8;

        bucket = new Bucket[size];
        // bucket => Bucket 구조체 배열을 가리키는 포인터
        // bucket[i] => i번째 Bucket 구조체(실제 객체, 포인터 아님)
        // bucket[i].head => i번째 버킷의 연결 리스트 시작 노드
        for (int i = 0; i < size; i++)
        {
            bucket[i].head = nullptr;
            bucket[i].count = 0;
        }
    }

    unsigned int hash_function(KEY key)  // hashtable의 key는 size 값보다 작아야 하므로.
    {
        return (unsigned int)key % size;
    }

    void insert(KEY key, VALUE value)
    {
        // 1. hash_function 함수를 통해서 값을 받는 임시 변수
        int hashIndex = hash_function(key);

        // 2. 새로운 노드를 생성합니다.
        Node* newNode = new Node;

        newNode->key = key;
        newNode->value = value;
        newNode->next = nullptr;    // insert 함수는 push_front같은 역할을 하기 때문에 뒤에 오는 포인터는 nullptr인 것.

        // 3. 노드가 비어있다면
        if (bucket[hashIndex].count == 0)
        {
            // bucket[hashIndex]의 head 포인터가 newNode를 가리키게 합니다.
            bucket[hashIndex].head = newNode;
        }

        // 4. 노드가 1개라도 존재한다면
        else
        {
            newNode->next = bucket[hashIndex].head;
            bucket[hashIndex].head = newNode;
        }

        // bucket[hashIndex]의 count를 증가시킵니다.
        bucket[hashIndex].count++;
    }

    // 처음으로 발견한 key만 삭제하는 함수
    void erase(KEY key)
    {
        // 1. hash_function 함수를 통해서 값을 받는 임시 변수
        int hashIndex = hash_function(key);

        // 2. Node를 탐색할 수 있는 포인터 변수 선언
        Node* currentNode = bucket[hashIndex].head;

        // 3. 이전 Node를 저장할 수 있는 포인터 변수
        Node* previousNode = nullptr;

        // 4. currentNode가 nullptr과 같다면(해당하는 key에 대해 지울 것이 없는 경우) 함수를 종료합니다.
        while (currentNode != nullptr)
        {
            // 5. 해당하는 key에 대해 지울 것이 있는 경우
            // [문자열의 주소값만 비교]
            // if (currentNode->key == key)
            // [문자열 내용 비교]
            if (currentNode->key == key)
            {
                // 지울 게 head라면
                // head는 currentNode->next가 되며, currentNode를 지운다.
                if (previousNode == nullptr)
                {
                    bucket[hashIndex].head = currentNode->next;
                }
                // key 값을 찾았다면
                // previousNode->next는 currentNode->next가 되며, currentNode를 지운다.
                else
                {
                    previousNode->next = currentNode->next;
                }

                delete currentNode;
                bucket[hashIndex].count--;

                cout << "Key erased : " << key << endl;
                return;  // 삭제 후 함수 종료
            }

            // key 값을 찾지 못했다면
            // previousNode를 currentNode로 하고 currentNode는 다음으로 넘겨준다.
            previousNode = currentNode;
            currentNode = currentNode->next;
        }

        // 다 살펴봤는 데도 key를 못 찾았다면
        // key를 찾지 못했다는 문구를 출력한다.
        // 여기까지 왔다는 건 key를 못 찾았다는 뜻
        cout << "Not Key Found" << endl;
        return;
    }

    // 중복되는 key를 모두 삭제하는 함수
    void erase_all(KEY key)
    {
        int hashIndex = hash_function(key);
        Node * currentNode = bucket[hashIndex].head;
        Node * previousNode = nullptr;
        
        while (currentNode != nullptr)
        {
            if (currentNode->key == key)  // 문자열 비교
            {
                Node * nextNode = currentNode->next;

                if (previousNode == nullptr)
                {
                    bucket[hashIndex].head = nextNode;
                }
                else
                {
                    previousNode->next = nextNode;
                }

                delete currentNode;
                bucket[hashIndex].count--;

                currentNode = nextNode;

                // 해당하는 key를 삭제할 때마다 메시지 출력
                cout << "Key Deleted : " << key << endl;
            }

            else
            {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
        }

        // 모든 노드가 삭제되어 버킷이 빈 상태
        if (bucket[hashIndex].head == nullptr || bucket[hashIndex].count == 0)
        {
            cout << "All matching keys deleted. Bucket is now empty." << endl;
        }
        // 삭제된 노드가 하나도 없는 경우
        else if (bucket[hashIndex].head != nullptr)
        {
            cout << "Not Key Found" << endl;
        }
    }

    // bucket의 size를 출력하는 함수
    const int& bucket_count()
    {
        return size;
    }
};

int main()
{
    HashTable <const char*, int> hashtable;

    //  cout << hashtable.hash_function("Operator") << endl;
    //  cout << hashtable.hash_function("Yahoo") << endl;
    //  cout << hashtable.hash_function("hello") << endl;
    //  cout << hashtable.hash_function("hi") << endl;
    //  cout << hashtable.hash_function("Apple") << endl;

    hashtable.insert("Abyssal Mask", 3000);
    hashtable.insert("Bami's Cinder", 1000);
    hashtable.insert("Chain Vest", 800);

    // 삭제 시도 - 존재하는 키
    hashtable.erase("Bami's Cinder");

    // 삭제 시도 - 존재하지 않는 키
    hashtable.erase("Nonexistent Key");

    // 중복 key 삽입 후 모두 삭제해보기
    hashtable.insert("Chain Vest", 900);
    hashtable.insert("Chain Vest", 850);
    
    hashtable.erase_all("Chain Vest");

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