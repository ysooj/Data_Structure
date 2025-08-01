#include <iostream>

using namespace std;

// --------------------------------------------------------
// [Graph] ; 그래프 중 인접 행렬
// 정점(Vertex)과 간선(Edge)으로 구성된 자료구조
//
// ▣ 그래프의 종류:
//   - 방향 그래프 (Directed Graph): 간선에 방향이 있으며, 진입 차수 / 진출 차수 개념이 존재
//   - 무방향 그래프 (Undirected Graph): 간선에 방향이 없으며, 연결이 양방향
//   - 가중치 그래프 (Weighted Graph): 간선에 비용 또는 가중치가 존재
//
// ▣ 그래프의 표현 방법:
//   - 인접 행렬 (Adjacency Matrix): 정점 간 연결 여부를 2차원 배열로 표현
//   - 인접 리스트 (Adjacency List): 각 정점에 연결된 정점들을 리스트로 표현 (공간 효율적)
//
// ▣ 그래프 기반 알고리즘:
//   - DFS (깊이 우선 탐색), BFS (너비 우선 탐색)
//   - 다익스트라 (최단 경로), 위상 정렬 (Topological Sort)
//   - 벨만-포드, 크루스칼, 프림, 플로이드 와샬 등
// --------------------------------------------------------

template <typename T>

class Graph
{
private:

    int size;     // 실제로 현재 존재하는 정점 개수.                 // 지금까지 push()로 추가된 정점 수
    int count;    // 인접 행렬(matrix)의 크기 (할당된 행/열 수)      // 인접 행렬(matrix)에 실제로 할당된 크기
    int capacity; // 최대 용량

