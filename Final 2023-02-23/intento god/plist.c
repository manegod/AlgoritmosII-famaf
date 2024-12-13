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
    struct s_node *menores;
    struct s_node *mayores;
    t_elem pivot;
    unsigned int cant; // <3
};

/* Creates a single node in dynamic memory containing the element <e>. */
static node_t create_node(t_elem e) {
    struct s_node *newnode = malloc(sizeof(node_t));
    if (newnode==NULL){
        printf("Error creando el nuevo nodo \n");
        EXIT_FAILURE;
    }
    newnode->elem = e;
    newnode->next = NULL;
    return newnode;
}

/* Destroys a single node */
static node_t destroy_node(node_t node) {
   //assert(node!=NULL);/////////////////////////////////CORTAR TODO A LA BOSTA O MANEJARLO?/////////////////////////
    if (node==NULL){
        return node;
    }
    free (node);
    node = NULL;
    return node;
}

/* Representation invariant */
static bool invrep(plist l) {
    /* COMPLETAR */
    
    unsigned int cuenta = 1;
    struct s_node *tmp = NULL;
    tmp = l->mayores;
    while(tmp!=NULL){
        cuenta++;
        tmp=tmp->next;
    }
    tmp = l->menores;
    while(tmp!=NULL){
        cuenta++;
        tmp=tmp->next;
    }
    if (cuenta!=l->cant){
        return false;
    }
    return true;
    //que no sea igual al pivot el nuevo elem
    //que haya la misma cant de nodos y de value cant
}

/* CONSTRUCTORS */

plist plist_create(t_elem pivot) {
    plist newlist = malloc(sizeof(struct s_plist));
    if(newlist==NULL){
        printf("Error creando nueva lista\n");
        return NULL;
    }
    newlist->cant=1u;
    newlist->mayores = NULL;
    newlist->menores = NULL;
    newlist->pivot = pivot;
    return newlist;
}   

plist plist_add(plist l, t_elem e) {
    assert(l!=NULL);
    if(t_elem_eq(e,l->pivot)){
        return l;
    }
    if(t_elem_less(e,l->pivot)){
        struct s_node *newnode = create_node(e);
        if(l->menores==NULL){
            l->menores = newnode;
            l->cant++;
            return l;
        }else{
        newnode->next = l->menores;
        l->menores = newnode;
        l->cant++;
        return l;
        }
    }else if (t_elem_greater(e,l->pivot)){
        struct s_node *newnode = create_node(e);
        if(l->mayores==NULL){
            l->mayores = newnode;
            l->cant++;
            return l;
        }else{
        newnode->next = l->mayores;
        l->mayores = newnode;
        l->cant++;
        return l;
        }
    }
return l;
}

/* OPERATIONS   */
unsigned int plist_length(plist l) {
     return (l->cant);
}

bool plist_is_empty(plist l) {
    return (l->cant==1u);
}

t_elem plist_get_pivot(plist l) {
    return l->pivot;
}

plist plist_delete_prev(plist l) {
    assert(l!=NULL);
    if(l->menores==NULL){
        return l;
    }else{
    struct s_node *tmp = NULL;
    tmp = l->menores;
    l->menores = tmp->next;
    destroy_node(tmp);
    l->cant--;
  }
    return l;
}

plist plist_delete_next(plist l) {
    assert(l!=NULL);
    if(l->mayores==NULL){
        return l;
    }
    struct s_node *tmp = NULL;
    tmp = l->mayores;
    l->mayores = tmp->next;
    destroy_node(tmp);
    l->cant--;
    return l;
}

unsigned int plist_count(plist l, t_elem e) {
    unsigned int a = 0u;

    struct s_node *tmp = NULL;
    tmp = l->menores;
    while(tmp!=NULL){
        if(t_elem_eq(e,tmp->elem)){
            a++;
        }
        tmp = tmp->next;
    }

    if (t_elem_eq(e,l->pivot)){
        a++;
    }

    tmp = l->mayores;
    while(tmp!=NULL){
        if(t_elem_eq(e,tmp->elem)){
            a++;
        }
        tmp = tmp->next;
    }

return a;
}

t_elem * plist_to_array(plist l) {

    assert(l!=NULL);
    struct s_node *tmp = NULL;
    t_elem *array = malloc(l->cant * sizeof(t_elem)+1);
    tmp = l->menores;
    int index = 0;
    while(tmp!=NULL){
        array[index]=tmp->elem;
        index++;
        tmp = tmp->next;
    }
    array[index] = l->pivot;
    index++;
    tmp = l->mayores;
    while(tmp!=NULL){
        array[index]=tmp->elem;
        index++;
        tmp = tmp->next;
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
    if(l==NULL){
        return l;
    }

    struct s_node *tmp = NULL;
    tmp = l->menores;
    while(tmp!=NULL){
        l->menores = tmp->next;
        destroy_node(tmp);
        tmp = NULL;
        tmp = l->menores;
    }
    tmp = l->mayores;
     while(tmp!=NULL){
        l->mayores = tmp->next;
        destroy_node(tmp);
        tmp = NULL;
        tmp = l->mayores;
    }  

    free(l); 
    l = NULL;
    return l;
}

