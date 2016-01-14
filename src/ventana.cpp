
#include <iostream>
#include "ventana.hpp"
#include "Log.hpp"

ventana::ventana(){

  ancho = 540;
  alto = 960;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		 Log::error("SDL no pudo inicializar. SDL error: ");
     Log::error( SDL_GetError() );
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			Log::warning( "Linear texture filtering no esta activada" );
		}

		//Create window
		miVent = SDL_CreateWindow( "EO_2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ancho, alto, SDL_WINDOW_SHOWN );
		if( miVent == NULL )
		{
			Log::error("No se creo la ventana. SDL Error: ");
      Log::error( SDL_GetError() );
		}
		else
		{
			//Create renderer for window
			miRender = SDL_CreateRenderer( miVent, -1, SDL_RENDERER_ACCELERATED );
			if( miRender == NULL )
			{
				Log::error( "No se pudo crear el renderizador. SDL Error: ");
        Log::error( SDL_GetError() );
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( miRender, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					Log::error("SDL_image no inicio. SDL_image Error:" );
          Log::error( IMG_GetError() );
				}
			}
		}
	}
}

ventana::~ventana(){
  //Free loaded image
  //SDL_DestroyTexture( miText );
  //gTexture = NULL;

  //Destroy window
  SDL_DestroyRenderer( miRender );
  SDL_DestroyWindow( miVent );
  miVent = NULL;
  miRender = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

void ventana::dibujar(){

  SDL_RenderClear( miRender );
  SDL_RenderPresent( miRender );

}
