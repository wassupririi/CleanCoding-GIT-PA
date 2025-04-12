#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} NODE;

typedef struct {
    int vertices;
    int* visited;
    NODE** adjacency_lists;
} GPH;

/// utils
NODE* create_node(int v) {
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH* create_graph(int vertices) {
    GPH* graph = (GPH*)malloc(sizeof(GPH));

    graph->vertices = vertices;
    graph->adjacency_lists = (NODE**)malloc(vertices * sizeof(NODE*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void add_edge(GPH* graph, int src, int dest) {
    NODE* new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insedg(int nr_of_vertices, int nr_of_edges, GPH* graph) {
    int src, dest;
    printf("Adauga %d muchii (nodurile de la 0 la %d):\n", nr_of_edges, nr_of_vertices - 1);
    for (int i = 0; i < nr_of_edges; i++) {
        printf("Muchia %d: ", i + 1);
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

/// bfs utils
int is_empty(NODE* queue) {
    return queue == NULL;
}

void enqueue(NODE** queue, int data) {
    NODE* new_node = create_node(data);
    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        NODE* temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE** queue) {
    int data = (*queue)->data;
    NODE* temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void wipe_visited_list(GPH* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

/// parcurgeri
void DFS(GPH* graph, int vertex) {
    NODE* temp = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH* graph, int start) {
    NODE* queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE* temp = graph->adjacency_lists[current];
        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    GPH* graph = create_graph(nr_of_vertices);
    insedg(nr_of_vertices, nr_of_edges, graph);

    printf("De unde plecam in DFS? ");
    scanf("%d", &starting_vertex);

    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    printf("\n");

    wipe_visited_list(graph);

    printf("De unde plecam in BFS? ");
    scanf("%d", &starting_vertex);

    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);
    printf("\n");

    return 0;
}
