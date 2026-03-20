#include "tablero.h"
#include <iostream>

using namespace std;

unsigned char **crearTablero(int ancho,int alto)
{

    int bytesFila = ancho/8;

    unsigned char **tablero = new unsigned char*[alto];

    for(int i=0;i<alto;i++)
    {

        tablero[i] = new unsigned char[bytesFila];

        for(int j=0;j<bytesFila;j++)
            tablero[i][j] = 0;

    }

    return tablero;

}

void liberarTablero(unsigned char **tablero,int alto)
{

    for(int i=0;i<alto;i++)
        delete[] tablero[i];

    delete[] tablero;

}

int ocupado(unsigned char **tablero,int x,int y)
{

    int byte = x/8;
    int bit = x%8;

    return tablero[y][byte] & (1<<(7-bit));

}

void colocarBloque(unsigned char **tablero,int x,int y)
{

    int byte = x/8;
    int bit = x%8;

    tablero[y][byte] |= (1<<(7-bit));

}

void limpiarBloque(unsigned char **tablero,int x,int y)
{

    int byte = x/8;
    int bit = x%8;

    tablero[y][byte] &= ~(1<<(7-bit));

}

void imprimirTablero(unsigned char **tablero,int ancho,int alto)
{

    // borde superior
    cout<<" ";
    for(int i=0;i<ancho;i++)
        cout<<"-";
    cout<<endl;

    for(int i=0;i<alto;i++)
    {

        cout<<"|";

        for(int j=0;j<ancho;j++)
        {

            if(ocupado(tablero,j,i))
                cout<<"#";
            else
                cout<<".";

        }

        cout<<"|"<<endl;

    }

    // borde inferior
    cout<<" ";
    for(int i=0;i<ancho;i++)
        cout<<"-";
    cout<<endl;

}
