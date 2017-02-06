#Asegurarse de que el compilador puede encontrar los ficheros de nuestra librería Hello
INCLUDE_DIRECTORIES(../inc)
INCLUDE_DIRECTORIES(../../inc)

INCLUDE_DIRECTORIES(../../libs/libhello/inc)
LINK_DIRECTORIES(libs)

#Añade una librería llamada Hello (libHello.a bajo linux) a partir del fichero fuente hello.cpp
ADD_EXECUTABLE(random_alloc_singlethreaded
	rand_alloc_single_thread)

ADD_EXECUTABLE(random_alloc_multithreaded
	rand_alloc_multi_thread)

ADD_EXECUTABLE(double_free
	double_free)
	
ADD_EXECUTABLE(memory_exhaustion
	memory_exhaustion)
	
# SET_TARGET_PROPERTIES(threads_ok
# 	PROPERTIES COMPILE_FLAGS "-g -O1 -fsanitize=thread -fno-omit-frame-pointer -fPIC")
# SET_TARGET_PROPERTIES(threads_error
# 	PROPERTIES COMPILE_FLAGS "-g -O1 -fsanitize=thread -fno-omit-frame-pointer -fPIC")

SET_TARGET_PROPERTIES(random_alloc_multithreaded
 	PROPERTIES COMPILE_FLAGS "-g -pthread")


#TARGET_LINK_LIBRARIES(random_alloc_singlethreaded ${LIBRARY_OUTPUT_PATH}/libHello.so pthread tsan)
TARGET_LINK_LIBRARIES(random_alloc_multithreaded ${LIBRARY_OUTPUT_PATH}/libHello.so pthread)
