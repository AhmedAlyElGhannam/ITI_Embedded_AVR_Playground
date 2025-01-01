# set minimum required version of cmake to avoid errors
cmake_minimum_required(VERSION 3.22)

# set C && Cpp versions
set(CMAKE_C_STANDARD 11)

# project name + defining used languages 
project(MPORT_UNIT_TEST C)

# defining include dir 
set(${PROJECT_NAME}_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc/")

# collect all .c files
file(GLOB_RECURSE ${PROJECT_NAME}_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# setting compiler flags for C (as written in included unity Makefile)
add_compile_options(
    # -std=c89    
    -Wall 
    -Wextra
    -Wpointer-arith
    -Wcast-align
    -Wwrite-strings
    -Wswitch-default
    -Wunreachable-code
    -Winit-self
    -Wmissing-field-initializers
    -Wno-unknown-pragmas
    -Wstrict-prototypes
    -Wundef
    -Wold-style-definition
    )

# defining UNIT_TESTING_MODE macro to include mock registers .h file instead of real one
add_compile_definitions(UNIT_TESTING_MODE) 

# compiling and getting .elf file
add_executable(${PROJECT_NAME}.elf "${${PROJECT_NAME}_SRC_FILES}") # main target

# defining include directory for all used .h files
target_include_directories(${PROJECT_NAME}.elf PRIVATE "${${PROJECT_NAME}_INC_DIR}")