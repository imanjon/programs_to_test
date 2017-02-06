#Asegurarse de que el compilador puede encontrar los ficheros de nuestra librería Hello
INCLUDE_DIRECTORIES(../inc)
INCLUDE_DIRECTORIES(../../inc)

INCLUDE_DIRECTORIES(../../libs/libhello/inc)
LINK_DIRECTORIES(libs)

#Añade una librería llamada Hello (libHello.a bajo linux) a partir del fichero fuente hello.cpp
ADD_EXECUTABLE(callgrind_example
	callgrind_example)

# SET_TARGET_PROPERTIES(threads_ok
# 	PROPERTIES COMPILE_FLAGS "-g -O1 -fsanitize=thread -fno-omit-frame-pointer -fPIC")

SET_TARGET_PROPERTIES(random_alloc_multithreaded
 	PROPERTIES COMPILE_FLAGS "-g")

#TARGET_LINK_LIBRARIES(callgrind_example ${LIBRARY_OUTPUT_PATH}/libHello.so pthread)
