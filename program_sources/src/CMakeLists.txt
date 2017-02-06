#Asegurarse de que el compilador puede encontrar los ficheros de nuestra librería Hello
INCLUDE_DIRECTORIES(../inc)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/libs/libhello/inc)
LINK_DIRECTORIES(libs)

#Añade una librería llamada Hello (libHello.a bajo linux) a partir del fichero fuente hello.cpp
ADD_EXECUTABLE(hello
	hello)

TARGET_LINK_LIBRARIES(hello ${LIBRARY_OUTPUT_PATH}/libHello.so)


ADD_SUBDIRECTORY(threads)
ADD_SUBDIRECTORY(memory_allocation)
ADD_SUBDIRECTORY(illegal_rw)
ADD_SUBDIRECTORY(callgrind)
ADD_SUBDIRECTORY(coding_style)
