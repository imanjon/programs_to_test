FILE(GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp *.hxx)

SET(GCC_PROFILE_FLAGS "-pg")
SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage --coverage")
SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O0 -g -Wall -W -pg -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings ${GCC_COVERAGE_COMPILE_FLAGS} ${GCC_PROFILE_FLAGS}" )
SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-O0 -g -Wall -W ${GCC_COVERAGE_COMPILE_FLAGS} ${GCC_PROFILE_FLAGS}")
#SET(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS})
SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS})

INCLUDE_DIRECTORIES(
    ${CUNIT_INCLUDE_DIRS}
    "inc"
)

# Nombre del ejecutable
SET (test_BIN ${PROJECT_NAME}-unittests_cunit)

# Creo el target ejecutable con sus ficheros fuente
ADD_EXECUTABLE(${test_BIN} ${test_SRCS})

TARGET_LINK_LIBRARIES(${test_BIN}
    ${test_LIBS}
    ${CUNIT_LIBRARIES}
    #"gcov"
    ${LIBRARY_OUTPUT_PATH}/libHello.so)
# Añado varios test poniendo el nombre del test y qué binario ejecutar y con qué argumentos
# El test se considerará válido si devuelve >= 0
ADD_TEST(NAME cunit-unittests-1 COMMAND ${test_BIN})
ADD_TEST(NAME cunit-unittests-2 COMMAND ${test_BIN} -p foo)
