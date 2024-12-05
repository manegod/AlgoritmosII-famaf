#include <stdio.h>
#include "pair.h"
/*
typedef struct s_pair_t pair_t;

struct s_pair_t {
    int values[2];
};
*/
pair_t pair_new(int x, int y){
    pair_t parnuevo;
    parnuevo.values[0] = x;
    parnuevo.values[1] = y;
    return parnuevo;
}

int pair_first(pair_t p){
    int x = p.values[0];
    return x;
}


int pair_second(pair_t p){
    int y = p.values [1];
    return y;
}
pair_t pair_swapped(pair_t p){
    pair_t q;
    q.values[0] = p.values[1];
    q.values[1] = p.values[0];
    
    return q;
}


pair_t pair_destroy(pair_t p){
    p.values[0] = 0;
    p.values[1] = 0;
    return p;
}
