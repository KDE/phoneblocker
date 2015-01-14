cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(BBCascades REQUIRED)
find_package(BBPim REQUIRED)

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${BBCASCADES_INCLUDE_DIR}
    $ENV{QNX_TARGET}/usr/include
)

set(PhoneBlocker_SRCS
    main.cpp
    blocker.cpp
)

QT4_ADD_RESOURCES(PhoneBlocker_RCC_SRCS
    phoneblocker.qrc
)

add_executable(phoneblocker ${PhoneBlocker_SRCS} ${PhoneBlocker_RCC_SRCS})

target_link_libraries(
    phoneblocker

    ${QT_QTCORE_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTDECLARATIVE_LIBRARY}

    ${BBCASCADES_LIBRARY}
    ${BBSYSTEM_LIBRARY}
)
