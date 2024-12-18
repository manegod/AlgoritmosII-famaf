/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    bool b = (x.rank<=y.rank);
    return b;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void swap (player_t a[], unsigned int x, unsigned int y){
    player_t tmp = a[x];
    a[x] = a[y];
    a[y] = tmp;

}
void insert (player_t a[], unsigned int i){
    
    for (unsigned int j = i;1<=j;j--){
        if(goes_before(a[j],a[j-1])){
            swap(a,j,j-1);
        }
    }
}

void sort(player_t a[], unsigned int length) {
    for (unsigned int i = 1; i<length; i++){
        insert(a,i);
}
}
