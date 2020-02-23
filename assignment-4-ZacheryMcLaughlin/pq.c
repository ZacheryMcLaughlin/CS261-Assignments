/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Zachery McLaughlin
 * Email: mclaughz@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq {
  struct dynarray* array;
};

struct priority_item {
  int priority;
  void* value;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* p = (struct pq*) malloc(sizeof(struct pq));
  struct dynarray* dyn = dynarray_create();
  p->array = dyn;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  dynarray_free(pq->array);
  free(pq);
  return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  dynarray_isempty(pq->array);
}

void _pq_insert_(struct pq* pq, int idx){
  struct priority_item* cur = dynarray_get(pq->array, idx);
  struct priority_item* parent = dynarray_get(pq->array, (idx-1)/2);
  if(idx == (idx-1)/2){
    return;
  }
  if(idx < 0 || (idx-1)/2 < 0){
    return;
  }
  else if(cur->priority < parent->priority){
    dynarray_set(pq->array, idx, cur);
    dynarray_set(pq->array, (idx-1)/2, parent);
    _pq_insert_(pq, (idx-1)/2);
  }
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  struct priority_item* pr = (struct priority_item*) malloc(sizeof(struct priority_item));
  pr -> value = value;
  pr -> priority = priority;
  dynarray_insert(pq->array, value);
  _pq_insert_(pq, dynarray_size(pq->array)-1);
  print(pq);
  return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  void* val = dynarray_get(pq->array, 0);
  return val;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  struct priority_item* pri = dynarray_get(pq->array, 0);
  return pri->priority;
}

void _pq_remove_first_(struct pq* pq, int idx){
  struct priority_item* cur = dynarray_get(pq->array, idx);
  if((idx*2) < dynarray_size(pq->array) && (idx*2 + 1) < dynarray_size(pq->array)){
    struct priority_item* left = dynarray_get(pq->array, idx*2);
    struct priority_item* right = dynarray_get(pq->array, idx*2 + 1);
    if(left->priority < right->priority && left->priority < cur->priority){
      struct priority_item* temp = left;
      dynarray_set(pq->array, idx*2, temp);
      cur = temp;
      _pq_remove_first_(pq, idx*2);
    }
    else if(right->priority < cur->priority){
      struct priority_item* temp = right;
      dynarray_set(pq->array, idx*2+1, temp);
      cur = temp;
      _pq_remove_first_(pq, idx*2+1);
    }
  }
  else if((idx*2) < dynarray_size(pq->array)){
    struct priority_item* left = dynarray_get(pq->array, idx*2);
    if(left->priority < cur->priority){
      struct priority_item* temp = left;
      dynarray_set(pq->array, idx*2, temp);left = cur;
      cur = temp;
      _pq_remove_first_(pq, idx*2);
    }
  }
  else if((idx*2 + 1) < dynarray_size(pq->array)){
    struct priority_item* right = dynarray_get(pq->array, idx*2 + 1);
    if(right->priority < cur->priority){
      struct priority_item* temp = right;
      dynarray_set(pq->array, idx*2+1, temp);
      cur = temp;
      _pq_remove_first_(pq, idx*2+1);
    }
  }
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  void* val = dynarray_get(pq->array, 0);
  void* val2 = dynarray_get(pq->array, dynarray_size(pq->array)-1);
  void* temp;
  temp = val;
  val = val2;
  val2 = temp;
  dynarray_remove(pq->array, dynarray_size(pq->array)-1);
  _pq_remove_first_(pq, 0);
  //print(pq);
  return val;
}

void print(struct pq* pq){
  printf("\n");
  for(int i = 0; i < dynarray_size(pq->array); i++){
    struct priority_item* parent = dynarray_get(pq->array, (i-1)/2);
    struct priority_item* child = dynarray_get(pq->array, i);
    printf("[%d] %d || parent %d", i, child->priority, (i-1)/2);

    if(child->priority < parent->priority){
      printf(" ERROR ");
    }
    printf("\n");
  }
}
