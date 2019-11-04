#include <iostream>
#include <cstring>
#include "datos.h"
#include "estadisticas.h"

using namespace std;

double Porcentaje(int total, int valor){
	double a= (double)total;
	double b=(double)valor;
	return (100*b)/a;
}
	
int TotalBlancos(provincia* vp, int num_provincias){
	int total=0;
	for (int i=0;i<num_provincias;i++){
		total += vp[i].GetBlancos();
	}
	return total;
}

int TotalNulos(provincia* vp, int num_provincias){
	int total=0;
	for (int i=0;i<num_provincias;i++){
		total += vp[i].GetNulos();
	}
	return total;
}

int TotalCenso(provincia* vp, int num_provincias){
	int total=0;
	for (int i=0;i<num_provincias;i++){
		total += vp[i].GetCenso();
	}
	return total;
}

int TotalVotos(provincia* vp, int num_provincias){
	int total=0;
	for (int i=0;i<num_provincias;i++){
		total += vp[i].VotosTotalesLista();
	}
	return total;
}

char **VectorNombresPartidos(provincia *vp, int num_provincias, int &longitud){
	int num_partidos_totales = 0;
	bool ya_esta=false;
	longitud = 1;
	char*** vec_nombres;
	
	// calculo el numero de partidos totales
	for(int i=0;i<num_provincias;i++){
		num_partidos_totales+= vp[i].GetNumPartidos();
	}
	
	// declaro un vector con un espacio suponiendo 
	// que todos los partidos seran distintos
	char **vector = new char *[num_partidos_totales];
	for(int i=0;i<num_partidos_totales;i++){
		vector[i]=new char [100];
	}

	vec_nombres = new char** [num_provincias];
	for(int i =0; i<num_provincias ; i++){
		vec_nombres[i] = vp[i].VectorNombresLista();
	}

	strcpy(vector[0],vec_nombres[0][0]);
	// busco los partidos con nombre desigual y los voy alamcenando, 
	// mientras compruebo que ya no estaba almacenados
	for(int i=0;i<num_provincias;i++){
		for(int j=0;j<vp[i].GetNumPartidos();j++){
			if(i!=0 && j!=0){
				if(!ya_esta){
					if(j==0)
						strcpy(vector[longitud],vec_nombres[i-1][vp[i-1].GetNumPartidos()-1]);
					else
						strcpy(vector[longitud],vec_nombres[i][j-1]);
					longitud++;
				}
				else
					ya_esta=false;
			}
			for(int k=0;k<longitud && !ya_esta;k++){
				if(strcmp(vector[k],vec_nombres[i][j])==0)
					ya_esta=true;
			}
		}
	}

	// copio los datos a un vector reducido ya que ahora si se su longitud verdadera
	char **vector_red = new char *[longitud];
	for(int i=0;i<longitud;i++){
		vector_red[i]=vector[i];
	}
	
	// libero el sobrante del vector que no hemos usado
	for(int i=longitud;i<num_partidos_totales;i++){
		delete [] vector[i];
	}
	
	return vector_red;
}

int VotosPartido(provincia* vp, const char *partido, int num_provincias){
	int total=0;
	
	for(int i=0;i<num_provincias;i++){
				total += vp[i].VotosPartidoLista(partido);
	}
	return total;
}

int* LeyDHont(provincia* p, char** partidos, int longpartidos, int num_escanios){
	int* hont = new int [longpartidos];
	int* v_escanios = new int [longpartidos];
	int pos, aux, divisor;

	// Recopilo los votos para realizar el sistema D'Hont
	for(int i=0; i<longpartidos ; i++)
		hont[i] = p->VotosPartidoLista(partidos[i]);

	// Inicializo a 0 el vector escanios
	for(int i=0; i<longpartidos ; i++)
		v_escanios[i] = 0;

	// Calculo los escaños con el sistema D'Hont
	aux = hont[0];
	pos = 0;
	for(int i=0 ; i<num_escanios ; i++){
		for(int j=0; j<longpartidos ; j++){
			if(aux<=hont[j]){
				aux = hont[j];
				pos = j;
			}
		}
		divisor = 2 + v_escanios[pos];
		hont[pos] = p->VotosPartidoLista(partidos[pos])/divisor;
		v_escanios[pos]++;
		aux = 0;
	}

	return v_escanios;
}

int PosicionProvincia(provincia* vp, char* nombre, int num_provincias){
	int pos = -1;
	bool encontrado = false;
	
	strcat(nombre,"\r");

	for(int i=0; i<num_provincias && !encontrado;i++){
		if(strcmp(vp[i].GetNombre(),nombre)==0){
			pos = i;
			encontrado = true;
		}
	}

	return pos;
}

void OrdenarPorVotos(char** partidos, int* votos, int longpartidos){
	// Metodo de la burbuja
	int aux_int;
	char* aux_char = new char;
	for (int i = 1; i < longpartidos; i++)
	{
     for (int j = longpartidos - 1; j >=i; j--)
     {
        if (votos[j-1] < votos[j])
        {
           aux_int = votos[j-1];
           votos[j-1] = votos[j];
           votos[j] = aux_int;
			  strcpy(aux_char, partidos[j-1]);
			  strcpy(partidos[j-1], partidos[j]);
			  strcpy(partidos[j],aux_char);
        }
     }
  }
}







