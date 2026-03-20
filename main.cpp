#include <iostream>
#include "tablero.h"
#include "juego.h"

using namespace std;

int main()
{
    int ancho;
    int alto;

    cout<<"Ancho (multiplo de 8, minimo 8): ";
    cin>>ancho;

    cout<<"Alto (minimo 8): ";
    cin>>alto;

    if(ancho % 8 != 0)
    {
        cout<<"Error: el ancho debe ser multiplo de 8"<<endl;
        return 1;
    }

    if(ancho < 8 || alto < 8)
    {
        cout<<"Error: ancho y alto deben ser al menos 8"<<endl;
        return 1;
    }

    unsigned char **tablero = crearTablero(ancho,alto);

    iniciarJuego(tablero,ancho,alto);

    liberarTablero(tablero,alto);

    return 0;
}


