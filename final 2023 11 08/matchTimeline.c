#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matchTimeline.h"

/* ============================================================================
STRUCTS
============================================================================ */

struct s_node
{
    team team;
    event e;
    time t;
    playerNumber pn;
    struct s_node *next;
};
/*struct s_node es una estructura que define un nodo 
de una lista enlazada que representa eventos ocurridos
 en un partido de fútbol. Cada nodo almacena 
 información sobre un evento en particular y un puntero 
 al siguiente nodo de la lista.*/

struct s_matchTimeline
{
    struct s_node *head;  //declara un puntero q apunta al tipo de estructura snode
                          //head es el puntero que representa el inicio de la lista enlazada
    
    unsigned int count;  //cuantos sucesos ocurrieron
    unsigned int Home; //goles
    unsigned int Away;
    
};

/* ============================================================================
INVERP & VALIDATION
============================================================================ */


static bool invrep(matchTimeline mt)
{
    bool ret = true;
    if (mt != NULL){
        if(mt->head!=NULL){
            struct s_node *tmp;
            tmp = mt->head;
            while(tmp->next != NULL && ret){
                ret = (tmp->t <= 90) && (1 <= tmp->pn) && (tmp->pn <= 26);
                tmp = tmp->next;
            }
        }
    }
    return ret;
}

bool matchTimeline_is_time_and_score_valid(matchTimeline mt)
{
   // assert(invrep(mt));

   // Verificar que los eventos estén ordenados cronológicamente
    struct s_node *tmp = mt->head;
    struct s_node *prev = NULL;

    while (tmp != NULL) {
        
       if (prev != NULL && tmp->t < prev->t){
        return false;
       }
        prev = tmp;
        tmp=tmp->next;
    }

    // Verificar que la cantidad de goles de Home y Away se correspondan con los registros de goles
    unsigned int home_goals = 0, away_goals = 0;
    tmp = mt->head;
    while (tmp != NULL) {
        if (tmp->e == Goal) {  // Si es un gol
            if (tmp->team == Home) {
                home_goals++;  // Incrementar goles para el equipo local
            } else if (tmp->team == Away) {
                away_goals++;  // Incrementar goles para el equipo visitante
            }
        }
        tmp = tmp->next;
    }

    unsigned int home_score = matchTimeline_get_score(mt, Home);
    unsigned int away_score = matchTimeline_get_score(mt, Away);

    // Comparar la cantidad de goles en los eventos con los goles registrados
    if (home_score != home_goals || away_score != away_goals) {
        return false;  // Si no coinciden, el matchTimeline no es válido
    }

    return true;  // El matchTimeline es válido
}

/* ============================================================================
CONSTRUCTOR
============================================================================ */

matchTimeline matchTimeline_empty(void)
{
    matchTimeline mt = malloc(sizeof(struct s_matchTimeline)); //malloc reserva memoria dinámica para un objeto del tamaño de struct s_matchTimeline y devuelve un puntero a esa memoria.
    if (mt == NULL){
        printf("Error. No se pudo alojar memoria para mt.\n");
        return NULL; //Retorna null para indicar error
    }
    if (mt != NULL){
        mt->head = NULL;
        mt->count = 0;
        mt->Away = 0;
        mt->Home = 0;
    }
    
   // assert(invrep(mt));
    return mt;
}

/* ============================================================================
INSERTION
============================================================================ */

static struct s_node *create_node(team team, event e, time t, playerNumber pn)
{

    struct s_node *new_node = malloc(sizeof(struct s_node));

    if (new_node==NULL){
        printf("ERROR ALOCANDO MEMORIA.");
        return NULL;
    }

    new_node->team = team;
    new_node->e = e;
    new_node->t = t;
    new_node->pn = pn;
    new_node->next = NULL;

    return new_node;
}

/* ============================================================================
GOAL
============================================================================ */

matchTimeline matchTimeline_score_goal(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    if(t > EVENT_MAX_TIME){
        return mt;
    }
    struct s_node *newnode = create_node(team, Goal,t,pn);
    if(team ==Home){
        mt->Home++;
    } else if (team == Away){
        mt->Away++;
    }
    if (newnode==NULL){
        printf("ERORR! NO SE PUDO ASIGNAR MEMORIA PARA EL NUEVO NODO\n");
    }
    if (mt->head==NULL){
        mt->head = newnode;
    } else {

    struct s_node *tmp;

    tmp= mt->head;
    
    while(tmp->next != NULL){
        tmp=tmp->next;
    }
    tmp->next = newnode;
    
    }

    mt->count++;

    return mt;
}

