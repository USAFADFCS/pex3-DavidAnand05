/** pagequeue.c
 * ===========================================================
 * Name: ______________David ANand_________, __ _4 23__ 2026
 * Section: CS483 / ____
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
 *          Head = LRU (eviction end), Tail = MRU end.
 * 
 * Doc: I used these websites for code references 
 * https://en.cppreference.com/c/memory/malloc
 * https://www.geeksforgeeks.org/dsa/create-linked-list-from-a-given-array/
 * https://www.geeksforgeeks.org/dsa/reverse-a-linked-list/
 * https://www.geeksforgeeks.org/system-design/lru-cache-implementation/
 * https://www.geeksforgeeks.org/dsa/design-a-data-structure-for-lru-cache/
 * https://www.geeksforgeeks.org/dsa/doubly-linked-list-tutorial/
 * https://www.geeksforgeeks.org/dsa/write-a-function-to-delete-a-linked-list/'
 * 
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {
    // TODO: malloc a PageQueue, set head and tail to NULL,
    //       size to 0, maxSize to maxSize, and return the pointer

    PageQueue *pq = malloc(sizeof(PageQueue));
    if (pq == NULL) {
        fprintf(stderr, "pqInit: malloc failed\n");
        exit(1);
    }
 
    pq->head    = NULL; //empty queue
    pq->tail    = NULL; //empty queue
    pq->size    = 0;    //zero pages
    pq->maxSize = maxSize;  //maximum frames
 
    return pq;
    //return NULL;
}






/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {
    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).

    long depth = 0;
    PqNode *cur = pq->tail;
 
    while (cur != NULL) {
        if (cur->pageNum == pageNum) {

        long hitDepth = depth;
 
            if (cur != pq->tail) {
 
                
                if (cur->prev != NULL) {
                    cur->prev->next = cur->next;
                } else {
                    pq->head = cur->next;
                }
 
                if (cur->next != NULL) {
                    cur->next->prev = cur->prev;
                }

                cur->prev      = pq->tail;
                cur->next      = NULL;
                pq->tail->next = cur;
                pq->tail       = cur;
            }
 
            return hitDepth;
        }
 
        cur = cur->prev;
        depth++;
    }
/*
On line regerence 
https://www.geeksforgeeks.org/dsa/reverse-a-linked-list/

struct Node {
    int data;
    struct Node *next;
};

struct Node *reverseList(struct Node *head) {

    struct Node *curr = head, *prev = NULL, *next;

    // traverse all the nodes of Linked List
    while (curr != NULL) {

        // store next
        next = curr->next;

        // reverse current node's next pointer
        curr->next = prev;

        // move pointers one position ahead
        prev = curr;
        curr = next;
    }

    return prev;
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d", node->data);
        if (node->next)
            printf(" -> ");
        node = node->next;
    }
}

struct Node *createNode(int new_data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

int main() {

    struct Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    head = reverseList(head);

    printList(head);

    return 0;
}

*/




    PqNode *node = malloc(sizeof(PqNode));


    if (node == NULL) {
        fprintf(stderr, "pqAccess... malloc failed :(\n");
        exit(1);
    }
 
    node->pageNum = pageNum;
    node->next    = NULL;
    node->prev    = pq->tail;
 
    if (pq->tail != NULL) {
        pq->tail->next = node;
    } else {
        pq->head = node;
    }
 
    pq->tail = node;
    pq->size++;
 
    if (pq->size > pq->maxSize) {
        PqNode *evict = pq->head;
        pq->head      = evict->next;
 
        if (pq->head != NULL) {
            pq->head->prev = NULL;
        } else {
            pq->tail = NULL;
        }

 
        free(evict);
        pq->size--;
    }
 
    return -1;

    //
    // HIT path (page found at depth d):
    //   - Remove the node from its current position and re-insert
    //     it at the tail (most recently used).
    //   - Return d.

    //
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.



    //return -1;
}








/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.

    if (pq == NULL) return;
 
    PqNode *cur = pq->head;


    while (cur != NULL) {
        PqNode *next = cur->next;
        free(cur);
        cur = next;
    }
 
    free(pq);  

}

/*
from online 
struct Node {
    int data;
    struct Node* next;
};

// Given the head of a list, delete the list
// using recursion
void deleteList(struct Node* curr) {

    // Base case: If the list is empty, return
    if (curr == NULL) {
        return;
    }

    // Recursively delete the next node
    deleteList(curr->next);

    // Delete the current node
    free(curr);
}

struct Node* createNode(int new_data) {
    struct Node* new_node = 
        (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}
}

*/






/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.


    if (pq == NULL) {
        fprintf(stderr, "Queue is empty!!!!!!\n");
        return;
    }

    fprintf(stderr, "Pages in queue     (oldest to newest):\n");

    PqNode *cur = pq->head;
    int position = 1;



    while (cur != NULL) {
        fprintf(stderr, "  Position %d: page %lu", position, cur->pageNum);

        if (cur == pq->head) {
            fprintf(stderr, "LRU (oldest, evicted first)");
        }


        if (cur == pq->tail) {
            fprintf(stderr, "MRU (newest, safe from eviction)");
        }

        fprintf(stderr, "\n");
        cur = cur->next;
        position++;
    }

    fprintf(stderr, "Total pages in queue: %u (max allowed: %u)\n",
            pq->size, pq->maxSize);





}
