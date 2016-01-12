/*LLamado al juego!! YUJUU*/

#include <iostream>
#include "juego.hpp"
#include <math.h>

using namespace std;

  int main( int argc, char** args){
    srand(time(NULL));
    int dim;
    cout << "Ingresar dimension de tablero (N x N) : ";
    cin >> dim;
    juego J(dim);
    J.jugar(); 
     /* while( T.rellenar_casilla() )
     { T.imprimir_tablero();
      std::cout << std::endl;}*/
    /*tabla = new int* [3];
    for (int i=0 ; i < 3 ; i++)
      tabla[i] = new int[2];
    
    for (int i=0 ; i<3 ; i++){
      for (int j= 0 ; j<2 ; j++)
	tabla[i][j]= i+j+2;
    }
    
    std::cout << "dir tabla: " << tabla << std::endl;
    std::cout << "dir *tabla: " << *tabla << std::endl;
    std::cout << "dir tabla[0]: " << tabla[0] << std::endl;
    std::cout << "dir tabla[1]: " << tabla[1] << std::endl;
    std::cout << "dir *tabla[0]: " << *tabla[0] << std::endl;
    std::cout << "dir *tabla[1]: " << *tabla[1] << std::endl;
    std::cout << "dir **tabla: " << tabla[2][1] << std::endl;
    
    for (int j=0 ; j<2 ; j++){
      for (int i= 0 ; i<3 ; i++)
	std::cout<< "\t" << tabla[i][j];// << "\t";
      std::cout<<std::endl;
    }
    for ( int i=0 ; i <3; i++)
      delete[] tabla[i];
    delete[] tabla;*/
   /* srand(time(NULL));
    for(int i=0; i<3;i++){
    int a = round(rand()%3 + 2);
   std::cout << a << std::endl;}*/
    return 0;
  } 