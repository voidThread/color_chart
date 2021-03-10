cmake_minimum_required(VERSION 3.16)
project(color_chart VERSION 0.0.1 DESCRIPTION 
	"Test gradient chart generator")

set(SOURCE_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source )
set(SOURCE_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(unit_test)

set(SOURCE_CODE 
	${SOURCE_CODE_DIR}/Display.cpp)

set(SOURCE_HEADERS 
	${SOURCE_HEADERS_DIR}/Display.h)

add_executable(color_chart main.cpp ${SOURCE_CODE} ${SOURCE_HEADERS})
