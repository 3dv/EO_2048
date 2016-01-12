/* Modela tablero de juego, matriz cuadrada de casilla
   de dimension d */

#ifndef TABLERO
#define TABLERO

#include <iostream>
#include "casilla.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

typedef int posicion[2];

  class tablero {
    
  private:
      int dimension;
      casilla **tabla;
      //posicion *casillas_vacias;
    
  public:
      tablero(){/*nada */};
      tablero( int dim );
      ~tablero();
      inline int ver_dimension(){ return dimension; };
      int cant_de_vacias();
      bool rellenar_casilla();
      casilla* obtener_casilla(int, int);
      void imprimir_tablero();
	    void limpiar_sumas();
      bool valida_posicion(int , int);
      bool jugada_disponible();
  };
  
#endif
  
