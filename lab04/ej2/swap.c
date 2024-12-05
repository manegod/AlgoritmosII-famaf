#include <stdlib.h>
#include <stdio.h>

void swap (int *a, int *b){
    int aux;
    aux = *a; //guardo el valor de lo q hay en *a en aux
    *a = *b;  //asigno el valor dentro de  b a la var a
    *b = aux; // guardo el nuevo valor aux dentro de b
}

int main(){
int x,y;
x = 6;
y = 4;
printf("x = %d, y = %d\n",x,y);
swap(&x,&y);
printf("x = %d, y = %d\n",x,y);
}