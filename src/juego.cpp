#include "juego.hpp"

juego::juego(){

	srand(time(NULL));

	tabla = NULL;
	//vent = new ventana();

	estadoAnterior = VACIO;
	estado = BIENVENIDA;
	puntaje = 0;
	jugada[0] = 0;
	jugada[1] = 0;

	/*tabla->rellenar_casilla();
	   tabla->rellenar_casilla();
	   tabla->imprimir_tablero();*/

}

juego::~juego(){
	delete tabla;

}

void juego::iniciar_juego( SDL_Renderer* dibujante, int dim ){
	estadoAnterior = estado;
	estado = EN_JUEGO;
	if( !tabla ) {
		tabla = new tablero(dim);

		tabla->rellenar_casilla();
		tabla->rellenar_casilla();
		tabla->imprimir_tablero(dibujante);
	}
}

tipo_estado juego::obtener_estado(){
	return estado;
}

tipo_estado juego::obtener_estado_anterior(){
	return estadoAnterior;
}

void juego::igualarEstado(){
	estadoAnterior = estado;
}

bool juego::procesar_jugada(direccionJugada dir){
	//int dir = -1;
	//std::cout << " Ingrese 0 para salir\n ";
	//while (dir!= 0 && dir!=8 && dir!=4 && dir!=5  && dir!=6) {
	std::cout << " la jugada es " << dir << std::endl;
	//std::cin >> dir;
	switch (dir) {
	case ABAJO:         // abajo
		jugada[0] = 0;
		jugada[1] = 1;
		return true;
		break;
	case ARRIBA:         // arriba
		jugada[0] = 0;
		jugada[1] = -1;
		return true;
		break;
	case IZQUIERDA:         // izquierda
		jugada[0] = -1;
		jugada[1] = 0;
		return true;
		break;
	case DERECHA:         // derecha
		jugada[0] = 1;
		jugada[1] = 0;
		return true;
		break;
	case SALIR:         // Salir del juego
		std::cout << " \tGracias por jugar: ¡hasta la próxima!" << std::endl;
		estado = FINALIZADO;
		return false;
		break;
	default:
		std::cout << " Jugada "<< dir << " no aceptada " << std::endl;
		return false;
		//tabla->imprimir_tablero();
	}
	//}
	//tabla->imprimir_tablero();
}

/* Metodo Validar jugada: evalua que la jugada ingresada este dentro del rango [0,dim]
 * que la casilla siguiente esté vacia y sino que esté ocupada con un valor igual a la
   casilla sobre la que se itera */

bool juego::validar_jugada(int i, int j){

	int dim = tabla->ver_dimension();
	casilla* casilla_act = tabla->obtener_casilla( i, j );
	casilla* casilla_sig = tabla->obtener_casilla( i+jugada[0], j+jugada[1] );

	/* si (pos > 0 && pos < dim) entonces:
	 *	 si (casilla_sig.esta_vacia())
	 *    entonces retorna true
	 *   de lo contrario
	 *    si (casilla_sig.valor() == casilla_act.valor() &  no_sumada) entonces
	 *      retorna true
	 *    de lo contrario:
	 *      retonar falso
	 *   de lo contrario:
	 *   retorna falso
	 */

	if (  ((i+jugada[0]) >= 0) && ((i+jugada[0]) < dim )
	      && ((j+jugada[1]) >= 0) && ((j+jugada[1]) < dim) ) {
		if (casilla_sig->vacia())
			return true;
		else{
			if(
			        ( casilla_act->ver_valor() == casilla_sig->ver_valor() ) &&
			        !casilla_sig->sumada() &&
			        !casilla_act->sumada()
			        )
				return true;
			else
				return false;
		}
	}
	else
		return false;
	;
}

void juego::mover(int i, int j){
	int val = tabla->obtener_casilla( i, j )->ver_valor();
	//std::cout << "jugada valida, moviendo i, j = " << i <<", " << j << " moviendo valor " << val << " a casilla -> " << i+jugada[0] <<", " << j+jugada[1] << std::endl;
	tabla->obtener_casilla( i, j )->reiniciar();
	puntaje +=  tabla->obtener_casilla( i+jugada[0], j+jugada[1] )->sumar_valor(val);
}

