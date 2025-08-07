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

// Set 클래스: 이진 탐색 트리 형태의 집합 구현
template <typename T>

class Set
{
private:
    // 노드 구조체: 값(data), 왼쪽/오른쪽 자식 포인터 포함
    struct Node
    {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(T data)
        {
            this->data = data;
        }
    };

    Node* root;    // 트리의 루트 노드

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
            root = new Node(data);
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

    // 노드 삽입 (중복 방지)
    void insert(T data)
    {
        Node* newNode = new Node(data);

        if (root == nullptr)
        {
            root = newNode;
        }

        else
        {
            Node* currentNode = root;

            while (currentNode != nullptr)
            {
                if (currentNode->data == data)
                {
                    delete newNode; // 중복이면 삽입 안 함

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

    // 재귀적으로 트리 전체 해제
    // 후위 순회(Left → Right → Root) ; 후위 순회를 사용해야 자식 노드부터 안전하게 지운 뒤 부모 노드를 삭제할 수 있다.
    void release(Node* root)
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

    // 노드 삭제
    void erase(T data)
    {
        Node* currentNode = root;      // 삭제 대상 노드를 찾기 위한 포인터
        Node* parentNode = nullptr;    // 삭제 대상의 부모 노드를 추적

        // [1단계] 삭제할 노드 탐색
        // - 트리를 루트부터 내려가면서 삭제할 값을 왼쪽 또는 오른쪽으로 내려가면서 탐색
        while (currentNode != nullptr && currentNode->data != data)
        {
            parentNode = currentNode;

            if (data < currentNode->data)
            {
                currentNode = currentNode->left;    // 삭제할 값이 더 작으면 왼쪽으로
            }

            else
            {
                currentNode = currentNode->right;   // 크면 오른쪽으로
            }
        }

        // [2] 삭제할 데이터를 찾지 못한 경우
        //     - currentNode가 nullptr이면 트리에 해당 data가 없음
        // [1단계 종료] 해당 값이 트리에 없는 경우
        if (currentNode == nullptr)
        {
            cout << "the data does not exist" << endl;

            // 지울 data를 찾지 못하면 바로 함수 종료.
            return;
        }

        // [2단계] 자식 노드가 없을 경우 (리프 노드) → 바로 삭제
        // 그냥 삭제하고 부모에서 연결 제거
        else if (currentNode->left == nullptr && currentNode->right == nullptr)
        {
            // 부모 노드가 있는 경우 (루트가 아님)
            // (1) 삭제할 노드가 루트가 아닌 경우
            if (parentNode != nullptr)
            {
                // 삭제할 노드가 부모의 왼쪽 자식이면 왼쪽 연결 끊기
                if (parentNode->left == currentNode)
                {
                    parentNode->left = nullptr;
                }

                // 삭제할 노드가 부모의 오른쪽 자식이면 오른쪽 연결 끊기
                else
                {
                    parentNode->right = nullptr;
                }
            }

            // (2) 삭제할 노드가 루트일 경우
            else
            {
                root = nullptr; // 루트 자체를 없앰
            }

            delete currentNode; // 실제 메모리에서 제거

            cout << "Deleted the data!" << endl;
        }


        // [3단계] 자식이 **하나만 있을 경우**
        // - 하나뿐인 자식을 부모가 직접 가리키게 한다.
        //     - 왼쪽 또는 오른쪽 자식만 있는 경우,
        //       부모 노드가 삭제할 노드 대신 자식 노드를 가리키게 함
        else if (currentNode->left == nullptr || currentNode->right == nullptr)
        {
            // (1) 삭제할 노드가 루트일 경우
            if (currentNode == root)
            {
                // 왼쪽 자식만 있는 경우 → 루트를 왼쪽 자식으로 교체
                if (currentNode->left != nullptr)
                {
                    root = currentNode->left;
                }
                // 오른쪽 자식만 있는 경우 → 루트를 오른쪽 자식으로 교체
                else
                {
                    root = currentNode->right;
                }
            }

            // (2) 루트가 아닌 경우 → 부모가 그 자식을 대신 가리키게 연결 수정
            else
            {
                Node* childNode = nullptr; // 자식 노드를 저장할 변수

                // 왼쪽 자식이 있는 경우 → 자식 노드를 왼쪽으로 지정
                if (currentNode->left != nullptr)
                {
                    childNode = currentNode->left;
                }
                // 오른쪽 자식이 있는 경우 → 자식 노드를 오른쪽으로 지정
                else
                {
                    childNode = currentNode->right;
                }

                // (2-1) 삭제할 노드가 부모의 왼쪽 자식인 경우
                if (parentNode->left == currentNode)
                {
                    parentNode->left = childNode;
                }
                // (2-2) 삭제할 노드가 부모의 오른쪽 자식인 경우
                else
                {
                    parentNode->right = childNode;
                }
            }
        }

        // [4단계] 자식이 **두 개 있는 경우**
        // - 오른쪽 서브트리에서 가장 작은 값을 가져와서 대체
        else if (currentNode->left != nullptr && currentNode->right != nullptr)
        {
            // (1) 오른쪽 서브트리에서 가장 작은 값을 가진 노드를 찾기
            //     → 이 노드는 currentNode를 대체할 값이 됨 (BST 성질 유지)
            Node* childNode = currentNode->right;  // 오른쪽 서브트리의 루트부터 시작
            Node* traceNode = currentNode;         // 후계자 노드의 부모 노드를 추적

            // 왼쪽 자식이 없을 때까지 반복 → 가장 작은 값
            while (childNode->left != nullptr)
            {
                traceNode = childNode;          // 부모를 갱신
                childNode = childNode->left;    // 왼쪽으로 내려감
            }


            // (2) 삭제할 노드의 데이터를 후계자의 데이터로 교체
            //     → 값만 바꾸고, 실제 삭제는 childNode에서 수행
            currentNode->data = childNode->data;


            // (3) 후계자 노드(childNode)의 부모와 연결 끊기
            //     - 후계자가 traceNode의 왼쪽 자식인 경우
            //     - 후계자 노드의 오른쪽 자식이 있을 수도 있으므로 연결 유지
            if (traceNode == currentNode)               // 만약 후계자(childNode)가 currentNode의 바로 오른쪽 자식이라면 (즉, traceNode가 currentNode 자체일 경우)
            {
                traceNode->right = childNode->right;    // currentNode의 오른쪽 포인터를 후계자의 오른쪽 자식으로 연결
            }
            else                                        // 그렇지 않다면 (후계자가 오른쪽 서브트리 내 더 깊은 위치에 있을 경우)
            {
                traceNode->left = childNode->right;     // 후계자의 부모(traceNode)의 왼쪽 포인터를 후계자의 오른쪽 자식으로 연결
            }

            // (4) 후계자 노드 삭제
            delete childNode;
        }

        cout << "Deleted the data!" << endl;
        cout << endl;
    }

    // 오름차순 순서대로 출력
    // 중위 순회
    void inorder(Node* root, ostream& ostream) const
    {
        if (root != nullptr)
        {
            inorder(root->left, ostream);

            ostream << root->data << " ";

            inorder(root->right, ostream);
        }
    }

    // 콜백 함수를 만들어서 출력 함수인 inorder 함수 호출.
    friend ostream& operator<< (ostream& ostream, const Set<T>& set)
    {
        set.inorder(set.root, ostream);

        return ostream;
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
    set.insert(5);
    set.insert(20);
    set.insert(15);
    set.insert(30);
    set.insert(24);
    set.insert(27);

    // [2] 리프 노드 삭제 테스트
    set.erase(5);    // 리프 노드

    // [3] 자식 1개 노드 삭제 테스트
    set.erase(30);   // 자식 하나 (왼쪽)만 있음

    // [4] 자식 2개 노드 삭제 테스트
    set.erase(20);   // 자식 2개 (15, 24)

    cout << set << endl;

    return 0;
}