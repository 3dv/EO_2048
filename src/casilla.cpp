#include "casilla.hpp"
#include <string>

casilla::casilla( ) {   //Constructor
	valor = 0;
	se_ha_sumado = false;
	formaCasilla = { 0, 0, 0, 0 };
}

casilla::~casilla(){  /*vacio*/
}

void casilla::setDimension(int dim){
	formaCasilla.w = dim;
	formaCasilla.h = dim;
}

bool casilla::vacia() {
	return ( valor == 0 );
}

int casilla::ver_valor() {
	return valor;
}

void casilla::reiniciar(){
	valor = 0;
}

unsigned long casilla::sumar_valor( int val ){
	se_ha_sumado = (valor==val);
	valor = valor + val;
	if(se_ha_sumado)
		return ( (unsigned long )this->valor );
	else
		return 0;
}

bool casilla::sumada(){
	return se_ha_sumado;
}

void casilla::limpiar_suma(){
	se_ha_sumado = false;
}

void casilla::dibujarCasilla(int i, int j, SDL_Renderer* dibujante){
	formaCasilla.x = (formaCasilla.w * i) + 60;
	formaCasilla.y = (formaCasilla.h * j) + 250;
	SDL_SetRenderDrawColor( dibujante, 0xB5, 0xB5, 0xB5, 0xFF );
	SDL_RenderFillRect( dibujante, &formaCasilla);

	SDL_Rect cuadroPeque = { formaCasilla.x+3, formaCasilla.y+3, formaCasilla.w-3, formaCasilla.h-3 };
	SDL_SetRenderDrawColor( dibujante, 0xDD, 0xDD, 0xDD, 0xFF );
	SDL_RenderFillRect( dibujante, &cuadroPeque);

	if( valor != 0 ) {
		SDL_Color textColor = { 0, 0, 0 };

		TTF_Font* fuente = TTF_OpenFont( "recursos/UbuntuMono.ttf", formaCasilla.w - 20 );

		//char* val = itoa(valor);
		std::string texto = std::to_string(valor); //(char)valor+14;
		//char* texto = (char*)valor+14;//(char)valor+14;

		SDL_Surface* superficieTexto = TTF_RenderText_Solid( fuente, texto.c_str(), textColor );
		if( superficieTexto == NULL ) {
			Log::error( TTF_GetError() );
		}else{
			SDL_Texture* miTextura = SDL_CreateTextureFromSurface( dibujante, superficieTexto );

			int x = ( ( formaCasilla.w - superficieTexto->w ) / 2 ) + formaCasilla.x;

			int y = ( ( formaCasilla.h - superficieTexto->h ) / 2 ) + formaCasilla.y;

			SDL_Rect cuadroRender = { x, y, superficieTexto->w, superficieTexto->h };

			SDL_RenderCopy( dibujante, miTextura, NULL, &cuadroRender );

			SDL_DestroyTexture( miTextura );
			miTextura = NULL;
		}

		SDL_FreeSurface( superficieTexto );
		superficieTexto = NULL;

		TTF_CloseFont( fuente );
		fuente = NULL;
	}

}
