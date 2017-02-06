Proyecto BASE
Solo un tipo de configuración de proyecto
Documentación de proyectos

Librerías Thirdparty
	Para las librerías Thirdparty habría que buscar primero si la librería existe y en caso contrario tomar el tar/tar.gz/tgz/tar.bz2/zip/gzip correspondiente
	Este fichero se descomprimiría en el directorio build y serviría para compilar la librería. Si se quisiera instalar en algún directorio habría que modificar el INSTALL_PATH de la macro.

Test de librerías:
	Una vez compilado ejecutar el comando make test. Depende de la arquitectura en la cual esté construido el proyecto. Solo se podrá hacer si se coge la configuración del proyecto de SISTEMA. En el resto de caso el Makefile es un script de bash que habría que mover junto con el/los programas de test y probar.
	Comando:
		$ make test

Generación de documentación:
	En el CMakeFiles.txt se habilita una opción para documentar y varias para indicar cómo hacerlo. Si se habilitan se puede documentar con el comando:
		$ make doc

Trabajo con Eclipse:
    Este es un proyecto que se compila con CMAKE. Hay dos formas de trabajar
con él: 
    1.- Crear una carpeta build y usar cmake desde esa carpeta y olvidarse de
usar Eclipse
    2.- Crear una carpeta build un directorio más arriba y crear un proyecto
Eclipse para cmake desde esa carpeta. Este proyecto incluye un fichero
.project porque se ha creado de esa forma.


TODO:
- Ejecutar algún script o meter algún script que exporte variables
