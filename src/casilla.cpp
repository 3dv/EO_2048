#include "casilla.hpp"

  casilla::casilla() { //Constructor
    valor = 0;
	se_ha_sumado = false;
  }

  casilla::~casilla(){/*empty*/}

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
