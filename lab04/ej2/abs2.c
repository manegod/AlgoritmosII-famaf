#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


void absolute(int x, int *y) { //como paso la direc de memoria, uso *y para acceder y modificarla

    if (x>=0){
        *y = x;
        
    } else {
        *y = (-x);
       
    }
}

int main(void) {
    int a=10, res=0;
    absolute(a, &res); //'&' en este caso pasa la direccion de memoria de res
    printf("%d\n",res);
    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

