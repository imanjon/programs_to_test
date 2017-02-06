PROJECT(HELLO)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

SET (APPLICATION_NAME "MyHelloApplication")
SET (APPLICATION_CODENAME "${PROJECT_NAME}")
SET (APPLICATION_COPYRIT_YEARS "2016")
SET (APPLICATION_VERSION_MAJOR 0)
SET (APPLICATION_VERSION_MINOR 0)
SET (APPLICATION_VERSION_PATCH 1)
SET (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")

#
# Project Output Paths
#
SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
SET(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/lib")
LIST (APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")

# Establecer la ruta para buscar ficheros cmake que puedan ser necesarios
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/tools/cmake/modules)

# Establecer los tipos de proyectos que voy a construir
IF(NOT CMAKE_BUILD_TYPE_LIST)
        # LAS POSIBLES CONSTRUCCIONES LAS METO AQUI
        LIST(APPEND CMAKE_BUILD_TYPE_LIST Debug Release)

        # Oculto la lista del cmake-gui, porque se muestran en el combo
        MARK_AS_ADVANCED(CMAKE_BUILD_TYPE_LIST)
        SET(CMAKE_BUILD_TYPE_LIST "${CMAKE_BUILD_TYPE_LIST}" CACHE STRING
                "Build types for optimization flags"
                FORCE)
ENDIF()
IF(NOT CMAKE_BUILD_TYPE)
    LIST(GET CMAKE_BUILD_TYPE_LIST 0 CMAKE_BUILD_TYPE_DEFAULT)
    SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE ${CMAKE_BUILD_TYPE_DEFAULT})
ENDIF()
SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_BUILD_TYPE_LIST})
SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Decidir qué tipo de construcción vamos a hacer")

IF(NOT CMAKE_BUILDING_ARCHITECTURE_LIST)
        # LAS POSIBLES CONSTRUCCIONES LAS METO AQUI
        LIST(APPEND CMAKE_BUILDING_ARCHITECTURE_LIST "System" "ARM" "ARM_hf" "MinGw")

        # Oculto la lista del cmake-gui, porque se muestran en el combo
        MARK_AS_ADVANCED(CMAKE_BUILDING_ARCHITECTURE_LIST)
        SET(CMAKE_BUILDING_ARCHITECTURE_LIST "${CMAKE_BUILDING_ARCHITECTURE_LIST}" CACHE STRING
                "Reset the configurations to what we need"
                FORCE)
ENDIF()
IF(NOT BUILDING_ARCHITECTURE)
        LIST(GET CMAKE_BUILDING_ARCHITECTURE_LIST 0 BUILDING_ARCHITECTURE_DEFAULT)
        SET(BUILDING_ARCHITECTURE "System" CACHE STRING "Target architecture")
        SET_PROPERTY(CACHE BUILDING_ARCHITECTURE PROPERTY VALUE ${BUILDING_ARCHITECTURE_DEFAULT})
ENDIF()
SET_PROPERTY(CACHE BUILDING_ARCHITECTURE PROPERTY STRINGS ${CMAKE_BUILDING_ARCHITECTURE_LIST})
SET_PROPERTY(CACHE BUILDING_ARCHITECTURE PROPERTY HELPSTRING "Decidir qué tipo de construcción vamos a hacer")

if (BUILDING_ARCHITECTURE STREQUAL "ARM")
        SET(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/tools/cmake/toolchain/Toolchain_ARM.cmake)
        include(${CMAKE_TOOLCHAIN_FILE})
elseif (BUILDING_ARCHITECTURE STREQUAL "ARM_hf")
        SET(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/tools/cmake/toolchain/Toolchain_ARM_hf.cmake)
        include(${CMAKE_TOOLCHAIN_FILE})
elseif (BUILDING_ARCHITECTURE STREQUAL "MinGw")
        SET(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/tools/cmake/toolchain/Toolchain-cross-mingw32-linux.cmake)
        include(${CMAKE_TOOLCHAIN_FILE})
else()
    SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall -W -Wno-return-type ")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -pipe -march=core2 ")
    SET(CMAKE_C_FLAGS_DEBUG "-O0 -g3 -Wall -W -Wno-return-type ")
    SET(CMAKE_C_FLAGS_RELEASE "-O2 -pipe -march=core2 ")
endif()

# Mark as advanced hides a variable. If preset with clear, it will be shown
mark_as_advanced(CLEAR CMAKE_VERBOSE_MAKEFILE)

