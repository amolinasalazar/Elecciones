#ifndef ESTADISTICAS
#define ESTADISTICAS

// Realiza un porcentaje mediante una regla de tres
double Porcentaje(int total, int valor);

// Devuelve el numero de votos en blanco totales de las elecciones
int TotalBlancos(provincia* vp, int num_provincias);

// Devuelve el numero de votos nulos totales de las elecciones
int TotalNulos(provincia* vp, int num_provincias);

// Devuelve el censo total de las provincias donde se han producido las elecciones
int TotalCenso(provincia* vp, int num_provincias);

// Devuelve el numero de votos totales de las elecciones
int TotalVotos(provincia* vp, int num_provincias);

// Devuelve un puntero a un vector de punteros de char 
// con cada uno de los nombres de los diferentes partidos
char **VectorNombresPartidos(provincia *p, int num_provincias, int &longitud);

// Devuelve los votos totales del partido pasado como argumento
int VotosPartido(provincia* p,const char *partido, int num_provincias);

// Hace un reparto de escaños entre los partidos de una provincia segun la ley D'Hont,
// devuelve un vector con los escaños resultado ordenados segun el vector de nombres de 
// provincias pasado como argumento a esta funcion
int* LeyDHont(provincia* p, char** partidos, int longpartidos, int num_escanios);

// Devuelve la posicion de la provincia en el vector de provincias
int PosicionProvincia(provincia* vp, char* nombre, int num_provincias);

// Devuelve el vector de partidos ordenado por numero de votos junto 
// con el vector de votos, de mayor a menor
void OrdenarPorVotos(char** partidos, int* votos, int longpartidos);

#endif

