#include <iostream>

using namespace std;

// ------------------
// [원형 연결 리스트]
// ------------------

// [규칙]
// head는 항상 "마지막 노드"를 가리킴
// head->next는 항상 "처음 노드"를 가리킴 (즉, 첫 번째 삽입된 노드)

template <typename T>

class List
{
private:
    struct Node
    {
        T data;
        Node* next;
    };

    int size;
    Node* head;

public:
    List()
    {
        size = 0;
        head = nullptr;
    }

    void push_back(T data)
    {
        Node* newNode = new Node;
        newNode->data = data;

        // 어짜피 if문과 else문에서 바로 쓰일 것이기 때문에 굳이 nullptr을 넣어주지 않아도 된다.
        // newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;

            newNode->next = head;
        }

        else
        {
            // newNode가 처음 노드인 head->next를 가리킴
            // 새 노드를 처음 노드 앞으로 연결
            newNode->next = head->next;

            // head의 next가 newNode를 가리키게 함
            // 현재 마지막 노드가 새 노드를 가리킴
            head->next = newNode;

            // 새 노드를 마지막 노드(head)로 설정
            head = newNode;
        }

        size++;
    }

    void push_front(T data)
    {
        Node* newNode = new Node;
        newNode->data = data;
        // 마찬가지로 아래의 조건문들에서 newNode->next를 바로 설정할 것이기 때문에 초기화하지 않아도 된다.
        // newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;

            newNode->next = head;
        }

        else
        {
            newNode->next = head->next;

            head->next = newNode;
        }

        size++;
    }

    void pop_front()
    {
        // 하나도 없을 때 : 리스트가 비어있다는 문구를 출력한다.
        if (head == nullptr)
        {
            cout << "Linked list is empty" << endl;
        }

        else
        {
            Node* deleteNode = head->next;

            // 하나만 있을 때 : head는 nullptr을 가리키면 된다.
            if (head == head->next)
            {
                head = nullptr;
            }

            // 둘 이상 있을 때 : head->next는 지울 노드의 next를 가리키면 된다.
            else
            {
                head->next = deleteNode->next;
            }

            delete deleteNode;

            size--;
        }
    }

    void pop_back()
    {
        // 하나도 없을 때 : 리스트가 비어있다는 문구를 출력한다.
        if (head == nullptr)
        {
            cout << "Linked list is empty" << endl;
        }

        else
        {
            Node* deleteNode = head;
            Node* currentNode = head;

            if (head == head->next)
            {
                // 하나만 있을 때 : head는 nullptr을 가리키면 된다.
                head = nullptr;
            }

            else
            {
                // 둘 이상 있을 때
                // currentNode와 deleteNode 둘 다 head를 가리키게 한 후
                // currentNode는 3개 있을 때는 2번, 4개 있을 때는 3번 움직이게 해야 한다.
                // 그리고 마지막에는 head가 currentNode가 되게 하면 된다.
                for (int i = 0; i < size - 1; i++)
                {
                    currentNode = currentNode->next;
                }

                currentNode->next = head->next;
                head = currentNode;

            }

            delete deleteNode;

            size--;
        }
    }

    bool empty()
    {
        return (head == nullptr);
    }

    // 소멸자 만들기
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

    list.push_back(10);
    list.push_back(20);

    list.push_front(5);

    list.pop_front();
    list.pop_front();

    list.pop_back();
    list.pop_back();

    cout << list.empty() << endl;

    return 0;
}