/* ============================================================================
THE CARDS
============================================================================ */


matchTimeline matchTimeline_receive_yellowCard(matchTimeline mt, team team, time t, playerNumber pn)
{
   assert(invrep(mt));
   if(t > EVENT_MAX_TIME){
        return mt;
    }
    bool has2yellow = false;
    struct s_node *tmp = mt->head;
    
    while(tmp != NULL && !has2yellow){
        if(tmp->pn == pn && tmp->team == team && tmp->e == YellowCard){
            has2yellow = true;
            break;
        }
        tmp = tmp->next;
    }

    struct s_node *newnode = create_node(team, YellowCard, t, pn);

     if(newnode == NULL){
        printf("ERRORCREANDO NEWNODE\n");
    }

    if(mt->head == NULL){
        mt->head = newnode;
    }else {
   
    tmp = mt->head;
    while (tmp->next != NULL){
    tmp=tmp->next;
    }
    tmp->next = newnode;
    if(has2yellow){
        matchTimeline_receive_redCard(mt,team,t,pn);
        
    }}

    mt->count++;
    return mt;
}

matchTimeline matchTimeline_receive_redCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));

    if(t > EVENT_MAX_TIME){
        return mt;
    }

    struct s_node *newnode = create_node(team,RedCard,t,pn);

    if (newnode == NULL){
        printf("Error asignando memoria para el nuevo nodo.\n");
        return mt;
    } 


        if (mt->head == NULL){

            mt->head = newnode;

        } else {

            struct s_node *tmp = mt->head;

            while (tmp->next != NULL){
                tmp = tmp->next;
            }
            tmp->next = newnode;

        }

    mt->count++;

    
    return mt;
}

/* ============================================================================
SCORE
============================================================================ */

unsigned int matchTimeline_get_score(matchTimeline mt, team team)
{
    assert(invrep(mt));
    unsigned int g;
    if (team == Home ){
        g = mt->Home;
    }else if (team == Away){
        g = mt->Away;
    }
 

    return g;
}

/* ============================================================================
SIZE
============================================================================ */

unsigned int matchTimeline_size(matchTimeline mt)
{
    assert(invrep(mt));
    unsigned int c = mt->count;

    return c;
}

/* ============================================================================
PRINT
============================================================================ */

void matchTimeline_print(matchTimeline mt)
{
    fprintf(
        stdout, "            Home %u -  %u Away \n", 
        matchTimeline_get_score(mt, Home), 
        matchTimeline_get_score(mt, Away)
    );

    struct s_node *aux = mt->head;
    while (aux != NULL)
    {
        unsigned int t = aux->t;
        char *e;
        switch (aux->e)
        {
        case Goal:
            e = "    Goal   ";
            break;
        case YellowCard:
            e = "Yellow Card";
            break;
        case RedCard:
            e = "  Red Card ";
            break;
        }
        unsigned int pn = aux->pn;

        if (aux->team == Home) {
            fprintf(stdout, "%u - %s - %u' \n", pn, e, t);
        }
        else {
            fprintf(stdout, "                   %u' - %s - %u \n", t, e, pn);
        }

        aux = aux->next;
    }
}

/* ============================================================================
ARRAY
============================================================================ */

event *matchTimeline_events_array(matchTimeline mt)
{
    event *array = NULL;

    if (mt->head == NULL){
        printf("Error al asignar espacio para el array.\n");
    } else {

        array = malloc (mt->count * sizeof(event));

             if (array == NULL){
                 printf("ERROR AL ASIGNAR MEMORIA PARA EL ARRAY\n");
             }

        struct s_node *tmp = mt->head;
        for (unsigned int i = 0; i < mt->count; i++){
            array[i] = tmp->e;
            tmp = tmp->next;
        }
    }
    
   

    return array;
}

/* ============================================================================
DESTRUCTOR!
============================================================================ */

static struct s_node *destroy_node(struct s_node *node)
{
    
   if (node != NULL){
    free(node);
   }

    return node;
}

matchTimeline matchTimeline_destroy(matchTimeline mt)
{
    assert(invrep(mt));
    struct s_node *tmp1 = mt->head;
    while (tmp1 != NULL){
        struct s_node *tmp2 = tmp1->next;
        destroy_node(tmp1);
        tmp1 = tmp2; 
    }
    
    free(mt);
    mt = NULL;
    return mt;
}
