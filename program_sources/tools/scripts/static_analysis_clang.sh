#!/bin/sh

export CCC_CC=clang
export CCC_CXX=clang++

OUTPUT_DIR=scan-build-output/

# Para que funcione hay que añadir unas opciones al cmake:
# -DCMAKE_EXPORT_COMPILE_COMMANDS=ON: Saca un fichero JSON llamado compile_commands.json con los comandos usados en la compilación
# -DCMAKE_C_COMPILER=/usr/share/clang/scan-build-3.8/libexec/ccc-analyzer: Indicar el compilador-analizador para C. Puede coger el de la ruta equivocada y no sacar ningún informe.
# -DCMAKE_CXX_COMPILER=/usr/share/clang/scan-build-3.8/libexec/c++-analyzer: Indicar el compilador-analizador para C++. Puede coger el de la ruta equivocada y no sacar ningún informe.
scan-build cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_COMPILER=/usr/share/clang/scan-build-3.8/libexec/c++-analyzer -DCMAKE_C_COMPILER=/usr/share/clang/scan-build-3.8/libexec/ccc-analyzer -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE ../program_sources/
 
# Opcionalmente se pueden añadir los compiladores clang y clang++, pero si ya se han definido antes no son necesarios
# --use-cc=clang
# --use-c++=clang++
# Opciones sí usadas:
# -k: Seguir la compilación aunque haya fallos
# -V: Verbose
# -v: versión
# -o <ruta>: Carpeta donde se van a crear los informes HTML. Por defecto coge /tmp
scan-build -k -V -v -o ${OUTPUT_DIR} make
 
# A scan-view hay que indicarle la carpeta donde tiene los HTML, no un HTML concreto.
#/usr/lib/llvm-3.8/bin/scan-view /home/lks/workspace/programs_to_test/build_debug/scan-build-output/2017-01-03-144535-23596-1
# Ejecuto un comando para quedarme con el último fichero
/usr/lib/llvm-3.8/bin/scan-view ${OUTPUT_DIR}/$(ls ${OUTPUT_DIR} | sort -n | tail -n 1)