#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include "datos.h"
#include "provincia.h"
#include "partido.h"
#include "lista_partidos.h"
#include "estadisticas.h"

using namespace std;

// Imprime por pantalla los datos y estadisticas de las elecciones
void ImprimirDatosPantalla(global* &general, provincia* &vp);
// Imprime por pantalla los datos y estadisticas de las elecciones enfocadas a una provincia especifica
void ImprimirDatosPantallaProvincia(global* &general, provincia* &vp, int pos_provincia);


int main(int argc,char *argv[]){
bool modo_provincia=false;
int pos = 0;
global* dgenerales;
provincia* dprovincias;

	if(argc<2){
		cerr << "Formato de entrada invalido: parlamento fichero_datos [provincia]" << endl;
		exit(1);
	}
			
	if(argc==3){
		modo_provincia=true;
	}
	
	LeerDatos(dgenerales, dprovincias, argv[1]);
	
	if(modo_provincia == true){
		pos = PosicionProvincia(dprovincias, argv[2], dgenerales->num_provincias);
		if(pos == -1){
			cerr << "El nombre de la provincia introducido como argumento no existe en la base de datos" << endl;
			exit(1);
		}
		else
			ImprimirDatosPantallaProvincia(dgenerales, dprovincias, pos);
	}
	else
		ImprimirDatosPantalla(dgenerales, dprovincias);
	
	LiberarDatos(dgenerales, dprovincias);
	
	return 0;
}

