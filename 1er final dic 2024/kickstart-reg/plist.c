#include <stdlib.h>   /* malloc(), free(), NULL  */
#include <stdbool.h>  /* Definition of bool      */
#include <stdio.h>    /* printf()                */
#include <assert.h>   /* assert()                */

#include "plist.h"      /* Iterface */

struct s_node {
    t_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_plist {
    t_elem ppiv;
    node_t less;
    node_t great;
    unsigned int count;
};

/* Creates a single node in dynamic memory containing the element <e>. */
static node_t create_node(t_elem e) {
    node_t newnode = NULL;
    newnode = malloc(sizeof(struct s_node));
    if (newnode==NULL){
        printf("ERROR AL CREAR EL NODO\n EXIT FAILURE\n");
        EXIT_FAILURE;
    }
    newnode->elem = e;
    newnode->next = NULL;
    return newnode;
}

/* Destroys a single node */
static node_t destroy_node(node_t node) {
    if (node == NULL){
        return node;
    }
    free (node);
    node = NULL;
    return node;
}

/* Representation invariant */
static bool invrep(plist l) {
    /////////////////////////////////////////////////////* COMPLETAR */ Q SE ASEGURE L!=NULL
    if (l==NULL){
        return false;
    }

    unsigned int checker = 1u;
    node_t aux = l->less;
    while (aux!=NULL){
        checker++;
        aux = aux->next;
    }
    aux = l->great;
    while (aux!=NULL){
        checker++;
        aux = aux->next;
    }
    if (checker!=l->count){
        return false;
    }



    return true;
}

/* CONSTRUCTORS */

plist plist_create(t_elem pivot) {  
    plist newlist = NULL;
    newlist = malloc(sizeof (struct s_plist));
    if (newlist==NULL){
        printf("ERROR AL CREAR LA LISTA\n EXIT FAILURE\n");
        EXIT_FAILURE;
    }
    newlist->count = 1u;
    newlist->less = NULL;
    newlist->great = NULL;
    newlist->ppiv = pivot;
    return newlist;
}

plist plist_add(plist l, t_elem e) {
    assert (invrep(l));
    if(t_elem_eq(l->ppiv,e)){
        return l;
    }

    node_t newnode = create_node(e);

    if (t_elem_less(e,l->ppiv)){
        if (l->less==NULL){  
            printf("agregando %d\n",e);                       //////////lista menores vacia
           l->less = newnode;
           l->count++;
           return l;
        } else {                      
            printf("agregando %d\n",e);                       //////////lista menores vacia
                         //////////lista menores no vacia
            newnode->next = l->less;
            l->less = newnode;
           l->count++;
            return l;
        }
    }else {
        if(l->great==NULL){
            printf("agregando %d\n",e);                       //////////lista menores vacia

            l->great = newnode;
           l->count++;
            return l;
        }else{
            printf("agregando %d\n",e);                       //////////lista menores vacia

            newnode->next= l->great;
            l->great = newnode;
           l->count++;
            return l;
        }

    }


}

/* OPERATIONS   */
unsigned int plist_length(plist l) {
    return l->count;
}

bool plist_is_empty(plist l) {
    return (l->count==1);
}

t_elem plist_get_pivot(plist l) {
    return l->ppiv;
}

plist plist_delete_prev(plist l) {
    assert (invrep(l));

    if (l->less==NULL){
        return l;
    } else {
        node_t aux = l->less;
        l->less = aux->next;
        destroy_node(aux);
        l->count--;
        return l;
    }

}

plist plist_delete_next(plist l) {
    assert(invrep(l));

    if(l->great==NULL){
        return l;
    } else {
        node_t aux = l->great;
        l->great = aux->next;
        destroy_node(aux);
        l->count--;
        return l;
    }
}

unsigned int plist_count(plist l, t_elem e) {
    assert (invrep(l));
    unsigned int counter = 0u;

        node_t aux = l->great;
        while (aux!=NULL){
            if(t_elem_eq(aux->elem,e)){
                counter++;
            }
            aux = aux->next;
        }
        aux = l->less;
        while (aux!=NULL){
            if(t_elem_eq(aux->elem,e)){
                counter++;
            }
            aux = aux->next;
        }
        if(t_elem_eq(l->ppiv,e)){
            counter++;
        }

    return counter;
}

t_elem * plist_to_array(plist l) {
    t_elem *array = NULL;
    array = malloc(l->count * sizeof(struct s_node));
    node_t aux = NULL;
    unsigned int index = 0u;
    aux = l->less;
    while (aux!=NULL){
        array[index] = aux->elem;
        aux = aux->next;
        index++;
    }
    array[index] = l->ppiv;
    index++;
    aux = l->great;
    while (aux!=NULL){
        array[index] = aux->elem;
        aux = aux->next;
        index++;
    }
    return array;
}

void plist_dump(plist l) {
    assert(invrep(l));
    if (plist_is_empty(l)) {
        printf("[]");
    } else {
        t_elem *elems = plist_to_array(l);
        printf("[ ");
        t_elem_dump(elems[0]);
        for (unsigned int i=1; i < plist_length(l); i++) {
            printf(", ");
            t_elem_dump(elems[i]);
        }
        printf(" ]");
        free(elems);
    }
}

plist plist_destroy(plist l) {
    if (l==NULL){
        return l;
    }
    node_t aux = NULL;
    aux = l->less;
    while (aux!=NULL){
        l->less = aux->next;
        destroy_node(aux);
        aux = l->less;
       
    }
    aux = l->great;
    while (aux!=NULL){
        l->great = aux->next;
        destroy_node(aux);
        aux = l->great;
    }

    free(l);
    l = NULL;
    return l;

}

