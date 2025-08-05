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
        Node * left;
        Node * right;
    };

    Node * root;

public:
    Set()
    {
        root = nullptr;
    }

    void insert(T data)
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
            Node * currentNode = root;

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
};

int main()
{
    Set <int> set;

    set.insert(10);

    return 0;
}