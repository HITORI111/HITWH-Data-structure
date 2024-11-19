#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000
#define MAX_M 330000
#define QUEUE_SIZE (MAX_N + 1)

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} Graph;

Graph graph[MAX_N + 1];
int visited[MAX_N + 1];
int distance[MAX_N + 1];

void addEdge(int u, int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = v;
    node->next = graph[u].head;
    graph[u].head = node;

    node = (Node*)malloc(sizeof(Node));
    node->vertex = u;
    node->next = graph[v].head;
    graph[v].head = node;
}

int bfs(int start, int n) {
    int queue[QUEUE_SIZE], front = 0, rear = 0;
    int count = 0;

    memset(visited, 0, sizeof(visited));
    memset(distance, -1, sizeof(distance));

    queue[rear++] = start;
    visited[start] = 1;
    distance[start] = 0;
    count++;

    while (front < rear) {
        int current = queue[front++];
        
        for (Node* neighbor = graph[current].head; neighbor != NULL; neighbor = neighbor->next) {
            if (!visited[neighbor->vertex]) {
                visited[neighbor->vertex] = 1;
                distance[neighbor->vertex] = distance[current] + 1;

                if (distance[neighbor->vertex] <= 6) {
                    queue[rear++] = neighbor->vertex;
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        graph[i].head = NULL;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    for (int i = 1; i <= N; i++) {
        int count = bfs(i, N);
        double percentage = (double)count / N * 100.0;
        printf("%d: %.2f%%\n", i, percentage);
    }

    return 0;
}
