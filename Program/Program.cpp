#include <iostream>

using namespace std;

// ------------------
// [원형 연결 리스트]
// ------------------

// head는 항상 "마지막 노드"
// head->next는 항상 "처음 노드"

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
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;

            newNode->next = newNode;
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
};

int main()
{

    return 0;
}