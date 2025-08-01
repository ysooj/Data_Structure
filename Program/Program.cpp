#include <iostream>

using namespace std;

// --------------------------------------------------------
// [Graph] ; 그래프 중 인접 리스트
// ▣ 인접 리스트 (Adjacency List):
//   - 각 정점마다 연결된 정점들의 목록을 리스트(또는 벡터 등)로 저장하는 방식
//   - 연결된 정점만 저장하므로, 간선이 적은 그래프(희소 그래프)에서 메모리 효율이 좋음
//   - 정점이 많고 간선이 적은 경우 인접 행렬보다 훨씬 공간 절약 가능
//   - 특정 정점에서 연결된 모든 정점을 탐색하는 데 걸리는 시간 복잡도는 O(k)
//     → 여기서 k는 해당 정점에 연결된 정점(간선)의 수
//   - 구현 시: 배열 + 연결 리스트, 또는 벡터<vector<int>> 등으로 구성
// --------------------------------------------------------

template <typename T>

class Graph
{
private:
    struct Node
    {
        T data;
        Node * next;

        //C언어에서는 구조체에서도 생성자를 초기화할 수 있다.
        Node(T data, Node * link = nullptr)
        {
            this->data = data;
            next = link;
        }
    };

    int size;       // 정점의 개수
    int capacity;   // 최대 용량
    int count;      // 인접 리스트의 크기

    T * vertex;     // 정점의 집합
    Node ** list;    // 각 정점의 인접 노드 리스트.(인접 리스트)

public:
    Graph()
    {
        size = 0;
        capacity = 0;
        count = 0;

        vertex = nullptr;
        list = nullptr;
    }

    void resize(int newSize)
    {
        // 1. capacity에  새로운 size 값을 저장합니다.
        capacity = newSize;

        // 2. 새로운 포인터 변수를 생성해서 새롭게 만들어진 메모리 공간을 가리키도록 합니다.
        T* container = new T[capacity];

        // 3. 새로운 메모리 공간의 값을 초기화합니다.
        for (int i = 0; i < capacity; i++)
        {
            container[i] = NULL;
        }

        // 4. 기존 배열에 있는 값을 복사해서 새로운 배열에 넣어줍니다.
        for (int i = 0; i < size; i++)
        {
            container[i] = vertex[i];
        }

        //5. 기존 배열의 메모리를 해제합니다. (if문을 쓰지 않고 그냥 'delete [] container;' 이라고 해도 된다고 한다.)
        if (vertex != nullptr)
        {
            delete[] vertex;
        }

        // 6. 기존에 배열을 가리키던 포인터 변수의 값을 새로운 배열의 시작 주소로 가리킵니다.
        vertex = container;
    }

    void push(T data)
    {
        // 초기 용량이 없으면 1로 설정
        if (capacity <= 0)
        {
            resize(1);
        }

        // 용량 초과 시 두 배로 확장
        else if (capacity <= size)
        {
            resize(capacity * 2);
        }

        vertex[size++] = data;  // 정점 추가 후 size 증가
    }

    void edge(int i, int j)
    {
        // 1. 그래프에 정점이 하나도 없으면 간선을 추가할 수 없음
        if (size <= 0)
        {
            cout << "Adjacency List is Empty" << endl;
        }

        // 2. 입력된 정점 번호 i 또는 j가 그래프에 존재하는 범위를 벗어나면 오류 출력
        else if (i >= size || j >= size)
        {
            cout << "Index Out of Range" << endl;
        }

        else
        {
            // 3. 인접 리스트 배열(list)이 아직 초기화되지 않은 경우, 초기화 진행
            if (list == nullptr)
            {
                // size만큼의 Node* 배열을 생성 (각 정점마다 연결 리스트의 head를 가리킴)
                list = new Node * [size];

                // 4. 모든 리스트 헤드를 nullptr로 초기화 (아직 아무 연결이 없음)
                for (int i = 0; i < size; i++)
                {
                    list[i] = nullptr;
                }

                count = size;
            }

            // 5. 정점 i의 인접 리스트 앞에 정점 j를 추가 (헤드 삽입)
            //    vertex[j]: 정점 j의 데이터(예: 'B', 'C' 등)
            //    list[i]: 현재 i의 인접 리스트 헤드
            list[i] = new Node(vertex[j], list[i]);

            // 6. 무방향 그래프이므로 반대 방향 간선도 추가
            list[j] = new Node(vertex[i], list[j]);
        }
    }

    void resize()
    {
        int ** newList = new int * [size];

        for (int i = 0; i < size; i++)
        {
            newList[i] = nullptr;
        }

        for (int i = 0; i < count; i++)
        {
            newList[i] = list[i];
        }

        list = newList;
    }

    ~Graph()
    {
        for (int i = 0; i < size; i++)
        {
            Node * deleteNode = list[i];
            Node * nextNode = deleteNode->next;

            if (deleteNode == nullptr)
            {
                continue;
            }
            else
            {
                while (nextNode != nullptr)
                {
                    nextNode = deleteNode->next;

                    delete deleteNode;

                    deleteNode = nextNode;
                }
            }
        }

        delete [] list;

        delete [] vertex;
    }
};

int main()
{
    Graph <char> graph;

    graph.push('A');
    graph.push('B');
    graph.push('C');
    graph.push('D');

    graph.edge(0, 1);
    graph.edge(0, 2);
    graph.edge(0, 3);
    graph.edge(2, 3);

    graph.push('E');
    graph.edge(2, 4);

    return 0;
}

// [다음 주] => 이진 트리