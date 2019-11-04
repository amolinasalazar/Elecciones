BIN	= bin
INCLUDE = include
LIB     = lib
OBJ     = obj
SRC     = src

all: parlamento tabula

# Creacion del ejecutable
parlamento: parlamento.o libelecciones.a
	@echo
	@echo Creando y enlazando el ejecutable parlamento...
	g++ -g -o $(BIN)/parlamento $(OBJ)/parlamento.o -L$(LIB) -lelecciones 
	
tabula: tabula.o libelecciones.a
	@echo
	@echo Creando y enlazando el ejecutable tabula...
	g++ -g -o $(BIN)/tabula $(OBJ)/tabula.o -L$(LIB) -lelecciones 
	
# Creacion de la biblioteca
libelecciones.a: datos.o estadisticas.o provincia.o partido.o lista_partidos.o
	@echo
	@echo Creando la biblioteca libelecciones.a...
	ar rvs $(LIB)/libelecciones.a $(OBJ)/datos.o $(OBJ)/estadisticas.o $(OBJ)/provincia.o $(OBJ)/partido.o $(OBJ)/lista_partidos.o  
	
# Creacion de los archivos objeto
datos.o: $(SRC)/datos.cpp
	@echo
	@echo Creando datos.o...
	g++ -g -c -I$(INCLUDE) -o $(OBJ)/datos.o -L$(LIB) $(SRC)/datos.cpp
	
provincia.o: $(SRC)/provincia.cpp
	@echo
	@echo Creando provincia.o...
	g++ -g -c -I$(INCLUDE) -o $(OBJ)/provincia.o -L$(LIB) $(SRC)/provincia.cpp
	
partido.o: $(SRC)/partido.cpp
	@echo
	@echo Creando partido.o...
	g++ -g -c -I$(INCLUDE) -o $(OBJ)/partido.o -L$(LIB) $(SRC)/partido.cpp
	
lista_partidos.o: $(SRC)/lista_partidos.cpp
	@echo
	@echo Creando lista_partidos.o...
	g++ -g -c -I$(INCLUDE) -o $(OBJ)/lista_partidos.o -L$(LIB) $(SRC)/lista_partidos.cpp

estadisticas.o: $(SRC)/estadisticas.cpp
	@echo
	@echo Creando estadisticas.o...
	g++ -g -c -I$(INCLUDE) -o $(OBJ)/estadisticas.o -L$(LIB) $(SRC)/estadisticas.cpp

parlamento.o: $(SRC)/parlamento.cpp
	@echo
	@echo Creando parlamento.o...
	g++ -g -c -I$(INCLUDE) -o $(OBJ)/parlamento.o -L$(LIB) $(SRC)/parlamento.cpp
	
tabula.o: $(SRC)/tabula.cpp
	@echo
	@echo Creando tabula.o...
	g++ -g -c -I$(INCLUDE) -o $(OBJ)/tabula.o -L$(LIB) $(SRC)/tabula.cpp
	

# Limpieza de directorios
clean :
	-rm $(OBJ)/* $(LIB)/*
