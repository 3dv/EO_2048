#include <iostream>
#include "casilla.hpp"
#include "tablero.hpp"

  class juego{
  private:
    tablero* tabla;
    unsigned long puntaje;
    enum tipo_estado { ESPERA, EN_JUEGO, FINALIZADO };
    tipo_estado estado;
    posicion jugada;
    void pedir_jugada();
    bool validar_jugada(int, int);
    bool ejecutar_jugada();
    void finalizar_juego();
    void mover(int, int);
  
  public:
    juego( int );
    ~juego();
    void jugar();
};
