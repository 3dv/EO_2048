/* Modela la casilla del tablero */ 
#ifndef CASILLA
#define CASILLA

#include <iostream>
 class casilla{
   private:
     int valor; // valor=0 casilla vacia
	   bool se_ha_sumado;
  
   public:
     casilla();
    ~casilla();
    bool vacia();
	bool sumada();
	void limpiar_suma();
    int ver_valor();
    void reiniciar();
    unsigned long sumar_valor( int );
};
#endif
