FILE(GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp *.hxx)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage --coverage")
SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage --coverage")

#SET(CMAKE_SHARED_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage --coverage")

SET (test_LIBS
    ${GTEST_BOTH_LIBRARIES}
    #${GTEST_LIBRARIES}
    #${GMOCK_LIBRARIES}
    pthread
)

INCLUDE_DIRECTORIES(
        ${GTEST_INCLUDE_DIRS}
        "inc"
)

# Nombre del ejecutable
SET (test_BIN ${PROJECT_NAME}-unittests_gtest)
# Creo el target ejecutable con sus ficheros fuente
ADD_EXECUTABLE(${test_BIN} ${test_SRCS})
TARGET_LINK_LIBRARIES(${test_BIN}
    ${test_LIBS}
    ${LIBRARY_OUTPUT_PATH}/libHello.so)
# Añado varios test poniendo el nombre del test y qué binario ejecutar y con qué argumentos
# El test se considerará válido si devuelve >= 0
ADD_TEST(NAME gtest-unittests-1 COMMAND ${test_BIN})
ADD_TEST(NAME gtest-unittests-2 COMMAND ${test_BIN} -p foo)
