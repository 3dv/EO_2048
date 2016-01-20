#include <iostream>
#include <math.h>

#include "casilla.hpp"
#include "tablero.hpp"
//#include "ventana.hpp"

enum tipo_estado { VACIO, BIENVENIDA, ESPERA, EN_JUEGO, FINALIZADO };
enum direccionJugada { NINGUNA, ARRIBA, ABAJO, DERECHA, IZQUIERDA, SALIR };

class juego{

  private:
    tablero* tabla;
    unsigned long puntaje;
    tipo_estado estado;
    tipo_estado estadoAnterior;
    posicion jugada;
    bool procesar_jugada(direccionJugada);
    bool validar_jugada(int, int);
    bool ejecutar_jugada();
    void finalizar_juego();
    void mover(int, int);

  public:
    juego();
    ~juego();
    void jugar(SDL_Renderer*, direccionJugada);
    tipo_estado obtener_estado();
    tipo_estado obtener_estado_anterior();
    void igualarEstado();
    void iniciar_juego( SDL_Renderer* dibujante, int );
    //void dibujarForma( SDL_Renderer* );
  };
