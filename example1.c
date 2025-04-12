/* Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf */

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} NODE;

/// pentru simplitate, folosim int-uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct g {
    int v;
    int* vis;
    struct Node** alst;
} GPH;

typedef struct s {
    int t;
    int scap;
    int* arr;
} STK;

NODE* create_node(int v) {
    NODE* nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH* g, int src, int dest) {
    NODE* nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH* create_g(int v) {
    GPH* g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE*) * v);
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

STK* create_s(int scap) {
    STK* s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STK* s) {
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GPH* g, STK* s, int v_nr) {
    NODE* aux = g->alst[v_nr];
    g->vis[v_nr] = 1;
    push(v_nr, s);

    while (aux != NULL) {
        int con_ver = aux->data;

        if (g->vis[con_ver] == 0) {
            DFS(g, s, con_ver);
        }

        aux = aux->next;
    }
}

void insert_edges(GPH* g, int edg_nr, int nrv) {
    int src, dest;

    printf("Adauga %d muchii (de la 0 la %d):\n", edg_nr, nrv - 1);

    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH* g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

int canbe(GPH* g, int src, int dest, int nrv) {
    STK* s = create_s(nrv);
    DFS(g, s, src);

    for (int i = 0; i <= s->t; i++) {
        if (s->arr[i] == dest) {
            return 1;
        }
    }

    return 0;
}

int main() {
    int nrv;
    int edg_nr;
    int src, dest;

    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH* g = create_g(nrv);

    insert_edges(g, edg_nr, nrv);

    printf("Introdu perechea de noduri pentru verificare (src dest): ");
    scanf("%d%d", &src, &dest);

    if (canbe(g, src, dest, nrv)) {
        printf("Drumul direct exista intre restaurante.\n");
    } else {
        printf("Nu exista drum direct intre restaurante.\n");
    }

    return 0;
}
