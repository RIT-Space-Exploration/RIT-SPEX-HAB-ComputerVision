cmake_minimum_required(VERSION 2.8) 
PROJECT (RIT_SPEX_Horizon)
find_package(OpenCV REQUIRED)
set(NAME_SRC
	src/main.cpp
	src/detectLines.cpp
	)

set(NAME_HEADERS
	include/detectLines.h 
	)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( RIT_SPEX_Horizon ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries( RIT_SPEX_Horizon ${OpenCV_LIBS} )
