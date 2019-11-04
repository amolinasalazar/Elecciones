#ifndef DATOS
#define DATOS

#include "provincia.h"

// Estructura de datos
// Almacena los tres primeros datos del fichero de entrada
struct global{
	char* titulo;
	int num_provincias, escanios_totales;
};

// Salta los retornos de carro que encuentra en el fichero de entrada
void SaltarBlancos(ifstream& entrada);

// Lee y almacena los datos del fichero de entrada
void LeerDatos(global* &general, provincia* &vp, char* fichero);

// Libera la memoria dinamica de las estructuras de datos
void LiberarDatos(global* &general, provincia* &vp);

#endif
