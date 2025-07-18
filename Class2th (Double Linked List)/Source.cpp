#include <iostream>

using namespace std;

// ---------------
// [양방향 리스트]
// ---------------

template <typename T>

class List
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* previous;
    };

    int size;       // 생성자에서 초기화

    Node* head;    // 생성자에서 초기화
    Node* tail;    // 생성자에서 초기화

public:
    List()
    {
        size = 0;

        head = nullptr;
        tail = nullptr;
    }

    void push_front(T data)
    {
        Node* newNode = new Node;

        newNode->data = data;
        newNode->next = nullptr;
        newNode->previous = nullptr;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }

        else
        {
            head->previous = newNode;
            newNode->next = head;

            head = newNode;
        }

        size++;
    }

    void pop_front()
    {
        // 노드가 없을 때
        if (head == nullptr)
        {
            cout << "Linked list is empty" << endl;
        }

        // 노드가 하나만 있을 때
        // head와 tail을 nullptr로 초기화시켜주기
        else
        {
            Node* deleteNode = head;

            if (head == tail)
            {
                head = nullptr;
                tail = nullptr;
            }

            // 노드가 둘 이상 있을 때
            // head의 next로 head를 옮겨주기
            else
            {
                deleteNode->next->previous = nullptr;

                head = head->next;
            }

            delete deleteNode;

            size--;
        }
    }

    void push_back(T data)
    {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        newNode->previous = nullptr;

        // 노드가 없을 때
        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }

        // 노드가 있을 때
        else
        {
            // 새 노드를 기존 tail 뒤에 연결
            tail->next = newNode;
            newNode->previous = tail;

            // tail 포인터를 새 노드로 갱신
            tail = newNode;
        }

        size++;
    }

    void pop_back()
    {
        // 리스트가 비어있는 경우
        if (tail == nullptr)
        {
            cout << "Linked list is empty" << endl;
        }

        else
        {
            // 삭제할 노드를 미리 저장
            Node* deleteNode = tail;

            // 노드가 하나만 있는 경우
            if (head == tail)
            {
                head = nullptr;
                tail = nullptr;
            }

            // 노드가 둘 이상 있는 경우
            else
            {
                tail->previous->next = nullptr;

                tail = tail->previous;
            }

            delete deleteNode;
        }

        size--;
    }

    void remove(T data)
    {
        Node* deleteNode = head;
        // nextNode는 nullptr로 초기화.
        Node* nextNode = nullptr;

        while (deleteNode != nullptr)
        {
            if (deleteNode->data == data)
            {
                // 찾는 data가 첫 번째 노드일 때는 pop_front 함수 사용하기
                if (deleteNode == head)
                {
                    deleteNode = deleteNode->next;

                    pop_front();
                }

                // 맨마지막 노드를 지울 때는 pop_back 함수 쓰고 deleteNode를 nullptr로 초기화시켜주기
                else if (deleteNode == tail)
                {
                    pop_back();

                    deleteNode = nullptr;
                }

                // 찾는 data가 중간에 있는 경우
                // deleteNode의 previous가 deleteNode의 next를 가리키게 한다.
                else
                {
                    deleteNode->previous->next = deleteNode->next;

                    deleteNode->next->previous = deleteNode->previous;

                    nextNode = deleteNode->next;

                    delete deleteNode;

                    deleteNode = nextNode;

                    size--;
                }
            }

            // 찾고자 하는 데이터가 아니면 다음 노드로 이동
            else
            {
                deleteNode = deleteNode->next;
            }
        }
    }

    bool empty()
    {
        return (head == nullptr);
    }

    ~List()
    {
        while (head != nullptr)
        {
            pop_front();
        }
    }
};

int main()
{
    List <int> list;

    list.push_front(10);
    list.push_front(20);
    list.push_front(10);

    list.push_back(30);
    list.push_back(10);

    //list.pop_front();
    //list.pop_front();
    //list.pop_front();
    //list.pop_front();
    //
    //list.pop_back();

    list.remove(10);

    list.pop_back();
    list.pop_front();


    cout << list.empty() << endl;

    return 0;
}