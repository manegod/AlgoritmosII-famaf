#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;

    res.is_lowerbound = true;
    res.is_upperbound = true;
    res.exists = false;
    res.where = 0;

    for (unsigned int i=0; i<length;i++){
        if (value < arr[i]){
            res.is_upperbound = false;
        }
        if (value > arr[i]){
            res.is_lowerbound = false;
        }
        if (value == arr[i]){
            res.exists = true;
            res.where = i;
        }

    }

    return res;
}

int main(void) {
    unsigned int length;
    int value;
    unsigned int i = 0;
    printf("Ingrese un largo para su lista\n");
    scanf("%u", &length);

    int arr[length];
    while (i<length){
        printf ("Ingrese un elemento\n");
        scanf ("%d",&arr[i]);
        i++;
    }

    printf ("Ingrese un VALUE para verificar\n");
    scanf ("%d", &value);

    struct bound_data res = check_bound(value, arr, length);

    printf("Mostrando resultados:\n");

    if (res.is_lowerbound == true){
        printf ("EL VALUE ingresado es cota inferior ");
        if (res.exists == true ) {
            printf ("y el minimo de la lista. Se encuentra en la posicion %u", res.where);
        } printf ("y no se encuentra en la lista\n");
    }
    if (res.is_upperbound == true) {
        printf ("El VALUE ingresado es cota superior ");
        if (res.exists==true){
            printf ("y el maximo de la lista. Se encuentra en la posicion %u", res.where);
        } else {
            printf ("y no se encuentra en la lista\n");
        }
    }
    if ((res.is_lowerbound == false) && (res.is_upperbound== false)){
        printf ("El VALUE ingresado no es ni cota inferior ni superior");
        if (res.exists == true){
            printf (", pero aparece en la posicion numero %u\n",res.where);
        } else {
            printf (", y no aparece en la lista\n");
        }
    }

    return EXIT_SUCCESS;
}

