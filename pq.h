#ifndef PQ_H
#define PQ_H

#include <stdint.h>

typedef struct {
    int distance;
    int i;
    int j;
} PQNode;

typedef struct {
    PQNode *heap;
    uint32_t size;
    uint32_t capacity;
} PriorityQueue;

PriorityQueue *pq_create(uint32_t capacity);

void pq_destroy(PriorityQueue* pq);

void pq_push(PriorityQueue* pq, int distance, int i, int j);

PQNode pq_pop(PriorityQueue *pq);

#endif