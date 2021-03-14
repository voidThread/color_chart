cmake_minimum_required(VERSION 3.16)

set(SOURCE_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../source )
set(SOURCE_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include )
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(GTest REQUIRED)

set(TESTS
	linear_mix_test.cpp
	)

set(SOURCE_FILES 
	${SOURCE_CODE_DIR}/LinearMix.cpp
	)

add_executable(color_chart_test ${TESTS} ${SOURCE_FILES})
target_include_directories(color_chart_test PRIVATE
	${GTEST_INCLUDE_DIRS}
	${GMOCK_INCLUDE_DIRS}
	${SOURCE_HEADERS_DIR})
target_link_libraries(color_chart_test GTest::GTest GTest::Main ${GMOCK_LIBRARIES})
