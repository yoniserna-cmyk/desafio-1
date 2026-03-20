#include "piezas.h"
#include <cstdlib>

void generarPieza(unsigned short *pieza,int *ancho,int *alto)
{
    for(int i=0;i<4;i++) pieza[i]=0;

    int tipo = rand()%7;

    if(tipo==0) // I
    {
        *ancho = 4;
        *alto = 1;
        pieza[0] = 0b1111;
    }

    if(tipo==1) // O
    {
        *ancho = 2;
        *alto = 2;
        pieza[0] = 0b11;
        pieza[1] = 0b11;
    }

    if(tipo==2) // T
    {
        *ancho = 3;
        *alto = 2;
        pieza[0] = 0b111;
        pieza[1] = 0b010;
    }

    if(tipo==3) // L
    {
        *ancho = 3;
        *alto = 2;
        pieza[0] = 0b100;
        pieza[1] = 0b111;
    }

    if(tipo==4) // Z
    {
        *ancho = 3;
        *alto = 2;
        pieza[0] = 0b110;
        pieza[1] = 0b011;
    }

    if(tipo==5) // S
    {
        *ancho = 3;
        *alto = 2;
        pieza[0] = 0b011;
        pieza[1] = 0b110;
    }

    if(tipo==6) // J
    {
        *ancho = 3;
        *alto = 2;
        pieza[0] = 0b001;
        pieza[1] = 0b111;
    }
}

/*
 * Rotacion 90 grados en sentido horario.
 * Para cada celda (x,y) de la pieza original:
 *   nueva posicion: fila = x, columna = (alto-1-y)
 */
void rotarPieza(unsigned short *pieza,int *ancho,int *alto)
{
    unsigned short temp[4] = {0,0,0,0};

    int nuevoAncho = *alto;
    int nuevoAlto  = *ancho;

    for(int y=0;y<*alto;y++)
    {
        for(int x=0;x<*ancho;x++)
        {
            if(pieza[y] & (1<<(*ancho-1-x)))
            {
                int nuevaFila = x;
                int nuevaCol  = (*alto-1-y);
                temp[nuevaFila] |= (1<<(nuevoAncho-1-nuevaCol));
            }
        }
    }

    for(int i=0;i<4;i++)
        pieza[i]=temp[i];

    *ancho = nuevoAncho;
    *alto  = nuevoAlto;
}
