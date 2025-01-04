# set minimum required version of cmake to avoid errors
cmake_minimum_required(VERSION 3.22)

# project name + defining used languages
project(HLED C) 

# collect library source files
file(GLOB_RECURSE ${PROJECT_NAME}_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# defining a list of MCAL libraries used in this HAL library
set(MCAL_LIB
	MDIO
	MPORT	
)

# looping over all libs to build them
foreach(mcal_lib ${MCAL_LIB})
	add_subdirectory(
	    "${CMAKE_CURRENT_SOURCE_DIR}/../../MCAL/${mcal_lib}/"
	    "${CMAKE_BINARY_DIR}/${mcal_lib}/"
	)
endforeach()

# setting default compiler for C
set(CMAKE_C_COMPILER /usr/bin/avr-gcc)

# create a static library
add_library(${PROJECT_NAME} STATIC "${${PROJECT_NAME}_SRC_FILES}")

# link with required MCAL libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${MCAL_LIB})

# in order to allow main to use .h & pbcfg.h -> make them interface
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# std_lib will be public to anyone who wants to use though this MCAL lib
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../STD_LIB/inc)
