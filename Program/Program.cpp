#include <iostream>

using namespace std;

#pragma region 이진 트리
// [Binary Tree] ; 이진 트리
// - 각 노드는 최대 2개의 자식을 가짐 (왼쪽, 오른쪽)
// - 루트에서 시작해 계층적 구조로 구성됨
// - 주요 유형: 포화 트리, 완전 트리, 이진 탐색 트리(BST)
// - 순회 방법: 전위(루트→왼쪽→오른쪽), 중위(왼쪽→루트→오른쪽), 후위(왼쪽→오른쪽→루트)
// - BST는 왼쪽 자식 < 루트 < 오른쪽 자식 관계 유지
// - 평균 탐색/삽입/삭제 시간 복잡도는 O(log n)
#pragma endregion

#pragma region 이진 탐색 트리
// [Binary Search Tree] ; 이진 탐색 트리 (BST)
// ▣ 구조:
//   - 각 노드는 최대 두 개의 자식 (left, right)
//   - 왼쪽 서브트리에는 더 작은 값, 오른쪽에는 더 큰 값 저장
//
// ▣ 특징:
//   - 루트에서 리프(자식 없는 노드)까지 계층적 구조
//   - 중위 순회 시 값들이 오름차순으로 출력됨
//
// ▣ 용어:
//   - 리프 노드: 자식이 없는 노드
//   - 완전 이진 트리: 마지막 레벨을 제외하고 왼쪽부터 모두 채워진 트리
//   - 편향 이진 트리: 모든 노드가 한쪽 자식만 가지는 트리
//     예) 왼쪽 자식만 계속 생기면 왼쪽 편향 트리 → 리스트처럼 됨
//
// ▣ 시간 복잡도:
//   - 평균: O(log n) (균형 잡힌 트리일 때)
//   - 최악: O(n) (편향 트리처럼 한쪽으로 치우친 경우)
#pragma endregion

template <typename T>

class Set
{
private:
    struct Node
    {
        T data;
        Node * left = nullptr;
        Node * right = nullptr;

        Node(T data)
        {
            this->data = data;
        }
    };

    Node * root;

public:
    Set()
    {
        root = nullptr;
    }

    void insert_me(T data)
    {
        // root가 비어있을 때 : data를 넣고, left와 right에는 nullptr 넣기
        if (root == nullptr)
        {
            root = new Node;

            root->data = data;
            root->left = nullptr;
            root->right = nullptr;
        }

        // root에 data가 있을 때
        else
        {
            // currentNode가 root를 가리키게 하고
            Node* currentNode = root;

            // 자식 노드가 있으면 계속 타고 들어가야 한다.
            while (true)
            {
                // currentNode의 data와 매개변수로 들어온 data를 비교해서
                // data가 작으면 left로, 크면 right로 넣는다.
                if (data < currentNode->data)
                {
                    if (currentNode->left == nullptr)
                    {
                        currentNode->left = new Node;

                        currentNode->left->data = data;
                        currentNode->left->left = nullptr;
                        currentNode->left->right = nullptr;

                        break;  // 삽입 후 함수 종료
                    }

                    else
                    {
                        currentNode = currentNode->left;
                    }
                }

                else if (data > currentNode->data)
                {
                    if (currentNode->right == nullptr)
                    {
                        currentNode->right = new Node;

                        currentNode->right->data = data;
                        currentNode->right->left = nullptr;
                        currentNode->right->right = nullptr;

                        break;  // 삽입 후 함수 종료
                    }

                    else
                    {
                        currentNode = currentNode->right;
                    }
                }

                // 중복된 data라면 data를 넣지 못하게 하기
                else
                {
                    cout << "중복된 데이터입니다." << endl;
                    break;
                }
            }
        }
    }

