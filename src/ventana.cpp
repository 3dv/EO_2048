#include <iostream>
#include "ventana.hpp"

ventana::ventana(){

	ancho = 540;
	alto = 960;

	partida = new juego();

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
		miVent = SDL_CreateWindow( "EO 2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ancho, alto, SDL_WINDOW_SHOWN );
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
				//SDL_SetRenderDrawColor( miRender, 0xFF, 0xFF, 0xFF, 0xFF );

				//Inicializamos la textura vacia
				//miTextura = SDL_CreateTexture( miRender, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, ancho, alto );

				miTextura = NULL;

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					Log::error("SDL_image no inicio. SDL_image Error:" );
					Log::error( IMG_GetError() );
				}
			}
		}

		if( TTF_Init() == -1 )
		{
			Log::error( TTF_GetError() );
		}

		fTitulo = TTF_OpenFont( "recursos/UbuntuMono.ttf", 40 );
		fCuerpo = TTF_OpenFont( "recursos/UbuntuMono.ttf", 25 );
	}


}

ventana::~ventana(){

	delete partida;
	//Free loaded image
	//SDL_DestroyTexture( miText );
	//gTexture = NULL;

	//Destroy window
	SDL_DestroyRenderer( miRender );
	SDL_DestroyWindow( miVent );
	miVent = NULL;
	miRender = NULL;
	TTF_CloseFont( fTitulo );
	fTitulo = NULL;
	TTF_CloseFont( fCuerpo );
	fCuerpo = NULL;
	SDL_DestroyTexture( miTextura );
	miTextura = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void ventana::dibujarInicio(){

	if( miTextura != NULL ) {
		SDL_DestroyTexture( miTextura );
		miTextura = NULL;
	}

	SDL_Rect fillRect = { 0, 0, ancho, alto };
	//SDL_SetRenderDrawColor( miRender, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( miRender, &fillRect );

	miTextura = SDL_CreateTexture( miRender, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, ancho, alto );

	dibujarTexto( 0, 350, "EO 2048", fTitulo );
	dibujarTexto( 0, 468, "Presione culaquier tecla para comenzar", fCuerpo );
}

void ventana::dibujarTablero( direccionJugada dir ){
	if( miTextura != NULL ) {
		SDL_DestroyTexture( miTextura );
		miTextura = NULL;
	}

	dibujarTexto( 0, 70, "EO 2048", fTitulo );

	partida->jugar( miRender, dir );


	/*SDL_Rect fillRect = { 60, 250, 420, 420 };
	   SDL_SetRenderDrawColor( miRender, 0xB5, 0xB5, 0xB5, 0xFF );
	   SDL_RenderFillRect( miRender, &fillRect );*/


}

void ventana::dibujar(direccionJugada dir){

	if( partida->obtener_estado() != partida->obtener_estado_anterior() ||
	    dir != NINGUNA ) {



		SDL_SetRenderDrawColor( miRender, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( miRender );

		switch( partida->obtener_estado() )
		{
		case BIENVENIDA:
			dibujarInicio();
			partida->igualarEstado();
			break;

		case EN_JUEGO:
			dibujarTablero( dir);
			partida->igualarEstado();
			break;
/*
        case SDLK_LEFT:
        dir = IZQUIERDA;
        break;

        case SDLK_RIGHT:
        dir = DERECHA;
        break;
 */
		default:
			break;
		}
		/*if( partida->obtener_estado() == BIENVENIDA ){
		      dibujarInicio();
		      partida->igualarEstado();
		   }else{
		   if( partida->obtener_estado() == EN_JUEGO ){
		    dibujarTablero( dir);
		    partida->igualarEstado();
		   }
		   }*/

		//partida->jugar();
	}

	/*mWidth = textSurface->w;
	   mHeight = textSurface->h;*/

	//SDL_RenderCopy( miRender, miTextura, NULL, NULL );

	SDL_RenderPresent( miRender );

}

void ventana::dibujarTexto( float x, float y, std::string texto, TTF_Font* fuente ){

	SDL_Color textColor = { 0, 0, 0 };

	if( miTextura != NULL ) {
		SDL_DestroyTexture( miTextura );
		miTextura = NULL;
	}

	SDL_Surface* superficieTexto = TTF_RenderText_Solid( fuente, texto.c_str(), textColor );
	if( superficieTexto == NULL )
	{
		Log::error( TTF_GetError() );
	}else{
		miTextura = SDL_CreateTextureFromSurface( miRender, superficieTexto );

		if( x == 0 ) {
			x = ( ancho - superficieTexto->w ) / 2;
		}

		if( y == 0 ) {
			y = ( ancho - superficieTexto->h ) / 2;
		}

		SDL_Rect cuadroRender = { x, y, superficieTexto->w, superficieTexto->h };

		SDL_RenderCopyEx( miRender, miTextura, NULL, &cuadroRender, 0.0, NULL, SDL_FLIP_NONE );

		//SDL_UpdateTexture( miTextura, &cuadroRender, superficieTexto->pixels, superficieTexto->pitch );

	}

	SDL_FreeSurface( superficieTexto );
}

void ventana::iniciar_juego(int dim){
	if( partida->obtener_estado() != EN_JUEGO )
		partida->iniciar_juego( miRender, dim );
}
