#include "partido.h"
#include <cstring>

using namespace std;

partido::partido(){
	nombre = new char [100];
	votos = 0;
}

partido::partido(const partido& par){
	nombre = new char [100];
	nombre = par.nombre;
	votos = par.votos;
}

partido::~partido() {
   delete [] nombre;
}

int partido::GetVotos(){
	return votos;
}

char* partido::GetNombre(){
	return nombre;
}

void partido::SetVotos(int v){
	votos = v;
}

void partido::SetNombre(char* n){
	strcpy(nombre, n);
}

partido& partido::operator=(const partido par){
	nombre = par.nombre;
	votos = par.votos;
}
	



