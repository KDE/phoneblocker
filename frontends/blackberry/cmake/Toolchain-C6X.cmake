#
# (C) Copyright 2012 Laszlo Papp <lpapp@kde.org>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#

SET(CMAKE_SYSTEM_NAME "Sysbios")
SET(CMAKE_SYSTEM_VERSION 7.4)
SET(CMAKE_SYSTEM_PROCESSOR armv7)

#SET(CMAKE_IMPORT_LIBRARY_SUFFIX ".a")

#SET(CMAKE_SHARED_LIBRARY_PREFIX "lib")
SET(CMAKE_SHARED_LIBRARY_PREFIX "")
SET(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
#SET(CMAKE_STATIC_LIBRARY_PREFIX "lib")
SET(CMAKE_STATIC_LIBRARY_PREFIX "")
SET(CMAKE_STATIC_LIBRARY_SUFFIX ".a")

IF(CMAKE_HOST_WIN32)
    SET(HOST_EXECUTABLE_SUFFIX ".exe")
ENDIF(CMAKE_HOST_WIN32)

FIND_PATH(C6X_HOST
    NAME bin/cl6x${HOST_EXECUTABLE_SUFFIX}
    PATHS $ENV{C6X_C_DIR} $ENV{C6X_C_DIR}/.. C:/ti/C6000CGT7.4.2
    NO_CMAKE_PATH
    NO_CMAKE_ENVIRONMENT_PATH
)
  
FIND_PATH(C6X_TARGET
  NAME include/c6x.h
  PATHS $ENV{C6X_C_DIR} $ENV{C6X_C_DIR}/.. C:/ti/C6000CGT7.4.2
  NO_CMAKE_PATH
  NO_CMAKE_ENVIRONMENT_PATH
)

SET(ENV{C6X_HOST} ${C6X_HOST})
SET(ENV{C6X_TARGET} ${C6X_TARGET})
IF(CMAKE_HOST_WIN32)
    SET(ENV{PATH} "$ENV{PATH};${C6X_HOST}/bin")
ENDIF(CMAKE_HOST_WIN32)

SET(CMAKE_MAKE_PROGRAM "${C6X_HOST}/bin/mk6x${HOST_EXECUTABLE_SUFFIX}"    CACHE PATH "C6000 Code Generation Tools Make Program")
SET(CMAKE_AR           "${C6X_HOST}/bin/ar6x${HOST_EXECUTABLE_SUFFIX}"    CACHE PATH "C6000 Code Generation Tools ar Program")
SET(CMAKE_NM           "${C6X_HOST}/bin/nm6x${HOST_EXECUTABLE_SUFFIX}"    CACHE PATH "C6000 Code Generation Tools nm Program")
SET(CMAKE_OBJDUMP      "${C6X_HOST}/bin/ofd6x${HOST_EXECUTABLE_SUFFIX}"   CACHE PATH "C6000 Code Generation Tools objdump Program")
SET(CMAKE_LINKER       "${C6X_HOST}/bin/lnk6x${HOST_EXECUTABLE_SUFFIX}"   CACHE PATH "C6000 Code Generation Tools Linker Program")
SET(CMAKE_STRIP        "${C6X_HOST}/bin/strip6x${HOST_EXECUTABLE_SUFFIX}" CACHE PATH "C6000 Code Generation Tools Strip Program")


SET(CMAKE_C_COMPILER ${C6X_HOST}/bin/cl6x${HOST_EXECUTABLE_SUFFIX})
SET(CMAKE_C_COMPILER_ARG1 "--abi=eabi --run_linker")
# SET(CMAKE_C_FLAGS_DEBUG "-g")
# SET(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
# SET(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
# SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

SET(CMAKE_CXX_COMPILER ${C6X_HOST}/bin/cl6x${HOST_EXECUTABLE_SUFFIX})
SET(CMAKE_CXX_COMPILER_ARG1 "--abi=eabi --run_linker")
# SET(CMAKE_CXX_FLAGS_DEBUG "-g")
# SET(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
# SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
# SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

SET(CMAKE_FIND_ROOT_PATH ${C6X_TARGET}) 
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
