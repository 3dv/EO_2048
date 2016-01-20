/* Modela la casilla del tablero */
#ifndef CASILLA
#define CASILLA

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Log.hpp"

class casilla {
private:
    int valor;      // valor=0 casilla vacia
    bool se_ha_sumado;
    SDL_Rect formaCasilla;

public:
    casilla();
    ~casilla();

    void setDimension(int);
    bool vacia();
    bool sumada();
    void limpiar_suma();
    int ver_valor();
    void reiniciar();
    unsigned long sumar_valor( int );
    void dibujarCasilla(int, int, SDL_Renderer*);
};
#endif
