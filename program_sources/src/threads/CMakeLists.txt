#Asegurarse de que el compilador puede encontrar los ficheros de nuestra librería Hello
INCLUDE_DIRECTORIES(../inc)
INCLUDE_DIRECTORIES(../../inc)

INCLUDE_DIRECTORIES(../../libs/libhello/inc)
LINK_DIRECTORIES(libs)

#Añade una librería llamada Hello (libHello.a bajo linux) a partir del fichero fuente hello.cpp
ADD_EXECUTABLE(threads_error
	threads_conflicted)
	
ADD_EXECUTABLE(threads_ok
	threads_unconflicted)

ADD_EXECUTABLE(threads_double_mutex_unlock
	threads_double_mutex_unlock)
	
ADD_EXECUTABLE(race_condition
	race_condition)
	
# SET_TARGET_PROPERTIES(threads_ok
# 	PROPERTIES COMPILE_FLAGS "-g -O1 -fsanitize=thread -fno-omit-frame-pointer -fPIC")
# SET_TARGET_PROPERTIES(threads_error
# 	PROPERTIES COMPILE_FLAGS "-g -O1 -fsanitize=thread -fno-omit-frame-pointer -fPIC")

SET(CMAKE_C_FLAGS_DEBUG " -m32 ")
SET(CMAKE_C_FLAGS_RELEASE " -m32 ")

TARGET_LINK_LIBRARIES(threads_ok pthread)
#TARGET_LINK_LIBRARIES(threads_ok ${LIBRARY_OUTPUT_PATH}/libHello.so pthread)
TARGET_LINK_LIBRARIES(threads_error pthread)
#TARGET_LINK_LIBRARIES(threads_error ${LIBRARY_OUTPUT_PATH}/libHello.so pthread)

#TARGET_LINK_LIBRARIES(threads_double_mutex_unlock ${LIBRARY_OUTPUT_PATH}/libHello.so pthread tsan)
TARGET_LINK_LIBRARIES(threads_double_mutex_unlock pthread)

#TARGET_LINK_LIBRARIES(race_condition ${LIBRARY_OUTPUT_PATH}/libHello.so pthread)
TARGET_LINK_LIBRARIES(race_condition pthread)