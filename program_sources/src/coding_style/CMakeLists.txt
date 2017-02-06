#Asegurarse de que el compilador puede encontrar los ficheros de nuestra librería Hello
INCLUDE_DIRECTORIES(../inc)
INCLUDE_DIRECTORIES(../../inc)

INCLUDE_DIRECTORIES(../../libs/libhello/inc)
LINK_DIRECTORIES(libs)

#Añade una librería llamada Hello (libHello.a bajo linux) a partir del fichero fuente hello.cpp
ADD_EXECUTABLE(macro_usage
	macro_usage)
ADD_EXECUTABLE(clang_errors_1
	clang_errors_1)
ADD_EXECUTABLE(clang_errors_2
	clang_errors_2)
ADD_EXECUTABLE(clang_errors_3
	clang_errors_3)
ADD_EXECUTABLE(clang_errors_4
	clang_errors_4)
ADD_EXECUTABLE(clang_errors_5
	clang_errors_5)
ADD_EXECUTABLE(clang_errors_6
	clang_errors_6)

	
	

# SET_TARGET_PROPERTIES(threads_ok
# 	PROPERTIES COMPILE_FLAGS "-g -O1 -fsanitize=thread -fno-omit-frame-pointer -fPIC")
# SET_TARGET_PROPERTIES(threads_error
# 	PROPERTIES COMPILE_FLAGS "-g -O1 -fsanitize=thread -fno-omit-frame-pointer -fPIC")

SET_TARGET_PROPERTIES(macro_usage
	PROPERTIES COMPILE_FLAGS "-g -O1 -Wall -pedantic -fno-omit-frame-pointer -fPIC")
SET_TARGET_PROPERTIES(clang_errors_1
	PROPERTIES COMPILE_FLAGS "-g -O1 -Wall -pedantic -fno-omit-frame-pointer -fPIC")
SET_TARGET_PROPERTIES(clang_errors_2
	PROPERTIES COMPILE_FLAGS "-g -O1 -Wall -pedantic -fno-omit-frame-pointer -fPIC")
SET_TARGET_PROPERTIES(clang_errors_3
	PROPERTIES COMPILE_FLAGS "-g -O1 -Wall -pedantic -fno-omit-frame-pointer -fPIC")
SET_TARGET_PROPERTIES(clang_errors_4
	PROPERTIES COMPILE_FLAGS "-g -O1 -Wall -pedantic -fno-omit-frame-pointer -fPIC")
SET_TARGET_PROPERTIES(clang_errors_5
	PROPERTIES COMPILE_FLAGS "-g -O1 -Wall -pedantic -fno-omit-frame-pointer -fPIC")
SET_TARGET_PROPERTIES(clang_errors_6
	PROPERTIES COMPILE_FLAGS "-g -O1 -Wall -pedantic -fno-omit-frame-pointer -fPIC")
#TARGET_LINK_LIBRARIES(random_alloc_singlethreaded ${LIBRARY_OUTPUT_PATH}/libHello.so pthread tsan)
#TARGET_LINK_LIBRARIES(random_alloc_multithreaded ${LIBRARY_OUTPUT_PATH}/libHello.so pthread)