    T* vertex;     // 정점의 집합
    int** matrix;  // 인접 행렬

public:
    Graph()
    {
        size = 0;
        count = 0;
        capacity = 0;

        vertex = nullptr;
        matrix = nullptr;
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

    // 정점을 만드는 함수
    void push(T data)
    {
        if (capacity <= 0)
        {
            resize(1);  // 최초 할당: 배열이 비어 있을 경우, 용량을 1로 설정
        }

        else if (size >= capacity)
        {
            resize(capacity * 2);   // 용량 부족 시 2배 확장 (동적 배열의 일반적 전략)
        }

        vertex[size++] = data;
    }

    // 내가 만든 edge 함수
    // edge_me 함수 문제점
    // 매번 호출할 때마다 matrix = new int* [capacity];를 새로 할당해서 메모리 누수가 생깁니다.
    // if (vertex == nullptr) 대신 if (size <= 0)으로 확인하는 게 더 정확해요.
    // i > size 대신 i >= size로 수정해야 범위 검사 올바릅니다.
    void edge_me(int i, int j)
    {
        // 1. vertex가 없을 때 edge를 연결하려고 하면, 인접 행렬이 없다고 알려주어야 합니다.
        if (vertex == nullptr)
        {
            cout << "Matrix is empty" << endl;
        }

        // 2. vertex의 크기를 벗어나서 edge를 연결하려고 한다면, 배열의 범위를 벗어났다고 알려주어야 합니다.
        else if (i > size || j > size)
        {
            cout << "Matrix Out of Range" << endl;
        }

        else
        {
            matrix = new int* [capacity];
            // 3. 행을 먼저 size만큼 할당하고, 열을 할당하고, data값을 0으로 다 초기화.
            //    인접 행렬의 크기를 size값으로 갱신시켜주어야 한다. count++.
            for (int i = 0; i < size; i++)
            {
                matrix[i] = new int[capacity];

                for (int j = 0; j < size; j++)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        count = size;

        matrix[i][j] = 1;
        matrix[j][i] = 1;
    }

    // 선생님의 edge 함수
    void edge(int i, int j)
    {
        // 1. 정점이 하나도 없는 상태이면 간선을 추가할 수 없으므로 메시지 출력 후 함수 종료
        if (size <= 0)
        {
            cout << "adjacency matrix is empty" << endl;
        }

        // 2. 간선을 추가하려는 정점 인덱스가 범위를 벗어나면 오류 메시지 출력 후 종료
        if (i >= size || j >= size)
        {
            cout << "index out of range" << endl;
        }

        // 3. 인접 행렬이 아직 할당되지 않았다면(최초 호출 시)
        if (matrix == nullptr)
        {
            count = size;

            // 3-1. 인접 행렬을 동적 2차원 배열로 할당 (정점 개수 size x size)
            matrix = new int* [size];

            // 3-2. 각 행마다 열 공간을 할당하고, 모든 값을 0으로 초기화
            for (int i = 0; i < size; i++)
            {
                matrix[i] = new int[size];

                for (int j = 0; j < size; j++)
                {
                    matrix[i][j] = 0;   // 초기에는 모든 간선이 없으므로 0으로 세팅
                }
            }
        }

        // 4. 만약 count가 size보다 작다면, 즉 인접 행렬이 정점 수보다 작다면 resize 호출
        else if (count < size)
        {
            resize();
        }

        // 5. 간선을 추가하는 부분
        // 무방향 그래프 기준: 양쪽 정점의 연결 표시
        matrix[i][j] = 1;   // i번째 정점에서 j번째 정점으로의 간선 추가
        matrix[j][i] = 1;   // j번째 정점에서 i번째 정점으로의 간선 추가 (무방향이므로 반대 방향도 1)
    }

    // edge를 이은 후 또 push하고 edge를 새로 연결하면 터지는데, 이는 지금은 최대 용량을 넘어갔기 때문이다.
    // 즉, size가 count보다 크다. 그래서 resize 함수를 만들어서 해결하려 한다.
    // 같은 이름의 함수가 있지만, 매개 변수의 수가 다르면 '함수의 오버로딩'으로 인해 터지지 않고 사용 가능하다.
    // 내가 만든 함수
    void resize_me()
    {
        int** newMatrix = new int* [size];

        for (int i = 0; i < size; i++)
        {
            newMatrix[i] = new int[size];

            for (int j = 0; j < size; j++)
            {
                newMatrix[i][j] = 0;

                if (i < count && j < count)
                {
                    newMatrix[i][j] = matrix[i][j];
                }
            }
        }

        for (int i = 0; i < count; i++)
        {
            delete[] matrix[i];
        }

        delete[] matrix;

        matrix = newMatrix;
        count = size;
    }

    void resize()
    {
        int** newMatrix = new int* [size];

        for (int i = 0; i < size; i++)
        {
            newMatrix[i] = new int[size] {0};   // 0으로 초기화
            // 크기 size인 배열을 선언하면서 중괄호 초기화(list-initialization)를 사용해 모든 요소를 0으로 설정한다.
            // 중괄호 초기화란, {} 안에 값을 넣어 변수를 초기화하는 방법으로, C++11부터 지원된다.
            // {0}일 경우 배열 전체가 0으로 초기화되지만
            // {1}이나 {48}처럼 0이 아닌 값을 넣으면, 첫 번째 원소만 그 값으로 초기화되고 나머지는 0이 된다.
            // 따라서 배열 전체를 같은 값으로 초기화하려면 별도의 for문이 필요하지만,
            // 0으로 초기화할 때는 중괄호 초기화만으로 충분해 for문 없이도 가능한 것이다.
        }

        // 기존 matrix 값 복사 (기존 count x count 범위)
        for (int i = 0; i < count; i++)
        {

            for (int j = 0; j < count; j++)
            {
                newMatrix[i][j] = matrix[i][j];
            }
        }

        // 기존 메모리 해제
        if (matrix != nullptr)
        {
            for (int i = 0; i < count; i++)
            {
                delete[] matrix[i];
            }

            delete[] matrix;
        }

        matrix = newMatrix;
        count = size;   // 인접 행렬 크기 업데이트
    }

    friend ostream& operator<< (ostream& ostream, const Graph<T>& graph)
    {
        // 열(j) 이름 출력
        ostream << "   ";
        for (int j = 0; j < graph.size; j++)
        {
            ostream << graph.vertex[j] << "  ";
        }
        ostream << endl;

        // 행(i) 출력
        for (int i = 0; i < graph.count; i++)
        {
            ostream << graph.vertex[i] << "  "; // 행 이름 출력

            for (int j = 0; j < graph.count; j++)
            {
                ostream << graph.matrix[i][j] << "  ";
            }

            ostream << endl;
        }
        return ostream;

        // 그러면 아래처럼 출력되게 된다.
        //      A  B  C  D    ← j가 바뀌며 열의 이름을 출력
        //    A 0  1  0  0
        //    B 1  0  0  0
        //    C 0  0  0  0
        //    D 0  0  0  0
        //    ↑
        //    i가 바뀌며 행의 이름 출력

    }

    ~Graph()
    {
        if (matrix != nullptr)
        {
            for (int i = 0; i < count; i++)
            {
                delete[] matrix[i];
            }

            delete[] matrix;
        }

        delete[] vertex;
    }
};

int main()
{
    Graph <char> graph;

    graph.push('A');
    graph.push('B');
    graph.push('C');

    graph.edge(0, 1);

    graph.push('D');

    graph.resize();
    graph.edge(0, 3);

    cout << graph;

    return 0;
}