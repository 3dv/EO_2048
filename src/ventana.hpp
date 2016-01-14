#ifndef VENTANA
#define VENTANA

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class ventana{
    public:
      ventana();
      ~ventana();
      void dibujar();


    private:
      SDL_Window* miVent;
      SDL_Renderer* miRender;
      //SDL_Texture* miText;
      int ancho;
      int alto;
};

#endif
