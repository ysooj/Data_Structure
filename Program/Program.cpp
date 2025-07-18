#include <iostream>

using namespace std;

// ------------------
// [원형 연결 리스트]
// ------------------

template <typename T>

class List
{
private:
    struct Node
    {
        T data;
        Node * next;
    };

    int size;
    Node * head;

public:
    List()
    {
        size = 0;
        head = nullptr;
    }

    void push_back(T data)
    {
        Node * nextNode = new Node;

        if (head == nullptr)
        {
            nextNode->next = head;

            head->next = nextNode;
        }

        else
        {
            nextNode->next = 
        }
    }
};

int main()
{

    return 0;
}