void ImprimirDatosPantalla(global* &general, provincia* &vp){
	int total_censo = TotalCenso(vp,general->num_provincias);
	int total_blancos = TotalBlancos(vp,general->num_provincias);
	int total_nulos = TotalNulos(vp,general->num_provincias);
	int votos_funcionales = TotalVotos(vp,general->num_provincias);
	int votos_totales = votos_funcionales + total_blancos + total_nulos;
	int votos_validos = votos_funcionales+total_blancos;
	int abstencion = total_censo-votos_totales;
	int longvector_partidos, total_escanios;
	double aux_double;
	bool imprimido = false;
	char* nombre_fichero = new char [204];
	
	cout << general->titulo << endl << endl;
	cout << "Escaños:\t" << general->escanios_totales << endl;
	cout << "Electores:\t" << total_censo << endl << endl;

	cout << "Votantes:\t" << votos_totales << " ( " << setprecision (3) << Porcentaje(total_censo,votos_totales) << "% de " << total_censo << ")" << endl;
	cout << "\tA canditaturas:\t" << votos_funcionales << " ( " << Porcentaje(votos_totales,votos_funcionales) << "% de " << votos_totales << ")" << endl;
	cout << "\tBlancos:\t" << total_blancos << " ( " << Porcentaje(votos_totales,total_blancos) << "% de " << votos_totales << ")" << endl;
	cout << "\tNulos:\t" << total_nulos << " ( " << Porcentaje(votos_totales,total_nulos) << "% de " << votos_totales << ")" << endl << endl;

	cout << "\tValidos:\t" << votos_funcionales+total_blancos << " ( " << Porcentaje(votos_totales,votos_funcionales+total_blancos) << "% de " << votos_totales << ")" << endl;
	cout << "\tNulos:\t" << total_nulos << " ( " << Porcentaje(votos_totales,total_nulos) << "% de " << votos_totales << ")" << endl << endl;

	cout << "Abstencion:\t" << total_censo-votos_totales << " ( " << Porcentaje(total_censo,total_censo-votos_totales) << "% de " << total_censo << ")" << endl << endl;

	cout << "DISTRIBUCION DE ESCAÑOS POR CIRCUNSCRIPCION" << endl << endl;

	char **vector_partidos=VectorNombresPartidos(vp, general->num_provincias, longvector_partidos);
	int* vector_votos_partidos = new int [longvector_partidos];

	for(int i=0 ; i<longvector_partidos ; i++){
		vector_votos_partidos[i]=0;
		for(int j=0 ; j<general->num_provincias ; j++)
			vector_votos_partidos[i] += vp[j].VotosPartidoLista(vector_partidos[i]);
	}
	OrdenarPorVotos(vector_partidos, vector_votos_partidos, longvector_partidos);

	int** vector_escanios=new int* [general->num_provincias];
	for(int i=0;i<general->num_provincias;i++){
		vector_escanios[i] = LeyDHont(&vp[i], vector_partidos, longvector_partidos, vp[i].GetEscanios());
	}

	cout << "\t";
	
	for(int i=0; i<longvector_partidos ;i++){
		for(int j=0; j<general->num_provincias && !imprimido;j++){
			if(vector_escanios[j][i] != 0){
				cout << "\t";
				for(int k=0; k<strlen(vector_partidos[i])-1 ; k++)
					cout << vector_partidos[i][k];
				imprimido = true;
			}
		}
		imprimido = false;
	}
	cout << endl;

	for(int i=0; i<general->num_provincias ;i++){
		cout << vp[i].GetNombre() << "\t\t";
		for(int j=0; j<longvector_partidos ;j++){
				if(vector_escanios[i][j] != 0)
					cout << vector_escanios[i][j] << "\t";
		}
	cout << endl;
	}
	
	cout << endl << "Total:\t\t";
	for(int i=0; i<longvector_partidos ;i++){
		total_escanios = 0;
		for(int j=0; j<general->num_provincias ;j++){
				total_escanios += vector_escanios[j][i];
		}
	 if(total_escanios!=0)
		cout << total_escanios << "\t";
	}
	
	cout << endl << endl << "DISTRIBUCION PORCENTUAL DE ESCAÑOS" << endl << endl;

	for(int i=0; i<longvector_partidos ;i++){
		total_escanios = 0;
		for(int j=0; j<general->num_provincias ;j++){
				total_escanios += vector_escanios[j][i];
		}
	 if(total_escanios!=0)
		cout << vector_partidos[i] << "\t" << total_escanios << "\t(" << Porcentaje(general->escanios_totales, total_escanios) << " %)" << endl; 
	}

	// Fin impresion por salida estandar

	// Escritura del archivo binario de datos

	strcpy(nombre_fichero,general->titulo);
	strcat(nombre_fichero,".bin");
	ofstream salida(nombre_fichero, ios::binary|ios::out);
	if(salida.fail()){
		cerr << "Error al crear el archivo binario." << endl;
		exit(1);
	}

	salida.write(general->titulo, 200);
	salida.write((const char *) (&general->escanios_totales), sizeof (int));
	salida.write((const char *) (&total_censo), sizeof (int));
	salida.write((const char *) (&votos_totales), sizeof (int));
	salida.write((const char *) (&votos_validos), sizeof (int));
	aux_double = Porcentaje(total_censo,votos_totales);
	salida.write((const char *) (&aux_double), sizeof (double));
	salida.write((const char *) (&total_nulos), sizeof (int));
	aux_double = Porcentaje(votos_totales,total_nulos);
	salida.write((const char *) (&aux_double), sizeof (double));
	salida.write((const char *) (&total_blancos), sizeof (int));
	aux_double = Porcentaje(votos_totales,total_blancos);
	salida.write((const char *) (&aux_double), sizeof (double));
	salida.write((const char *) (&abstencion), sizeof (int));
	aux_double = Porcentaje(total_censo,total_censo-votos_totales);
	salida.write((const char *) (&aux_double), sizeof (double));

	salida.write((const char *) (&longvector_partidos), sizeof (int));
	for(int i=0; i<longvector_partidos ; i++)
		salida.write(vector_partidos[i], 100);

	salida.write((const char *) (&general->num_provincias), sizeof (int));
	for(int i=0; i< general->num_provincias ; i++)
		salida.write(vp[i].GetNombre(),100);

	for(int i=0; i<general->num_provincias ;i++){
		for(int j=0; j<longvector_partidos ;j++){
			salida.write((const char *) (&vector_escanios[i][j]), sizeof (int));
		}
	}

	for(int i=0; i<longvector_partidos ;i++){
		total_escanios = 0;
		for(int j=0; j<general->num_provincias ;j++){
				total_escanios += vector_escanios[j][i];
		}
	if(total_escanios!=0)
		salida.write((const char *) (&total_escanios), sizeof (int));
	}

	salida.close();

	// Liberacion de Memoria
	for(int i=0; i<longvector_partidos; i++)
		delete [] vector_partidos[i];
	delete [] vector_votos_partidos;
	for(int i=0;i<general->num_provincias;i++)
		delete [] vector_escanios[i];
	
}

