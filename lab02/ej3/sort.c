#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

//No funciona para ordenar numeros negativos x ser unsigned la fun
static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
   unsigned int i,j;
   unsigned int ppiv = izq;
   i = izq+1u;
   j = der;
   while (i<=j){
    if (goes_before(a[i],a[ppiv])){
        i++;
    } else if (goes_before(a[ppiv], a[j])){
        j--;
    } else {
        swap (a,i,j);
    }
   }
   swap (a, ppiv,j);
   ppiv = j;
   return ppiv;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
  unsigned int ppiv;
    if (izq<der){
        ppiv = partition(a,izq,der);
        quick_sort_rec (a, izq, ppiv == 0 ? ppiv : ppiv-1);
        quick_sort_rec (a,ppiv == der ? der : ppiv+1 ,der);

    }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

