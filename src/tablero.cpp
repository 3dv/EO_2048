#include "tablero.hpp"

  tablero::tablero( int dim ){
    dimension = dim;
    
    tabla = new casilla* [dim];
    for(int i = 0 ; i < dim ; i++ ){
	tabla[i]= new casilla[dim];
    } 
  }
  
  tablero::~tablero(){
    for ( int i=0 ; i < dimension; i++)
      delete[] tabla[i];
    delete[] tabla;
  }

  int tablero::cant_de_vacias(){
    
    int tamano = 0;
    
    for(int i=0 ; i < dimension ; i++){
      for(int j=0 ; j < dimension ; j++){
	if( tabla[i][j].vacia() )
	  tamano++;
      }
    }
    return tamano;
   }
   
  bool tablero::rellenar_casilla(){
 
    int tam = cant_de_vacias();
    
    if(tam==0)
      return false; 
    
    int cont_vacias = 0; 
    posicion *casillas_vacias = new posicion[tam];
    
    for(int i=0 ; i < dimension ; i++){
      for(int j=0 ; j < dimension ; j++){
	if( tabla[i][j].vacia() )
	{
	  //posicion aux = { i , j } ;
	  casillas_vacias[cont_vacias][0]= i ;
	  casillas_vacias[cont_vacias][1]= j ;
	  cont_vacias++;
	}
      }
    }
    
    //srand (time(NULL));
    int rdm = rand() % cont_vacias; //casilla a rellenar
    int valor = round(rand()%10 + 1); //valores entre 1-4
    tabla[ casillas_vacias[rdm][0] ][ casillas_vacias[rdm][1] ].sumar_valor(valor <= 6 ? 2 : 4) ;
    return true;
  }
 
 casilla* tablero::obtener_casilla(int i, int j){
   	return &tabla[i][j];
 }
 
  void tablero::imprimir_tablero(){
    for (int j=0 ; j<dimension ; j++){
      for (int i= 0 ; i<dimension ; i++){
		  //std::cout<< "\t pos[" << i << "][" << j << "]->" << tabla[i][j].ver_valor() ;// << "\t";
		  if(tabla[i][j].ver_valor()==0){
			  std::cout<< " " << "_";// << "\t";
		  }else{
			  std::cout<< " " << tabla[i][j].ver_valor() ;
		  }
	  }
		std::cout<<std::endl;
    }
  }

  void tablero::limpiar_sumas(){
	 for (int j=0 ; j<dimension ; j++){
      for (int i= 0 ; i<dimension ; i++)
			tabla[i][j].limpiar_suma ();
    } 
  }

  bool tablero::valida_posicion( int i, int j){
   if (  (i>= 0) && (i < dimension )
     && (j >= 0) && (j < dimension) )
      return true;
  else
      return false;
  }

  bool tablero::jugada_disponible(){
   if( this->cant_de_vacias() > 0 )
      return true;
   else{
        for( int i=0 ; i < this->dimension ; i++){
          for( int j=0 ; j < this->dimension ; j++){
            if( this->valida_posicion( i+1 , j) ){ 
              if( tabla[i][j].ver_valor() == tabla[i+1][j].ver_valor() )
                return true;
              }
            if( this->valida_posicion(i, j+1)){
              if( tabla[i][j].ver_valor() == tabla[i][j+1].ver_valor() )
                return true;
              }
            }
          }
        }    
    return false;
  }
  
