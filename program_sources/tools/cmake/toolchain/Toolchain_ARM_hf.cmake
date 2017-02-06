# this one is important
SET(CMAKE_SYSTEM_NAME Arm-Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
#CMAKE_FORCE_C_COMPILER(arm-linux-gnueabihf-gcc GNU)
#CMAKE_FORCE_CXX_COMPILER(arm-linux-gnueabihf-g++ GNU)
SET(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER   arm-linux-gnueabihf-g++)

SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall -Werror -W -Wno-return-type" )
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -pipe -march=armv3" )
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g3 -Wall -Werror -W -Wno-return-type" )
SET(CMAKE_C_FLAGS_RELEASE "-O2 -pipe -march=armv3" )

#set(CMAKE_C_COMPILER /home/devel/gcc-4.7-linaro-rpi-gnueabihf/bin/arm-linux-gnueabihf-gcc)
#set(CMAKE_CXX_COMPILER /home/devel/gcc-4.7-linaro-rpi-gnueabihf/bin/arm-linux-gnueabihf-g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /usr/arm-linux-gnueabi)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


