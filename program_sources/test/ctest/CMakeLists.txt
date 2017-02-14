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

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O0 -g -Wall -W -pg -Wfatal-errors -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings ${GCC_COVERAGE_COMPILE_FLAGS} ${GCC_PROFILE_FLAGS}" )
SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-O0 -g -Wall -W -Wfatal-errors ${GCC_COVERAGE_COMPILE_FLAGS} ${GCC_PROFILE_FLAGS}")
#SET(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS})
SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS})

# Nombre del ejecutable
SET (test_BIN ${PROJECT_NAME}-unittests_ctest)
# Creo el target ejecutable con sus ficheros fuente
ADD_EXECUTABLE(${test_BIN} ${test_SRCS})
TARGET_LINK_LIBRARIES(${test_BIN}
    ${test_LIBS}
    ${LIBRARY_OUTPUT_PATH}/libHello.so)
# Añado varios test poniendo el nombre del test y qué binario ejecutar y con qué argumentos
# El test se considerará válido si devuelve >= 0
ADD_TEST(NAME ctest-unittests-1 COMMAND ${test_BIN})
ADD_TEST(NAME ctest-unittests-2 COMMAND ${test_BIN} -p foo)
