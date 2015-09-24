cmake_minimum_required(VERSION 3.2)
project(QtMarkup CXX)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

QT4_WRAP_CPP(MOCSrcs mainwindow.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
ADD_EXECUTABLE(qtmarkup main.cpp mainwindow.cpp ${MOCSrcs})
TARGET_LINK_LIBRARIES(qtmarkup Qt4::QtGui Qt4::QtWebKit)
