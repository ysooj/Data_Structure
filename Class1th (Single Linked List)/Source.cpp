#include <iostream>

using namespace std;

// 지금 배우고 있는 건 {[자료 구조론]}

// -----------------
// [단일 방향 리스트]
// -----------------

//  데이터 만들기
//  생성자 초기화
//  node는 구조체로 만들어준다

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

    void push_front(T data)
    {
        Node * newNode = new Node;

        newNode->data = data;
        //if head가 0일 때(보다 작을 때)
        // newNode가 처음 생성됐을 때는 nullptr을 가리키고 있어야 한다.
        if (head == nullptr)
        {
            head = newNode;

            newNode->next = nullptr;
        }

        //하나라도 존재한다면 앞에 newNode 놓기
        else
        {
            newNode->next = head;
            head = newNode;
        }

        size++;
    }

    void pop_front()
    {
        // 데이터가 아무것도 없을 때 지우려고 하면 아래의 문구를 출력한다.
        if (head == nullptr)
        {
            cout << "Linked list is empty" << endl;
        }

        else
        {
            // 삭제하기 위해 그냥 참조만 할 포인터기 때문에 할당할 필요는 없다.
            Node* deleteNode = head;

            // 원래의 head는 pop_front를 통해 지울 것이기 때문에 deleteNode의 next가 가리키는 것이 이제 head가 돼야 한다.
            head = deleteNode->next;

            delete deleteNode;

            size--;
        }
    }

    void push_back(T data)
    {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;
        }

        else
        {
            Node* currentNode = head;

            while (currentNode->next != nullptr)
            {
                currentNode = currentNode->next;
            }

            currentNode->next = newNode;
        }

        size++;
    }

    void pop_back()
    {
        if (head == nullptr)
        {
            cout << "Linked list is empty" << endl;
        }

        else
        {
            Node* deleteNode = head;
            Node* previousNode = nullptr;

            if (size == 1)
            {
                head = deleteNode->next;

                delete deleteNode;
            }

            else
            {
                while (deleteNode->next != nullptr)
                {
                    previousNode = deleteNode;
                    deleteNode = deleteNode->next;
                }

                previousNode->next = deleteNode->next;

                delete deleteNode;
            }

            size--;
        }

    }

    void remove(T data)
    {
        // head가 nullptr일 때는 그냥 return하면 된다.
        // 즉, 리스트가 비어 있으면 아무것도 하지 않는다.
        if (head == nullptr)
        {
            return;
        }

        else
        {
            Node* deleteNode = head;
            Node* previousNode = head;

            while (deleteNode != nullptr)
            {
                // 지우고 싶은 data가 맞을 때
                if (deleteNode->data == data)
                {
                    // 삭제할 노드가 head인 경우
                    if (deleteNode == head)
                    {
                        pop_front();

                        deleteNode = head;
                        previousNode = head;
                    }


                    // data가 처음에 있는 게 아니라, 중간에 있는 경우
                    else
                    {
                        previousNode->next = deleteNode->next;

                        delete deleteNode;

                        size--;

                        deleteNode = head;
                        previousNode = deleteNode;
                    }
                }

                // 지우고 싶은 data가 아닐 때는 다음 노드로 넘어간다.
                // 즉, 현재 노드가 삭제 대상이 아니므로 다음 노드로 이동
                else
                {
                    previousNode = deleteNode;
                    deleteNode = deleteNode->next;
                }
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
    List<int> list;

    list.push_front(10);
    list.push_front(5);
    list.push_front(1);

    list.push_back(20);
    list.push_back(30);

    list.pop_front();
    list.pop_back();

    list.remove(20);

    cout << list.empty() << endl;

    return 0;
}