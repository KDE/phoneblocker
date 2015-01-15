# - Try to find BB
# Once done this will define
#
#  BB_FOUND - system has BB
#  BB_INCLUDE_DIRS - the BB include directory
#  BB_LIBRARIES - Link these to use BB
#
#  Copyright (c) 2013 Laszlo Papp <lpapp@kde.org>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

if (BB_FIND_REQUIRED)
    set(_bbReq "REQUIRED")
endif (BB_FIND_REQUIRED)

find_package(Qt 4.8 ${_bbReq})

find_path(BB_INCLUDE_DIR Global
  HINTS
  ENV BBDIR
  PATH_SUFFIXES include include/bb
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /opt/local
  /opt
  $ENV{QNX_TARGET}/usr
)

find_library(BB_LIBRARY
  NAMES BB bb
  HINTS
  ENV BBDIR
  PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /opt/local
  /opt
  $ENV{QNX_TARGET}/armv7/usr
  $ENV{QNX_TARGET}/armle-v7/usr
)


# handle the QUIETLY and REQUIRED arguments and set BB_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BB DEFAULT_MSG BB_LIBRARY BB_INCLUDE_DIR)

mark_as_advanced(BB_LIBRARY BB_INCLUDE_DIR)
