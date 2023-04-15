#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "grid.h"
#include "pq.h"

/** Initializes a new PriorityQueue instance with a max of CAPACITY elements. */
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue* pq = malloc(sizeof(PriorityQueue));
    pq->heap = malloc(sizeof(PQNode) * (capacity + 1));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

/** Frees memory associated with the PQ PriorityQueue. */
void pq_destroy(PriorityQueue* pq) {
    free(pq->heap);
    free(pq);
}

/** Pushes an element onto the PriorityQueue with a DiSTANCE and for a point at I, J. 
 * Distance is the minimized element for the PQ, and as such points are assigned based on
 * the minimum distance from other elements.
*/
void pq_push(PriorityQueue* pq, int distance, int i, int j) {
    if (pq->size >= pq->capacity) {
        printf("Priority queue overflow.\n");
        return;
    }
    pq->size += 1;
    int k = pq->size;
    while (k > 1 && pq->heap[k/2].distance > distance) {
        pq->heap[k] = pq->heap[k/2];
        k /= 2;
    }
    pq->heap[k].distance = distance;
    pq->heap[k].i = i;
    pq->heap[k].j = j;
}

/** Pops the PQNode with the minimum distance. */
PQNode pq_pop(PriorityQueue *pq) {
    if (pq->size <= 0) {
        printf("Priority queue underflow!\n");
        return (PQNode) {0, 0, 0};
    }
    PQNode min_node = pq->heap[1];
    pq->size -= 1;
    int k = 1;
    while (k * 2 <= pq->size) {
        int j = k * 2;
        if (j < pq->size && pq->heap[j+1].distance < pq->heap[j].distance) {
            j += 1;
        }
        if (pq->heap[j].distance < pq->heap[k].distance) {
            PQNode temp_node = pq->heap[k];
            pq->heap[k] = pq->heap[j];
            pq->heap[j] = temp_node;
            k = j;
        } else {
            break;
        }
    }
    return min_node;
}