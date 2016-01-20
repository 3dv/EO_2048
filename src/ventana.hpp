#ifndef VENTANA
#define VENTANA

#include <iostream>

#include "juego.hpp"

class ventana{
    public:
      ventana();
      ~ventana();
      void dibujar(direccionJugada dir);
      void iniciar_juego(int);


    private:
      TTF_Font* fTitulo;
      TTF_Font* fCuerpo;
      SDL_Window* miVent;
      SDL_Renderer* miRender;
      SDL_Texture* miTextura;
      int ancho;
      int alto;
      juego* partida;

      void dibujarTexto( float x, float y, std::string texto, TTF_Font* fuente );
      void dibujarInicio();
      void dibujarTablero(direccionJugada dir);
};

#endif
