#include <iostream>

using namespace std;

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
            Node * deleteNode = head;

            // 원래의 head는 pop_front를 통해 지울 것이기 때문에 deleteNode의 next가 가리키는 것이 이제 head가 돼야 한다.
            head = deleteNode->next;

            delete deleteNode;

            size--;
        }
    }
    //push back, pop back, empty, remove 등 내일 만들 예정
};

int main()
{
    List<int> list;

    list.push_front(10);
    list.push_front(5);
    list.push_front(1);

    list.pop_front();
    list.pop_front();
    list.pop_front();
    list.pop_front();

    return 0;
}
