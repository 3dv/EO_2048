/*LLamado al juego!! YUJUU*/

#include <iostream>
#include "ventana.hpp"

using namespace std;

int main( int argc, char** args){
	//juego* J = new juego();
	//J->jugar();

	bool salir = false;

	ventana* vent = new ventana();

	SDL_Event evento;

	direccionJugada dir = NINGUNA;

	while ( !salir ) {
		while( SDL_PollEvent( &evento ) != 0 ) {
			if ( evento.type == SDL_QUIT ) {
				salir = true;
				dir = SALIR;
			}else if( evento.type == SDL_KEYDOWN ) {
				vent->iniciar_juego(4);
				switch( evento.key.keysym.sym )
				{
				case SDLK_UP:
					dir = ARRIBA;
					break;

				case SDLK_DOWN:
					dir = ABAJO;
					break;

				case SDLK_LEFT:
					dir = IZQUIERDA;
					break;

				case SDLK_RIGHT:
					dir = DERECHA;
					break;

				default:
					break;
				}
			}
		}
		vent->dibujar(dir);
		dir = NINGUNA;
		/*if( tabla->jugada_disponible() ) {
		        pedir_jugada();
		        ejecutar_jugada();
		   }else{
		        finalizar_juego();
		   }*/


	}
	delete vent;


	return 0;
}
