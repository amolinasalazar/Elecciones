#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include "datos.h"

using namespace std;

void SaltarBlancos(ifstream& entrada){
	while (entrada.peek() <= 32 || entrada.peek() >= 127){
		entrada.ignore();
	}
}

void LeerDatos(global* &general, provincia* &vp, char* fichero){
	char * aux_char = new char [100];
	int aux_int;
	general = new global;

	ifstream entrada(fichero,ios::in); // Abrimos el archivo de datos

	if(!entrada) {
		cerr << "Imposible abrir el archivo: " << fichero << ", compruebe si existe y/o si tiene los permisos adecuados" << endl;
	exit(1);
	}

	general->titulo = new char [200];
	entrada.getline(general->titulo,200);
	entrada >> general->num_provincias;
	entrada >> general->escanios_totales;

	SaltarBlancos(entrada);

	vp = new provincia [general->num_provincias];

	for(int i=0; i<general->num_provincias; i++){
		entrada.getline(aux_char,100);
		vp[i].SetNombre(aux_char);
		entrada >> aux_int;
		vp[i].SetEscanios(aux_int);
		entrada >> aux_int;
		vp[i].SetCenso(aux_int);
		entrada >> aux_int;
		vp[i].SetNumPartidos(aux_int);
		
		SaltarBlancos(entrada);
		
		lista_partidos* lista = new lista_partidos;

		partido* par = new partido;

		
		for (int j=0; j<vp[i].GetNumPartidos() ; j++){
			entrada.getline(aux_char,100);
			(*par).SetNombre(aux_char);
			entrada >> aux_int;
			(*par).SetVotos(aux_int);
			lista->AniadirPartido(par);
			SaltarBlancos(entrada);
		}

		vp[i].EnlazarLista(lista);

		SaltarBlancos(entrada);
		entrada >> aux_int;
		vp[i].SetNulos(aux_int);
		entrada >> aux_int;
		vp[i].SetBlancos(aux_int);

		if(i!=general->num_provincias-1)
			SaltarBlancos(entrada);
		
	}
	delete [] aux_char;
	entrada.close();
}

void LiberarDatos(global* &general, provincia* &vp){

	delete [] vp;
	delete general->titulo;
	delete general; 

}