# Se puede establecer que los warnings sean considerados errores
#SET(BUILDING_WARN_AS_ERROR OFF CACHE BOOL "Treat warnings as errors" )
OPTION(BUILDING_WARN_AS_ERROR  "Treat warnings as errors"                                  OFF)
if (BUILDING_WARN_AS_ERROR)
    SET(MY_COMPILATION_FLAGS "${MY_COMPILATION_FLAGS} -Werror")
endif()

# Pongo unos flags por defecto para cada tipo de compilación
# y les añado mis flags de compilación dependiendo de las opciones que haya 
# seleccionado el usuario
SET(CMAKE_CXX_FLAGS_DEBUG "${MY_COMPILATION_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
SET(CMAKE_CXX_FLAGS_RELEASE "${MY_COMPILATION_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
SET(CMAKE_C_FLAGS_DEBUG "${MY_COMPILATION_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
SET(CMAKE_C_FLAGS_RELEASE "${MY_COMPILATION_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")

# Busca un paquete
FIND_PACKAGE(PkgConfig) #Enable PKG-CONFIG suport

#
# GTest for TESTING
#
OPTION(TESTING_USE_GTEST    "Set to ON to build testing executables"                    OFF)
IF(TESTING_USE_GTEST)
    FIND_PACKAGE (GTest)    #optional package, not REQUIRED
    if (GTEST_FOUND)
        message(WARNING "Tests are enabled")
        
        # Debug flags
        SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wfatal-errors")
    else(GTEST_FOUND)
        message(WARNING "GTEST is not installed. An alternative version for GTEST will be used instead")

	# We need thread support
	find_package(Threads REQUIRED)

	# Enable ExternalProject CMake module
	include(ExternalProject)

	# Download and install GoogleTest;:
	ExternalProject_Add(
	    gtest
	    URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
	    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
            # Paso como argumentos de CMAKE el compilador, los flags y hago que compila las librerías shared
            # Válido para todas las arquitecturas
            CMAKE_ARGS -DCMAKE_C_COMPILER='${CMAKE_C_COMPILER}' -DCMAKE_C_FLAGS='${CMAKE_C_FLAGS}' -DCMAKE_CXX_COMPILER='${CMAKE_CXX_COMPILER}' -DCMAKE_CXX_FLAGS='${CMAKE_CXX_FLAGS}'-DBUILD_SHARED_LIBS=ON
	    # Disable install step
	    INSTALL_COMMAND ""
	)

	# Create a libgtest target to be used as a dependency by test programs
	add_library(libgtest IMPORTED STATIC GLOBAL)
	add_dependencies(libgtest gtest)

	# Set gmock properties
	ExternalProject_Get_Property(gtest source_dir binary_dir)
	set_target_properties(libgtest PROPERTIES
	    "IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
	    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
            #"INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
	)
	# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
        include_directories("${source_dir}/include")

	# Download and install GoogleMock
	ExternalProject_Add(
	    gmock
	    URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
	    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gmock
            # Paso como argumentos de CMAKE el compilador, los flags y hago que compila las librerías shared
            # Válido para todas las arquitecturas
            CMAKE_ARGS -DCMAKE_C_COMPILER='${CMAKE_C_COMPILER}' -DCMAKE_C_FLAGS='${CMAKE_C_FLAGS}' -DCMAKE_CXX_COMPILER='${CMAKE_CXX_COMPILER}' -DCMAKE_CXX_FLAGS='${CMAKE_CXX_FLAGS}'-DBUILD_SHARED_LIBS=ON
	    # Disable install step
	    INSTALL_COMMAND ""
	)

	# Create a libgmock target to be used as a dependency by test programs
	add_library(libgmock IMPORTED STATIC GLOBAL)
	add_dependencies(libgmock gmock)

	# Set gmock properties
	ExternalProject_Get_Property(gmock source_dir binary_dir)
	set_target_properties(libgmock PROPERTIES
	    "IMPORTED_LOCATION" "${binary_dir}/libgmock.a"
	    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
            #"INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
	)
	# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
        include_directories("${source_dir}/include")

        SET(GMOCK_LIBRARIES  libgmock)
        SET(GTEST_LIBRARIES  libgtest)
        SET(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
    endif(GTEST_FOUND)
    enable_testing ()
ENDIF()

# Documentation Generation
SET(DOXY_DOCUMENTATION_PATH ./doc CACHE  FILEPATH "Path where documentation will be loaded")
FILE(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${DOXY_DOCUMENTATION_PATH})
OPTION(DOXY_INSTALL          "Set to OFF to skip build/install Documentation"            ON)
OPTION(DOXY_DOT             "Set to ON to perform diagram generation with graphviz"     OFF)
OPTION(DOXY_LATEX           "Set to ON to build latex documentation"                    OFF)
OPTION(DOXY_CHM             "Set to ON to build CHM Windows documentation"              OFF)

# Hace un include y llama a la macro que hay definida en él
include(UseCustomIncludes)
ADD_CUSTOM_CMAKE_INCLUDE()

FIND_PACKAGE(FooBar REQUIRED)
IF (FOOBAR_FOUND)
    MESSAGE("Vale, has encontrado FOOBAR")
    include_directories(${LibFOOBAR_INCLUDE_DIRS})
    SET(LIBS ${LIBS} ${LibFOOBAR_LIBRARIES})
ELSE()
    MESSAGE("FOOBAR no encontrado")
ENDIF()

PKG_CHECK_MODULES(FOO  foo<=1.0.0)
IF (FOO_FOUND)
    SET(hdrs ${hdrs} foo_file.h)
    SET(srcs ${srcs} foo_file.cpp)
    INCLUDE_DIRECTORIES(${FOO_INCLUDE_DIRS})
    SET(libraries ${libraries} ${FOO_LIBRARIES})
ELSE()
    message("No encuentra la libreria FOO en una versión mínima")
ENDIF()

PKG_CHECK_MODULES(ZLIB  zlib>=1.0.0 REQUIRED)




	# Enable ExternalProject CMake module
	include(ExternalProject)

	# Download and install GoogleMock
	ExternalProject_Add(
	    thirdparty_foo
            URL ${CMAKE_SOURCE_DIR}/thirdparty/libfoo.tar.gz
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/thirdparty_libfoo
            # Paso como argumentos de CMAKE el compilador, los flags y hago que compila las librerías shared
            # Válido para todas las arquitecturas
            CMAKE_ARGS -DCMAKE_C_COMPILER='${CMAKE_C_COMPILER}' -DCMAKE_C_FLAGS='${CMAKE_C_FLAGS}' -DCMAKE_CXX_COMPILER='${CMAKE_CXX_COMPILER}' -DCMAKE_CXX_FLAGS='${CMAKE_CXX_FLAGS}'-DBUILD_SHARED_LIBS=ON -DCMAKE_MODULE_PATH='${CMAKE_MODULE_PATH}'
	    # Disable install step
	    INSTALL_COMMAND ""
	)

	# Create a libgmock target to be used as a dependency by test programs
	add_library(libfoo IMPORTED STATIC GLOBAL)
	add_dependencies(libfoo thirdparty_hello)

	# Set gmock properties
	ExternalProject_Get_Property(thirdparty_foo source_dir binary_dir)
	set_target_properties(thirdparty_foo PROPERTIES
	    "IMPORTED_LOCATION" "${binary_dir}/libfoo.a"
	    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
            #"INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
	)
	# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
        include_directories("${source_dir}/inc")




# Directorios que van a ser compilados
#link_directories(libs thirdparty/*)
ADD_SUBDIRECTORY(libs)
ADD_SUBDIRECTORY(src)
IF (TESTING_USE_GTEST)
    ADD_SUBDIRECTORY(test)
ENDIF(TESTING_USE_GTEST)

# Documentation installation 
IF (DOXY_INSTALL)
    #INCLUDE("${PROJECT_SOURCE_DIR}/generateDoc.cmake" )
    INCLUDE("generateDoc" )
    GENERATE_DOCUMENTATION(${PROJECT_SOURCE_DIR}/share/lib${PROJECT_NAME}.dox.in)
ENDIF()

# Install the package
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/share/conf DESTINATION ${CMAKE_INSTALL_PREFIX}/share/conf/)
FILE(GLOB header_files "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/libs/libhello/inc/*.h")
INSTALL(FILES ${header_files} DESTINATION include)

# Uninstall everything
CONFIGURE_FILE( "${CMAKE_MODULE_PATH}/uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" )

# ESTABLECER VARIABLES DE ENTORNO
cmake_minimum_required(VERSION 2.6)
SET(ENV{MYVAR} "SOME VALUE" PARENT_SCOPE)
message(STATUS "the value of MYVAR: " $ENV{MYVAR})
execute_process(COMMAND "/usr/bin/env" OUTPUT_VARIABLE myEnvOut)
string(REGEX MATCH "MYVAR=[^\n]*" MyVarEnv "${myEnvOut}")
message(STATUS "Found MYVAR: ${MyVarEnv}")

