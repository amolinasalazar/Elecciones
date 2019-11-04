#include "provincia.h"
#include "lista_partidos.h"
#include <cstring>

using namespace std;

provincia::provincia(){
	nombre = new char [100];
	
	escanios = 0;
	censo = 0;
	num_partidos = 0;
	nulos = 0;
	blancos = 0;
	
	lpar = 0;
}

provincia::provincia(const provincia& p){
	nombre = new char [100];
	nombre = p.nombre;
	
	escanios = p.escanios;
	censo = p.censo;
	num_partidos = p.num_partidos;
	nulos = p.nulos;
	blancos = p.blancos;
	
	lpar = p.lpar;
}

provincia::~provincia() {
	delete [] nombre;
	delete lpar;
}

void provincia::EnlazarLista(lista_partidos* lista){
	lpar = lista;
}

void provincia::SetNombre(char * n){
	strcpy(nombre,n);
}

void provincia::SetEscanios(int e){
	escanios = e;
}

void provincia::SetCenso(int c){
	censo = c;
}

void provincia::SetNumPartidos(int np){
	num_partidos = np;
}

void provincia::SetNulos(int n){
	nulos = n;
}

void provincia::SetBlancos(int b){
	blancos = b;
}

char* provincia::GetNombre(){
	return nombre;
}

int provincia::GetEscanios(){
	return escanios;
}

int provincia::GetCenso(){
	return censo;
}

int provincia::GetNumPartidos(){
	return num_partidos;
}

int provincia::GetNulos(){
	return nulos;
}

int provincia::GetBlancos(){
	return blancos;
}

int provincia::VotosTotalesLista(){
	return (*lpar).VotosTotales();
}

char** provincia::VectorNombresLista(){
	return (*lpar).VectorNombres();
}

int provincia::VotosPartidoLista(const char* nombre){
	return (*lpar).VotosPartido(nombre);
}