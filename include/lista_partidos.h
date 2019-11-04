#ifndef LISTA_PARTIDOS
#define LISTA_PARTIDOS

#include <iostream>
#include "partido.h"

using namespace std;

class lista_partidos{

	private:
		partido* par;
		lista_partidos* sig;
		
	public:

		lista_partidos();

		lista_partidos(const lista_partidos& lpar);

		~lista_partidos();

		// Añade un nodo partido a la lista
		void AniadirPartido(partido* par_nuevo);

		// Devuelve la suma de todos los votos de los diferentes nodos partido
		int VotosTotales();

		// Devuelve el numero de partidos que hay enlazados en la lista
		int NumeroPartidos();

		// Devuelve un vector con los nombres de los nodos partido de la lista
		char** VectorNombres();

		// Devuelve los votos del partido cuyo nombre se ha pasado como argumento
		int VotosPartido(const char* nombre);
};

#endif
