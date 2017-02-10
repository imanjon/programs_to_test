FILE(GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp *.hxx)

IF (OPTION_PROFILING_FOR_TESTS) 
    SET(GCC_PROFILING_ENABLED ON)
    SET(GCC_PROFILE_FLAGS "-pg")
ENDIF(OPTION_PROFILING_FOR_TESTS)

IF (OPTION_COVERAGE_FOR_TESTS)
    SET(GCC_COVERAGE ON)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage --coverage")
    SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")
ENDIF(OPTION_COVERAGE_FOR_TESTS)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O0 -g -Wall -W -pg -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings ${GCC_COVERAGE_COMPILE_FLAGS} ${GCC_PROFILE_FLAGS}" )
SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-O0 -g -Wall -W ${GCC_COVERAGE_COMPILE_FLAGS} ${GCC_PROFILE_FLAGS}")
#SET(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS})
SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS})

INCLUDE_DIRECTORIES(
    # CUnit header directory
    ${CUNIT_INCLUDE_DIRS}
    
    # Project's main header directory
    ${CMAKE_SOURCE_DIR}/inc

    # Example library header directory, add as many as your project has
    #${CMAKE_SOURCE_DIR}/inc

    # Local test headers
    "inc"
)

# Nombre del ejecutable
SET (test_BIN ${PROJECT_NAME}-unittests_cunit)

# Creo el target ejecutable con sus ficheros fuente
ADD_EXECUTABLE(${test_BIN} ${test_SRCS})

TARGET_LINK_LIBRARIES(${test_BIN}
    ${test_LIBS}
    ${CUNIT_LIBRARIES}
    ${LIBRARY_OUTPUT_PATH}/libHello.so)
# Añado varios test poniendo el nombre del test y qué binario ejecutar y con qué argumentos
# El test se considerará válido si devuelve >= 0
ADD_TEST(NAME cunit-unittests-1 COMMAND ${test_BIN})
ADD_TEST(NAME cunit-unittests-2 COMMAND ${test_BIN} -p foo)

# Execute some commands to get coverage information after build
IF(GCC_COVERAGE_ENABLED)
    ADD_CUSTOM_COMMAND(
        TARGET ${test_BIN}
        POST_BUILD
        COMMAND ${test_BIN} 1>> /dev/null
        COMMAND ${CMAKE_COMMAND} -E echo "Generating code coverage reports. This may take some time"
        COMMAND lcov --base-directory . --directory . -c -o ${test_BIN}_test.info
        COMMAND ${CMAKE_COMMAND} -E echo "Generating HTML files"
        COMMAND genhtml -o ${CMAKE_BINARY_DIR}/cunit_test_coverage -t \"${test_BIN} test coverage\" --num-spaces 4 ${test_BIN}_test.info
        WORKING_DIRECTORY "."
        COMMENT "Code coverage reports"
        #VERBATIM
        )
ENDIF(GCC_COVERAGE_ENABLED)

# Execute some commands to get profiling information after build
IF (GCC_PROFILING_ENABLED)
    ADD_CUSTOM_COMMAND(
        TARGET ${test_BIN}
        POST_BUILD
        COMMAND ${test_BIN} 1>> /dev/null
        COMMAND ${CMAKE_COMMAND} -E echo "Generating profiling reports"
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/cunit_test_profiling
        COMMAND gprof -a ${CMAKE_BINARY_DIR}/bin/${test_BIN} ${CMAKE_CURRENT_BINARY_DIR}/gmon.out > ${CMAKE_BINARY_DIR}/cunit_test_profiling/analysis.txt
        WORKING_DIRECTORY "."
        COMMENT "Profiling tools to generate reports"
        )
ENDIF(GCC_PROFILING_ENABLED)
