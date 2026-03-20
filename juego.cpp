#include "juego.h"
#include "tablero.h"
#include "piezas.h"

#include <iostream>

using namespace std;

// Elimina filas completas y baja las superiores
static void eliminarFilas(unsigned char **tablero,int ancho,int alto)
{
    int bytesFila = ancho/8;

    for(int y=0;y<alto;y++)
    {
        int llena = 1;

        for(int b=0;b<bytesFila;b++)
        {
            if(tablero[y][b] != 255)
            {
                llena = 0;
                break;
            }
        }

        if(llena)
        {
            // Bajar todas las filas superiores
            for(int i=y;i>0;i--)
            {
                for(int b=0;b<bytesFila;b++)
                {
                    tablero[i][b] = tablero[i-1][b];
                }
            }

            // Limpiar fila superior
            for(int b=0;b<bytesFila;b++)
            {
                tablero[0][b] = 0;
            }

            // Revisar la misma fila y de nuevo (ahora tiene el contenido de la de arriba)
            y--;
        }
    }
}

void iniciarJuego(unsigned char **tablero,int ancho,int alto)
{
    unsigned short pieza[4];

    int anchoP;
    int altoP;

    generarPieza(pieza,&anchoP,&altoP);

    int px = ancho/2 - anchoP/2;
    int py = 0;

    // Verificar Game Over al inicio (tablero ya lleno)
    if(colision(tablero,pieza,px,py,anchoP,altoP,ancho,alto))
    {
        imprimirTablero(tablero,ancho,alto);
        cout<<"GAME OVER"<<endl;
        return;
    }

    char tecla;

    while(true)
    {
        // Borde superior
        cout<<" ";
        for(int i=0;i<ancho;i++)
            cout<<"-";
        cout<<endl;

        for(int i=0;i<alto;i++)
        {
            cout<<"|";

            for(int j=0;j<ancho;j++)
            {
                int mostrar = ocupado(tablero,j,i);

                // Superponer pieza activa
                for(int y=0;y<altoP;y++)
                {
                    for(int x=0;x<anchoP;x++)
                    {
                        if(pieza[y] & (1<<(anchoP-1-x)))
                        {
                            if(j==px+x && i==py+y)
                                mostrar = 1;
                        }
                    }
                }

                if(mostrar)
                    cout<<"#";
                else
                    cout<<".";
            }

            cout<<"|"<<endl;
        }

        // Borde inferior
        cout<<" ";
        for(int i=0;i<ancho;i++)
            cout<<"-";
        cout<<endl;

        cout<<"Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
        cin>>tecla;

        // Salir
        if(tecla=='q' || tecla=='Q')
        {
            cout<<"Hasta luego!"<<endl;
            break;
        }

        // Mover izquierda: verificar borde Y colision con bloques
        if(tecla=='a' || tecla=='A')
        {
            if(px > 0 && !colision(tablero,pieza,px-1,py,anchoP,altoP,ancho,alto))
                px--;
        }

        // Mover derecha: verificar borde Y colision con bloques
        if(tecla=='d' || tecla=='D')
        {
            if(px+anchoP < ancho && !colision(tablero,pieza,px+1,py,anchoP,altoP,ancho,alto))
                px++;
        }

        // Bajar
        if(tecla=='s' || tecla=='S')
        {
            if(!colision(tablero,pieza,px,py+1,anchoP,altoP,ancho,alto))
            {
                py++;
            }
            else
            {
                // Fijar pieza
                fijarPieza(tablero,pieza,px,py,anchoP,altoP);

                // Eliminar filas completas
                eliminarFilas(tablero,ancho,alto);

                // Generar nueva pieza
                generarPieza(pieza,&anchoP,&altoP);

                px = ancho/2 - anchoP/2;
                py = 0;

                // Verificar Game Over
                if(colision(tablero,pieza,px,py,anchoP,altoP,ancho,alto))
                {
                    imprimirTablero(tablero,ancho,alto);
                    cout<<"GAME OVER"<<endl;
                    break;
                }
            }
        }

        // Rotar: guardar estado anterior y revertir si hay colision
        if(tecla=='w' || tecla=='W')
        {
            unsigned short piezaAntes[4];
            int anchoAntes = anchoP;
            int altoAntes  = altoP;

            for(int i=0;i<4;i++)
                piezaAntes[i] = pieza[i];

            rotarPieza(pieza,&anchoP,&altoP);

            if(colision(tablero,pieza,px,py,anchoP,altoP,ancho,alto))
            {
                // Revertir rotacion
                for(int i=0;i<4;i++)
                    pieza[i] = piezaAntes[i];
                anchoP = anchoAntes;
                altoP  = altoAntes;
            }
        }
    }
}

int colision(unsigned char **tablero,
             unsigned short *pieza,
             int px,int py,
             int anchoP,int altoP,
             int ancho,int alto)
{
    for(int y=0;y<altoP;y++)
    {
        for(int x=0;x<anchoP;x++)
        {
            if(pieza[y] & (1<<(anchoP-1-x)))
            {
                int tx = px + x;
                int ty = py + y;

                if(ty >= alto)
                    return 1;

                if(tx < 0 || tx >= ancho)
                    return 1;

                if(ocupado(tablero,tx,ty))
                    return 1;
            }
        }
    }

    return 0;
}

void fijarPieza(unsigned char **tablero,
                unsigned short *pieza,
                int px,int py,
                int anchoP,int altoP)
{
    for(int y=0;y<altoP;y++)
    {
        for(int x=0;x<anchoP;x++)
        {
            if(pieza[y] & (1<<(anchoP-1-x)))
            {
                colocarBloque(tablero,px+x,py+y);
            }
        }
    }
}
