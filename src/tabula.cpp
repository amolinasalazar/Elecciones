#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include "provincia.h"
#include "partido.h"
#include "lista_partidos.h"
#include "estadisticas.h"

using namespace std;

// Lee el archivo binario de entrada y crea un fichero de extension .html, 
// el cual contiene los datos del fichero de entrada bien estructurados
void CreaFicheroHtml(char* fichero_entrada);

int main(int argc,char *argv[]){

	if(argc!=2){
		cerr << "Formato de entrada invalido: tabula fichero.bin" << endl;
		exit(1);
	}
	
	CreaFicheroHtml(argv[1]);
	
	return 0;
}

void CreaFicheroHtml(char* fichero_entrada){
	char* titulo=new char [200], *nombre_fichero =new char [205];
	int escanios_totales, total_censo, votos_totales, votos_funcionales, votos_validos, total_nulos, total_blancos, abstencion, longvector_partidos, num_provincias, columnas=0, total_escanios=0, impresiones=0;
	double porc_participacion, porc_blancos, porc_nulos, porc_abstencion;
	bool imprimido = false;

	// Abrimos fichero de datos binario y lo leemos

	ifstream entrada(fichero_entrada, ios::binary|ios::in);
	if(entrada.fail()){
		cerr << "Error al leer el archivo binario." << endl;
		exit(1);
	}

	entrada.read(titulo, 200);
	entrada.read((char *) (&escanios_totales), sizeof (int));
	entrada.read((char *) (&total_censo), sizeof (int));
	entrada.read((char *) (&votos_totales), sizeof (int));
	entrada.read((char *) (&votos_validos), sizeof (int));
	entrada.read((char *) (&porc_participacion), sizeof (double));
	entrada.read((char *) (&total_nulos), sizeof (int));
	entrada.read((char *) (&porc_nulos), sizeof (double));
	entrada.read((char *) (&total_blancos), sizeof (int));
	entrada.read((char *) (&porc_blancos), sizeof (double));
	entrada.read((char *) (&abstencion), sizeof (int));
	entrada.read((char *) (&porc_abstencion), sizeof (double));

	entrada.read((char *) (&longvector_partidos), sizeof (int));
	char** vector_partidos = new char* [longvector_partidos];
	for(int i=0; i<longvector_partidos ; i++){
		vector_partidos[i] = new char [100];
		entrada.read(vector_partidos[i],100);
	}

	entrada.read((char *) (&num_provincias), sizeof (int));
	char** vector_provincias = new char* [num_provincias];
	for(int i=0; i<num_provincias ; i++){
		vector_provincias[i] = new char [100];
		entrada.read(vector_provincias[i],100);
	}

	int** vector_escanios = new int* [num_provincias];
	for(int i=0; i<num_provincias ; i++)
		vector_escanios[i] = new int [longvector_partidos];

	for(int i=0; i<num_provincias ;i++){
		for(int j=0; j<longvector_partidos ;j++){
			entrada.read((char *) (&vector_escanios[i][j]), sizeof (int));
		}
	}

	int* vector_escanios_totales = new int [longvector_partidos];
	for(int i=0; i<longvector_partidos;i++)
		entrada.read((char *) (&vector_escanios_totales[i]),sizeof (int));

	entrada.close();

	// Creamos el fichero HTML y escribimos su contenido

	strcpy(nombre_fichero,titulo);
	strcat(nombre_fichero,".html");
	ofstream salida(nombre_fichero, ios::out|ios::trunc);

	salida << "<HTML>" << endl;
	salida << "<HEAD>" << endl;
	salida << "<TITLE>" << endl;
	salida << titulo << endl;
	salida << "</TITLE>" << endl;
	salida << "</HTML>" << endl;
	salida << "</HEAD>" << endl;
	salida << "<BODY>" << endl;
	salida << "<H1>" << endl;
	salida << titulo << endl;
	salida << "</H1>" << endl;

	salida << "<P>" << endl;
	salida << "Escaños: <b>" << escanios_totales << "</b>";
	salida << "<BR>";
	salida << "Electores: <b>" << total_censo << "</b>";
	salida << "<BR>" << "<BR>";
	salida << "Votantes: <b>" << votos_totales << "</b> ( " << setprecision (3) << porc_participacion << "% de " << total_censo << ")<BR><BR></P>";

	salida << "<p style='text-indent: 1em'>A canditaturas: " << votos_totales-total_blancos << " ( " << Porcentaje(votos_totales,votos_totales-total_blancos) << "% de " << votos_totales << ")</p>";
	salida << "<p style='text-indent: 1em'>Blancos: " << total_blancos << " ( " << porc_blancos << "% de " << votos_totales << ")</p>";
	salida << "<p style='text-indent: 1em'>Nulos: " << total_nulos << " ( " << porc_nulos << "% de " << votos_totales << ")<BR><BR></p>";

	salida << "<p style='text-indent: 1em'>Validos: " << votos_validos << " ( " << Porcentaje(votos_totales, votos_validos) << "% de " << votos_totales << ")</p>";
	salida << "<p style='text-indent: 1em'>Nulos: " << total_nulos << " ( " << porc_nulos << "% de " << votos_totales << ")<BR><BR></p>";

	salida << "<P>Abstencion: <b>" << abstencion << "</b> ( " << porc_abstencion << "% de " << total_censo << ")<BR><BR></P>" ;

	salida << "<P><b>DISTRIBUCION DE ESCAÑOS POR CIRCUNSCRIPCION</b></P><BR>";

	salida << "<BODY><CENTER><TABLE BORDER=1>";

	for(int i=0; i<longvector_partidos ;i++){
		for(int j=0; j<num_provincias && !imprimido;j++){
			if(vector_escanios[j][i] != 0){
				columnas++;
				imprimido=true;
			}
		}
		imprimido = false;
	}

	salida << "<TR>";
	salida << "<TH colspan=" << columnas+1 << ">" << titulo << "</TR>";
	salida << "</TR>";

	salida << "<TR><TD>&nbsp</TD>";
	for(int i=0; i<longvector_partidos ;i++){
		for(int j=0; j<num_provincias && !imprimido;j++){
			if(vector_escanios[j][i] != 0){
				salida << "<TD>" << vector_partidos[i] << "</TD>";
				imprimido = true;
			} 
		}
		imprimido = false;
	}
	salida << "</TR><TR>";

	for(int i=0; i<num_provincias ;i++){
		salida << "<TD>" << vector_provincias[i] << "</TD>";
		for(int j=0; j<longvector_partidos ;j++){
			if(vector_escanios[i][j] != 0){
				salida << "<TD>" << vector_escanios[i][j] << "</TD>";
				impresiones++;
			}
		}
		if(impresiones < columnas){
			for(int j=impresiones;j<columnas;j++){
				salida << "<TD>&nbsp</TD>";
			}
		}
		impresiones = 0;
		salida << "</TR><TR>";
	}

	salida << "<TD><b>Total</b></TD>";
	for(int i=0; i<longvector_partidos ;i++){
		total_escanios = 0;
		for(int j=0; j<num_provincias ;j++){
				total_escanios += vector_escanios[j][i];
		}
	if(total_escanios!=0)
		salida << "<TD><b>" << total_escanios << "</b></TD>";
	}
	
	salida << "</TR></TABLE><BR><BR><BR></CENTER><b>" << "DISTRIBUCION PORCENTUAL DE ESCAÑOS" << "</b><BR><BR><BR>";

	salida << "<CENTER><TABLE BORDER=1>";

	salida << "<TR>" << "<TH colspan=3>" << titulo << "</TR>";
	salida << "<TR><TD>&nbsp</TD><TD><b>Escaños</b></TD><TD><b>Porc.</b></TD>";

	for(int i=0; i<longvector_partidos ;i++){
	if(vector_escanios_totales[i]!=0)
		salida << "<TR><TD>" << vector_partidos[i] << "</TD><TD>" << vector_escanios_totales[i] << "</TD><TD>" << Porcentaje(escanios_totales, vector_escanios_totales[i]) << " %" << "</TD></TR>";
	}

	salida << "</TABLE></BODY></HTML>";

	salida.close();

	// Liberacion de Memoria
	for(int i=0; i<longvector_partidos; i++)
		delete [] vector_partidos[i];
	delete [] vector_provincias;
	delete [] vector_escanios_totales;
	for(int i=0;i<num_provincias;i++)
		delete [] vector_escanios[i];
	
}