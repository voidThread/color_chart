cmake_minimum_required(VERSION 3.16)

find_package(GTest REQUIRED)
find_package(GTest REQUIRED)

set(TESTS
	)
set(INCLUDE_DIRS ../include)

add_executable(color_chart_test ${TESTS})
target_link_libraries(color_chart_test PRIVATE
	${GTEST_INCLUDE_DIRS}
	${GMOCK_INCLUDE_DIRS}
	${INCLUDE_DIRS})
target_link_libraries(color_chart_test GTest::GTest GTest::Main ${GMOCK_LIBRARIES})
