#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "rqueue.h"
#include "assert.h"

struct _node_t {
    struct _node_t * links[2];
    elem_t value;
};

typedef struct _node_t * node_t;
typedef int orientation_t;

struct _rqueue_t {
    node_t extreme[2];
    orientation_t orientation;
};

static orientation_t current(rqueue_t q) {
    return q->orientation;
}

static orientation_t inverse(rqueue_t q) {
    return 1 - q->orientation;
}

rqueue_t rqueue_empty() {
    rqueue_t newqueue = NULL;
    newqueue = malloc(sizeof (struct _rqueue_t));
    assert(newqueue!=NULL);
    newqueue->orientation=0;
    newqueue->extreme[0]=NULL;
    newqueue->extreme[1]=NULL;
    return newqueue;
}

bool rqueue_is_empty(rqueue_t q) {
    return (q->extreme[0]==NULL && q->extreme[1]==NULL);
}

static node_t create_node(elem_t e) {
    node_t newnode = NULL;
    newnode = malloc (sizeof (struct _node_t));
    assert(newnode!=NULL);
    newnode->links[0]=NULL;
    newnode->links[1]=NULL;
    newnode->value=e;
    return newnode;
}
static node_t destroy_node (node_t node){
    if (node == NULL){
        return node;
    }
    free (node);
    node = NULL;
    return node;
}

rqueue_t rqueue_enqueue(rqueue_t q, elem_t e) {

        node_t node = create_node(e);


    if (q->extreme[current(q)]==NULL){
        q->extreme[current(q)] = node;
        q->extreme[1-current(q)] = node;

    }else{
        node_t aux = q->extreme[1-current(q)];
        aux->links[1-current(q)]=node;
        node->links[current(q)] = q->extreme[1-current(q)];
        q->extreme[1-current(q)] = node;
        
    }
    

return q;
}

elem_t rqueue_fst(rqueue_t q) {
    assert(q != NULL);
    assert(!rqueue_is_empty(q));
    return q->extreme[current(q)]->value;
}

void rqueue_dequeue(rqueue_t q) {
   
    if(q==NULL ||rqueue_is_empty(q)){
        EXIT_SUCCESS;
    }

    node_t aux = NULL;
    node_t aux1 = NULL;
    aux1 = q->extreme[current(q)];
    aux = aux1->links[1-current(q)];
    if(aux!=NULL){
    aux->links[current(q)] = NULL;  //desvinculo el elem anterior de existir
    }
    q->extreme[current(q)] = aux;
    destroy_node(aux1);
    
    EXIT_SUCCESS;
}

void rqueue_revert(rqueue_t q) {
    q->orientation = 1-q->orientation;
}

rqueue_t rqueue_destroy(rqueue_t q) {
    if(rqueue_is_empty(q)){
        free(q);
        q = NULL;
        return q;
    }
    node_t aux = NULL;
    aux = q->extreme[current(q)];
    while(q->extreme[current(q)]!=NULL){
        q->extreme[current(q)] = aux->links[1-current(q)];
        destroy_node(aux);
        aux = q->extreme[current(q)];
    }
    free(q);
    q = NULL;
    return q;
}



void rqueue_dump(rqueue_t q) {
    orientation_t next;
    orientation_t fst;
    node_t aux = NULL;
    elem_t elem;
    assert(q != NULL);
    next = inverse(q);
    fst  = current(q);
    aux = q->extreme[fst];
    printf("\n Queue:");
    while(aux != NULL) {
        elem = aux->value;
        printf("%d ",elem);
        aux = aux->links[next];
    }
    printf("\n");
}