void ImprimirDatosPantallaProvincia(global* &general, provincia* &vp, int pos_provincia){
	int total_censo = vp[pos_provincia].GetCenso();
	int total_blancos = vp[pos_provincia].GetBlancos();
	int total_nulos = vp[pos_provincia].GetNulos();
	int votos_funcionales = vp[pos_provincia].VotosTotalesLista();
	int votos_totales = votos_funcionales + total_blancos + total_nulos;
	int longvector_partidos, total_escanios=0, votos=0;

	cout << general->titulo << endl << endl;
	cout << "Escaños:\t" << vp[pos_provincia].GetEscanios() << endl;
	cout << "Electores:\t" << total_censo << endl << endl;

	cout << "Votantes:\t" << votos_totales << " ( " << setprecision (3) << Porcentaje(total_censo,votos_totales) << "% de " << total_censo << ")" << endl;
	cout << "\tA canditaturas:\t" << votos_funcionales << " ( " << Porcentaje(votos_totales,votos_funcionales) << "% de " << votos_totales << ")" << endl;
	cout << "\tBlancos:\t" << total_blancos << " ( " << Porcentaje(votos_totales,total_blancos) << "% de " << votos_totales << ")" << endl;
	cout << "\tNulos:\t" << total_nulos << " ( " << Porcentaje(votos_totales,total_nulos) << "% de " << votos_totales << ")" << endl << endl;

	cout << "\tValidos:\t" << votos_funcionales+total_blancos << " ( " << Porcentaje(votos_totales,votos_funcionales+total_blancos) << "% de " << votos_totales << ")" << endl;
	cout << "\tNulos:\t" << total_nulos << " ( " << Porcentaje(votos_totales,total_nulos) << "% de " << votos_totales << ")" << endl << endl;

	cout << "Abstencion:\t" << total_censo-votos_totales << " ( " << Porcentaje(total_censo,total_censo-votos_totales) << "% de " << total_censo << ")" << endl << endl;

	char **vector_partidos=VectorNombresPartidos(vp, general->num_provincias, longvector_partidos);
	int* vector_votos_partidos = new int [longvector_partidos];

	for(int i=0 ; i<longvector_partidos ; i++){
		vector_votos_partidos[i] = vp[pos_provincia].VotosPartidoLista(vector_partidos[i]);
	}
	
	OrdenarPorVotos(vector_partidos, vector_votos_partidos, longvector_partidos);

	int* vector_escanios=LeyDHont(&vp[pos_provincia], vector_partidos, longvector_partidos, vp[pos_provincia].GetEscanios());

	cout << endl << "\t\tVOTOS\tPORC\tESCAÑOS" << endl << endl;

	for(int i=0; i<longvector_partidos ;i++){
		votos = vp[pos_provincia].VotosPartidoLista(vector_partidos[i]);
		if(votos!=0){
			cout << vector_partidos[i] << "\t\t" << votos << "\t" << Porcentaje(votos_funcionales,votos);
			if(vector_escanios[i]!=0){
				total_escanios+=vector_escanios[i];
				cout << "\t" << vector_escanios[i] << endl;
			}
			else
				cout << endl;
		}
	}
	
	cout << endl << "Total:\t\t" << votos_funcionales << "\t\t";
	if(total_escanios!=0)
		cout << total_escanios << endl;
	else
		cout << endl;

	// Liberacion de Memoria
	for(int i=0; i<longvector_partidos; i++)
		delete [] vector_partidos[i];
	delete [] vector_votos_partidos;
	delete [] vector_escanios;
}
