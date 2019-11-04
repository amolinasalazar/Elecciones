#include "lista_partidos.h"
#include "partido.h"
#include <cstring>

using namespace std;

lista_partidos::lista_partidos(){
	par = new partido;
	(*par).SetVotos(0);
	sig = 0;
}

lista_partidos::lista_partidos(const lista_partidos& lpar){
	bool primera_vez = false;
	lista_partidos* aux = new lista_partidos;
	lista_partidos* aux2 = new lista_partidos;
	do{
		if(!primera_vez){
			par = new partido;
			par->SetNombre(lpar.par->GetNombre());
			par->SetVotos(lpar.par->GetVotos());
			sig = 0;
			aux = lpar.sig;
			aux2 = sig;
			primera_vez = true;
		}
		else{
			aux2 = new lista_partidos;
			(aux2->par)->SetNombre((aux->par)->GetNombre());
			(aux2->par)->SetVotos((aux->par)->GetVotos());
			aux2->sig = 0;
			aux = aux->sig;
			aux2 = aux2->sig;
		}
	} while(aux != 0);
}

lista_partidos::~lista_partidos() {
   delete par;
	delete sig;
}

void lista_partidos::AniadirPartido(partido* par_nuevo) {
	// llegar al final de la lista
	lista_partidos* aux = sig;
	lista_partidos* aux2;
	lista_partidos* aux3 = sig;

	if(NumeroPartidos() == 0){
		par->SetNombre(par_nuevo->GetNombre());
		par->SetVotos(par_nuevo->GetVotos());
	}
	else{
		while(aux != 0){
			aux3 = aux;
			aux = aux->sig;

		}
		//cout << NumeroPartidos() << endl;
		//cout << par->GetVotos() << endl;
		aux2 = new lista_partidos;
	//cout << par_nuevo->GetNombre() << endl;
		(aux2->par)->SetNombre(par_nuevo->GetNombre());
		(aux2->par)->SetVotos(par_nuevo->GetVotos());
	//cout << (aux->par)->GetVotos() << endl;
		aux2->sig = 0;
		//aux = aux2
	if(aux3 != 0){
		aux3->sig = aux2;
	}
	else{
		sig = aux2;
	}
	}
}

int lista_partidos::VotosTotales() {
	lista_partidos* aux = sig;
	int votos_t = par->GetVotos();
	//cout << par->GetVotos() << endl;
	//cout << "antes del while" << endl;
	//cout << aux << endl;
	//cout << NumeroPartidos() << endl;
	while(aux != 0){
		if(aux != 0){
			//cout << (aux->par)->GetVotos() << endl;
			votos_t += (aux->par)->GetVotos();
		}
		aux = aux->sig;
	}
	//cout << votos_t << endl;
	return votos_t;
}

int lista_partidos::NumeroPartidos() {
	lista_partidos* aux = sig;
	int contador = 1;
	if(par->GetVotos()==0){
		contador = 0;
	}
	while(aux != 0){
		aux = aux->sig;
		contador++;
	}
	
	return contador;
}

char** lista_partidos::VectorNombres(){
	lista_partidos* aux = sig;
	char **vector = new char *[NumeroPartidos()];
	for(int i=0;i<NumeroPartidos();i++){
		vector[i]=new char [100];
	}

	strcpy(vector[0],par->GetNombre());
	for(int i=1;aux != 0;i++){
		strcpy(vector[i],(aux->par)->GetNombre());
		aux = aux->sig;
	}

	return vector;
}


int lista_partidos::VotosPartido(const char* nombre){
	lista_partidos* aux = sig;
	int votos = 0;
	if(strcmp(nombre,par->GetNombre())==0)
			votos = par->GetVotos();
	while(aux != 0){
		if(strcmp(nombre,(aux->par)->GetNombre())==0)
			votos = (aux->par)->GetVotos();
		aux = aux->sig;
	}

	return votos;
}



