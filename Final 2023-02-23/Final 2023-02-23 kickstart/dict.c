#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include "key_value.h"  /* key_t               */
#include "dict.h"       /* intarface           */

struct _s_dict {
    unsigned int count;
    struct _node_t * first;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};




struct _node_t * create_node(key_t k, value_t v) {
    struct _node_t *new_node=malloc(sizeof(struct _node_t));
    new_node->key=k;
    new_node->value=v;
    new_node->next=NULL;
    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    if(node==NULL){
        return node;
    }
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    node=NULL;
    return node;
}

static bool invrep(dict_t dict) {

    return (dict!=NULL);

}
// --- Interface functions ---

dict_t dict_empty(void) {
    struct _s_dict *newdic = malloc (sizeof(struct _s_dict));
    newdic->count = 0;
    newdic->first = NULL;
    return newdic;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(dict!=NULL);

    struct _node_t *newnode = create_node(word,def);
    if (dict->first==NULL){             //caso dict vacio
        dict->first=newnode;
        dict->count++;
        return dict;
    }                                   //caso dict no vacio
    if(dict_exists(dict,word)){         //existe en el dict?
        struct _node_t *tmp = dict->first;
        while(tmp!=NULL && !string_eq(tmp->key,word)){
            tmp = tmp->next;
        }
        if(tmp==NULL){
            printf("Error: Palabra existente y no encontrada\n");
            return dict;
        }
        if(string_eq(tmp->key,word)){
            tmp->value = def;
            return dict;
        }
    } else {
        struct _node_t *tmp = dict->first;
        while(tmp->next != NULL ){
            tmp = tmp->next;
        }
        tmp->next= newnode;
        dict->count++;
        return dict;
    }
return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(dict!=NULL);

    struct _node_t *tmp = dict->first;

    if (dict->first==NULL){
        return NULL;
    } else {
        while(tmp->next!=NULL && !string_eq(tmp->key,word)){
            tmp = tmp->next;
        }
        
        if(string_eq(tmp->key,word)){
            return tmp->value;
        }
        if(tmp==NULL || tmp->next==NULL){
            printf("Error: Palabra no encontrada\n");
            return NULL;
        }
    }
return NULL;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(dict!=NULL);

    struct _node_t *tmp = dict->first;

    if (dict->first==NULL){
        return false;
    } else {
        while(tmp!=NULL){
            if(string_eq(tmp->key,word)){
                return true;
            }
            tmp=tmp->next;
        }
    return false;
    }
}

unsigned int dict_length(dict_t dict) {

    return dict->count;

}

dict_t dict_remove(dict_t dict, key_t word) {
    assert((dict!=NULL) && dict_exists(dict,word));

    struct _node_t *tmp = dict->first;

    if (dict->first==NULL){
        return dict;
    } else {
        struct _node_t *tmp2 = NULL;
        while(tmp!=NULL && !string_eq(tmp->key,word) ){
            tmp2=tmp;
            tmp=tmp->next;
        }
        if(tmp==NULL){
            printf("ERROR: Palabra no encontrada\n");
            return dict;
        }
        tmp2->next=tmp->next;
        destroy_node(tmp);
        return dict;
    
    }


}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    for (struct _node_t *check=dict->first; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
}

dict_t dict_remove_all(dict_t dict) {
    if(dict!=NULL && dict->first!=NULL){
        return dict;
    }
    struct _node_t *tmp1 = dict->first;
    
    
        struct _node_t *tmp2 = NULL;
        while(tmp1!=NULL){
            tmp2=tmp1->next;        
            destroy_node(tmp1);
            tmp1 = tmp2;
    
            }
    dict->first=NULL;
return dict;
}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict = NULL;
    return dict;
}

