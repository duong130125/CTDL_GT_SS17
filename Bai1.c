#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int vertices;
    int edges;
    int adjacencyList[MAX][MAX];
    int degree[MAX];
} Graph;

typedef struct
{
    int items[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q)
{
    return q->front == -1;
}

void enqueue(Queue *q, int value)
{
    if (q->rear == MAX - 1)
    {
        printf("Hàng đợi đầy!\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Hàng đợi trống!\n");
        return -1;
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
    {
        q->front = q->rear = -1;
    }
    return item;
}

void initGraph(Graph *g, int vertices)
{
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++)
    {
        g->degree[i] = 0;
    }
}

void addEdge(Graph *g, int src, int dest)
{
    g->adjacencyList[src][g->degree[src]++] = dest;
    g->adjacencyList[dest][g->degree[dest]++] = src;
}

void printGraph(Graph *g)
{
    for (int i = 0; i < g->vertices; i++)
    {
        printf("Đỉnh %d: ", i);
        for (int j = 0; j < g->degree[i]; j++)
        {
            printf("%d ", g->adjacencyList[i][j]);
        }
        printf("\n");
    }
}

void DFS(Graph *g, int v, int visited[])
{
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < g->degree[v]; i++)
    {
        int adj = g->adjacencyList[v][i];
        if (!visited[adj])
        {
            DFS(g, adj, visited);
        }
    }
}

void BFS(Graph *g, int start, int visited[])
{
    Queue q;
    initQueue(&q);
    visited[start] = 1;
    enqueue(&q, start);

    while (!isEmpty(&q))
    {
        int v = dequeue(&q);
        printf("%d ", v);

        for (int i = 0; i < g->degree[v]; i++)
        {
            int adj = g->adjacencyList[v][i];
            if (!visited[adj])
            {
                visited[adj] = 1;
                enqueue(&q, adj);
            }
        }
    }
}

int main()
{
    Graph g;
    int vertices, edges, startVertex;
    int visited[MAX] = {0};

    printf("Nhập số đỉnh và số cạnh: ");
    scanf("%d %d", &vertices, &edges);

    initGraph(&g, vertices);

    printf("Nhập các cạnh (đỉnh đầu, đỉnh cuối):\n");
    for (int i = 0; i < edges; i++)
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(&g, src, dest);
    }

    printf("Danh sách kề của đồ thị:\n");
    printGraph(&g);

    printf("\nNhập đỉnh bắt đầu duyệt: ");
    scanf("%d", &startVertex);

    printf("Duyệt đồ thị bằng DFS: ");
    for (int i = 0; i < vertices; i++)
        visited[i] = 0;
    DFS(&g, startVertex, visited);
    printf("\n");

    printf("Duyệt đồ thị bằng BFS: ");
    for (int i = 0; i < vertices; i++)
        visited[i] = 0;
    BFS(&g, startVertex, visited);
    printf("\n");

    return 0;
}
