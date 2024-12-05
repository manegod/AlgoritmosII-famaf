#include <stdio.h>
#include "pair.h"
#include <assert.h>
#include <stdlib.h>


pair_t pair_new(int x, int y){
    pair_t p = malloc(sizeof(pair_t));
    p->fst = x;
    p->snd = y;
    return p;
    }

elem pair_first(pair_t p){
    assert(p!=NULL);
    return p->fst;
}

elem pair_second(pair_t p){
    assert(p!=NULL);
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    assert(p!=NULL);
    pair_t q = malloc(sizeof(pair_t));
    q->fst = p->snd;
    q->snd = p->fst;
    return q;
}

pair_t pair_destroy(pair_t p){
    free(p);
    return p;
}