bool juego::ejecutar_jugada(){

	/*int Icero = 0;
	   int Ifinal = tabla->ver_dimension();

	   int Jcero = tabla->ver_dimension()-1;
	   int Jfinal = 0;*/

	int dim = tabla->ver_dimension();
	bool haMovido = false;

	for (int i = 0; i < dim; i++) {
		//std::cout << "moviendo en i = " << i << std::endl;
		for (int j = 0; j < dim; j++) {

			//-- verificaremos la jugada y haremos que la matriz se recorra en el sentido deseado según la jugada.
			int __i;
			int __j;

			if ( jugada[1] == 1 ) { // abajo
				__i = i;
				__j = dim-1-j;
			}else{
				if ( jugada[1] == -1 ) { //arriba
					__i = i;
					__j = j;
				}else{
					if ( jugada[0] == 1 ) { //derecha
						__i = dim-1-j;
						__j = i;
					}else{
						if ( jugada[0] == -1 ) { // izquierda
							__i = j;
							__j = i;
						}
					}
				}
			}

			//std::cout << "parado en i, j = " << __i <<", " << __j << std::endl;

			if ( !tabla->obtener_casilla( __i, __j )->vacia() ) {

				int despj = 0;
				int despi = 0;
				int itera = 0;
				bool continua = true;

				while( continua ) {

					despj = ( itera * jugada[1] );
					despi = ( itera * jugada[0] );
					//std::cout << "casilla con elemento-> " << tabla->obtener_casilla(__i+despi, __j+despj)->ver_valor() << ", se buscara en i,j->" << __i+despi+jugada[0] << ","<< __j+despj+jugada[1] << ", despi-> " << despi << ", despj-> " << despj << std::endl;
					continua = validar_jugada(__i+despi,__j+despj);
					if (continua) {
						mover(__i+despi,__j+despj);
						haMovido = true;
					}

					//std::cout << "se han sumando " << cantsum << " veces." << std::endl;
					itera++;
				}
				//delete cantsum;
			}else{
				//std::cout << "casilla vacia!" << std::endl;
			}

		}
	}


	if(haMovido)
		tabla->rellenar_casilla();
	tabla->limpiar_sumas();
	//tabla->imprimir_tablero( dibujante );
	std::cout << "\t Puntaje: " << this->puntaje << std::endl;
	/*if ( !tabla->jugada_disponible( ) ){
	   return false;
	   final del juego -- sin casillas disponibles ni jugada posible
	   }*/
	return true;
}

void juego::finalizar_juego(){

	std::cout << "\n\t¡Juego terminado!" << std::endl;
	std::cout << "\t Puntaje: " << this->puntaje << std::endl;
	estado = FINALIZADO;
}

/* Metodo Jugar: evalua el estado del juego, pide la jugada
 * llama a ejecutar la jugada y por ultimo imprime el tablero */
void juego::jugar( SDL_Renderer* dibujante, direccionJugada dir){

	if( tabla->jugada_disponible() ) {
		if( procesar_jugada( dir ) ) {
			ejecutar_jugada();
		}
		tabla->imprimir_tablero(dibujante);
	}else{
		finalizar_juego();
	}
	/*while ( estado == EN_JUEGO ) {
	   bool salir = false;
	   SDL_Event evento;

	   while ( !salir ) {
	        while( SDL_PollEvent( &evento ) != 0 ){
	                if ( evento.type == SDL_QUIT )
	                      salir = true;
	        }
	        //vent->dibujar();
	        if( tabla->jugada_disponible() ) {
	                pedir_jugada();
	                ejecutar_jugada();
	        }else{
	                finalizar_juego();
	        }

	   }

	   delete vent;*/

}

/*void juego::dibujarForma( SDL_Renderer* dibujante, direccionJugada dir){

   int x = 60;
   int y = 250;

   procesar_jugada( dir );
   jugar( dibujante );


   SDL_Rect fillRect = { x, y, 420, 420 };
   SDL_SetRenderDrawColor( dibujante, 0xB5, 0xB5, 0xB5, 0xFF );
   SDL_RenderFillRect( dibujante, &fillRect );

   }*/
