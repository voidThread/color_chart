cmake_minimum_required(VERSION 3.16)
project(color_chart VERSION 0.0.1 DESCRIPTION 
	"Test gradient chart generator")

set(SOURCE_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source/ )
set(SOURCE_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/ )
set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(tests)

#set(SOURCE_HEADERS 
#	${SOURCE_HEADERS_DIR}/Defines.h
#	${SOURCE_HEADERS_DIR}/Display.h
#	${SOURCE_HEADERS_DIR}/LinearMix.h
#	${SOURCE_HEADERS_DIR}/ScreenBuffer.h
#	)

set(SOURCE_CODE 
	${SOURCE_CODE_DIR}Display.cpp
	${SOURCE_CODE_DIR}LinearMix.cpp
	${SOURCE_CODE_DIR}ScreenBuffer.cpp
	)

add_executable(color_chart main.cpp ${SOURCE_CODE} )
target_include_directories(color_chart PRIVATE
	${SOURCE_HEADERS_DIR}
	)