    void insert(T data)
    {
        Node * newNode = new Node(data);

        if (root == nullptr)
        {
            root = newNode;
        }

        else
        {
            Node * currentNode = root;

            while (currentNode != nullptr)
            {
                if (currentNode->data == data)
                {
                    delete newNode;

                    return;
                }

                else if (currentNode->data > data)
                {
                    if (currentNode->left == nullptr)
                    {
                        currentNode->left = newNode;
                        break;
                    }
                    else
                    {
                        currentNode = currentNode->left;
                    }
                }

                else
                {
                    if (currentNode->right == nullptr)
                    {
                        currentNode->right = newNode;
                        break;
                    }
                    else
                    {
                        currentNode = currentNode->right;
                    }
                }
            }
        }
    }

    // 후위 순회(Left → Right → Root) ; 후위 순회를 사용해야 자식 노드부터 안전하게 지운 뒤 부모 노드를 삭제할 수 있다.
    void release(Node * root)
    {
        // 1. 현재 노드가 nullptr이 아니면 재귀 함수 호출
        if (root != nullptr)
        {
            // 2. 왼쪽 자식 노드부터 재귀적으로 삭제
            //    왼쪽 자식이 nullptr이 될 때까지 쭉 들어감
            release(root->left);

            // 3. 왼쪽 서브트리가 모두 삭제되면 오른쪽 자식 노드도 재귀적으로 삭제
            //    오른쪽 자식도 nullptr이 될 때까지 쭉 들어감
            release(root->right);

            // 4. 왼쪽, 오른쪽 자식 노드가 모두 삭제된 후
            //    현재 노드를 안전하게 삭제
            delete root;
        }
    }

    void erase(T data)
    {
        Node * currentNode = root;
        Node * parentNode = nullptr;

        while (currentNode != nullptr && currentNode->data != data)
        {
            if (data < currentNode->data)
            {
                parentNode = currentNode;
                currentNode = currentNode->left;
            }

            else
            {
                parentNode = currentNode;
                currentNode = currentNode->right;
            }
        }

        // erase 함수의 역할
        // 1. 자식 노드가 하나도 없을 때
        if (currentNode->left == nullptr && currentNode->right == nullptr)
        {
            if (currentNode == root && parentNode == root)
            {
                root = nullptr;

                delete currentNode;
            }

            else
            {
                delete currentNode;

                currentNode = parentNode;
            }
        }

        cout << "Found the data!" << endl;


        
         
        
        // 2. 자식 노드가 하나만 있을 때
        
        
        // 3. 자식 노드가 두 개 있을 때
    }

    void erase_gpt(T data)
    {
        Node* currentNode = root;
        Node* parentNode = nullptr;

        // 삭제할 노드 탐색
        while (currentNode != nullptr && currentNode->data != data)
        {
            parentNode = currentNode;

            if (data < currentNode->data)
                currentNode = currentNode->left;
            else
                currentNode = currentNode->right;
        }

        // 찾지 못한 경우
        if (currentNode == nullptr)
        {
            cout << "해당 데이터를 찾을 수 없습니다." << endl;
            return;
        }

        // 찾은 경우
        cout << "찾았다! 삭제할 데이터는: " << currentNode->data << endl;

        // [1] 자식 노드가 하나도 없는 경우 (리프 노드)
        if (currentNode->left == nullptr && currentNode->right == nullptr)
        {
            // (1) 삭제 대상이 루트 노드인 경우
            if (currentNode == root)
            {
                delete root;
                root = nullptr;
            }
            // (2) 부모 노드에서 자식 연결 끊기
            else if (parentNode->left == currentNode)
            {
                delete currentNode;
                parentNode->left = nullptr;
            }
            else if (parentNode->right == currentNode)
            {
                delete currentNode;
                parentNode->right = nullptr;
            }

            return; // 여기서 끝내야 아래 코드 실행 안 함
        }

        // [2] 자식 노드가 하나만 있을 때 (작성 예정)

        // [3] 자식 노드가 두 개 있을 때 (작성 예정)
    }

    ~Set()
    {
        release(root);
    }
};

int main()
{
    Set <int> set;

    set.insert(10);
    set.insert(6);
    set.insert(20);
    set.insert(3);
    set.insert(15);

    return 0;
}