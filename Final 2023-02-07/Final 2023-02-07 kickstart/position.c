#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "position.h"

struct _position {
        unsigned int row;
        unsigned int column;
        unsigned int dimension;
};


position_t position_initial(unsigned int dimension)
{
        position_t  p = malloc(sizeof(struct _position));
        if (p==NULL){
                printf("Error: no se pudo generar la posicion\n");
                return NULL;
        }
        p->row = 0;
        p->column = 0;
        p->dimension = dimension;
        return p;
}

position_t position_absolute(unsigned int row, unsigned int column,
                             unsigned int dimension)
{
        position_t p = position_initial(dimension);
        if(p==NULL){
                printf("Error al crear la nueva posicion\n");
                return NULL;
        }
        p->column = column;
        p->dimension = dimension;
        p->row = row;
        return p;
}

position_t position_left(position_t pos)
{
        assert(pos!=NULL);
        if (pos->column == 0){
                pos->column = ((pos->dimension)-1u);
        } else {
                pos->column--;
        }

        return pos;
}

position_t position_right(position_t pos)
{
        assert(pos!=NULL);
        if (pos->column == ((pos->dimension)-1u)){
                pos->column = 0u;
        } else {
                pos->column++;
        }

        return pos;
        
}

position_t position_down(position_t pos)
{
        assert(pos!=NULL);
        if (pos->row == pos->dimension-1){
                pos->row = 0u;
        } else {
                pos->row++;
        }

        return pos;
}

position_t position_up(position_t pos)
{
        assert(pos!=NULL);
        if (pos->row == 0u){
                pos->row = ((pos->dimension)-1u);
        } else {
                pos->row--;
        }

        return pos;
}

unsigned int position_row(position_t pos)
{
        assert(pos!=NULL);
        return pos->row;
}

unsigned int position_column(position_t pos)
{
        assert(pos!=NULL);
        return pos->column;
}

unsigned int **position_board(position_t pos)
{
        unsigned int **tabla = (unsigned int**)malloc(pos->dimension * sizeof(unsigned int*));
        if(tabla==NULL){
                return NULL;
        }
        
        for(unsigned int i = 0; i<pos->dimension; i++){
                tabla[i]=(unsigned int *)calloc(pos->dimension, sizeof(unsigned int)); //inicializo todos en 0
                /*for(unsigned int j = 0; j<pos->dimension; j++){
                      tabla[i][j] = 0u;}*/
        }
        tabla[pos->column][pos->row]=1;
        
return tabla;
}



list_t position_movements(position_t pos)
{
        position_t aux = position_initial(pos->dimension);
        list_t newlist = list_empty();
       
                while(aux->column!=pos->column){
                     newlist = list_append(newlist,RIGHT);   
                     aux = position_right(aux);
                }
                while (aux->row!=pos->row){
                     newlist = list_append(newlist,DOWN);   
                     aux = position_down(aux);
                }

return newlist;

}

position_t position_destroy(position_t pos)
{
        if (pos != NULL && pos != NULL){
        pos->column = 0;
        pos->dimension = 0;
        pos->row = 0;
        free(pos);
        pos=NULL;
        }
        return pos;
}
