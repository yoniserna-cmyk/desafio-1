#ifndef JUEGO_H
#define JUEGO_H

void iniciarJuego(unsigned char **tablero,int ancho,int alto);

int colision(unsigned char **tablero,
             unsigned short *pieza,
             int px,int py,
             int anchoP,int altoP,
             int ancho,int alto);

void fijarPieza(unsigned char **tablero,
                unsigned short *pieza,
                int px,int py,
                int anchoP,int altoP);

#endif
