#ifndef PROVINCIA
#define PROVINCIA

#include <iostream>
#include "lista_partidos.h"

using namespace std;

class provincia{

	private:
		char* nombre;
		int escanios, censo, num_partidos, nulos, blancos;
		lista_partidos* lpar;
		
	public:

		provincia();

		provincia(const provincia& p);

		~provincia();

		// Asigna el puntero lpar a una lista de partidos
		void EnlazarLista(lista_partidos* lista);

		// Asigna el nombre de la provincia al valor del argumento
		void SetNombre(char * n);

		// Asigna los escaños de la provincia al valor del argumento
		void SetEscanios(int e);

		// Asigna el censo de la provincia al valor del argumento
		void SetCenso(int c);

		// Asigna el numero de partidos que hay por provincia al valor del argumento
		void SetNumPartidos(int np);

		// Asigna los votos nulos recogidos en la provincia al valor del argumento
		void SetNulos(int n);

		// Asigna los votos blancos recogidos en la provincia al valor del argumento
		void SetBlancos(int b);

		// Devuelve el nombre de la provincia
		char* GetNombre();

		// Devuelve el numero de escaños de la provincia
		int GetEscanios();

		// Devuelve el censo de la provincia
		int GetCenso();

		// Devuelve el numero de partidos de la provincia
		int GetNumPartidos();

		// Devuelve los votos nulos recogidos de la provincia
		int GetNulos();

		// Devuelve los votos en blanco recogidos de la provincia
		int GetBlancos();

		// Llama a la funcion VotosTotales de la clase lista_partidos
		int VotosTotalesLista();

		// Llama a la funcion VectorNombres de la clase lista_partidos
		char** VectorNombresLista();

		// Llama a la funcion VotosPartido de la clase lista_partidos
		int VotosPartidoLista(const char* nombre);
};

#endif
