#Asegurarse de que el compilador puede encontrar los ficheros de nuestra librería Hello
INCLUDE_DIRECTORIES(../inc)

#Añade una librería llamada Hello (libHello.a bajo linux) a partir del fichero fuente hello.cpp
ADD_LIBRARY(HelloStatic
	STATIC		# STATIC | SHARED | MODULE
	hello)

ADD_LIBRARY(HelloShared
	SHARED
	hello)

# Creo un alias para las librerías
set_target_properties(HelloStatic PROPERTIES OUTPUT_NAME Hello)
set_target_properties(HelloShared PROPERTIES OUTPUT_NAME Hello)

