INCLUDE_DIRECTORIES(${CTEST_INCLUDE_DIRS})

FILE(GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp *.hxx)
SET (test_LIBS
    #    ${CTEST_LIBRARIES}
    #${GTEST_LIBRARIES}
    #${GMOCK_LIBRARIES}
    pthread
    gcov
)

INCLUDE_DIRECTORIES(
    ${CTEST_INCLUDE_DIRS}
    "../inc"
)

# Nombre del ejecutable
SET (test_BIN ${PROJECT_NAME}-unittests_ctest)
# Creo el target ejecutable con sus ficheros fuente
ADD_EXECUTABLE(${test_BIN} ${test_SRCS})
TARGET_LINK_LIBRARIES(${test_BIN}
    ${test_LIBS}
    ${LIBRARY_OUTPUT_PATH}/libHello.so)
# Añado varios test poniendo el nombre del test y qué binario ejecutar y con qué argumentos
# El test se considerará válido si devuelve >= 0
ADD_TEST(NAME unittests-1 COMMAND ${test_BIN})
ADD_TEST(NAME unittests-2 COMMAND ${test_BIN} -p foo)
