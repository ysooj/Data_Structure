#include <iostream>

using namespace std;

// --------------
// [양방향 리스트]
// --------------

template <typename T>

class List
{
private:
    struct Node
    {
        T data;
        Node * next;
        Node * previous;
    };

    int size;       // 생성자에서 초기화

    Node * head;    // 생성자에서 초기화
    Node * tail;    // 생성자에서 초기화

public:
    List()
    {
        size = 0;

        head = nullptr;
        tail = nullptr;
    }

    void push_front(T data)
    {
        Node * newNode = new Node;

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
            Node * deleteNode = head;

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
        Node * newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        newNode->previous = nullptr;

        // 노드가 없을 때
        if (head == nullptr)
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
    list.push_front(5);
    list.push_front(1);

    list.pop_front();
    list.pop_front();
    list.pop_front();
    list.pop_front();

    return 0;
}