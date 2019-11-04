#ifndef PARTIDO
#define PARTIDO

#include <iostream>

using namespace std;

class partido{

	private:
		char* nombre;
		int votos;
		
	public:

		partido();

		partido(const partido& par);

		~partido();

		// Devuelve los votos del partido
		int GetVotos();
		
		//Devuelve el nombre del partido
		char* GetNombre();
		
		// Asigna los votos del partido al valor del argumento
		void SetVotos(int v);
		
		// Asigna el nombre del partido al valor del argumento
		void SetNombre(char* n);
		
		// Sobrecarga el operador = para usarlo con variables partido
		partido& operator=(const partido par);
};

#endif
