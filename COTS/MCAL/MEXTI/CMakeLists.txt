# set minimum required version of cmake to avoid errors
cmake_minimum_required(VERSION 3.22)

# project name + defining used languages
project(MEXTI C) 

# collect library source files
file(GLOB_RECURSE ${PROJECT_NAME}_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# collecting GIE src file
file(GLOB_RECURSE GIE_SRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/GIE/src/*.c)

# collect library header files
file(GLOB_RECURSE ${PROJECT_NAME}_LIB_INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
file(GLOB_RECURSE ${PROJECT_NAME}_STDLIB_INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../STD_LIB/inc/*.h)
file(GLOB_RECURSE ${PROJECT_NAME}_COMMON_INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/inc/*.h)

# combine all header file variables into a single variable
set(${PROJECT_NAME}_INC_FILES "${${PROJECT_NAME}_LIB_INC_FILES}" "${${PROJECT_NAME}_STDLIB_INC_FILES}" "${${PROJECT_NAME}_COMMON_INC_FILES}")

# setting default compiler for C in this CMake file
set(CMAKE_C_COMPILER "/usr/bin/avr-gcc")

# create a static library
add_library(${PROJECT_NAME} STATIC "${${PROJECT_NAME}_SRC_FILES}" ${GIE_SRC_FILE})

# compiler options for library
target_compile_options( ${PROJECT_NAME}
    PRIVATE
    -mmcu=${COMPILE_MCU_NAME}
	-DF_CPU=${F_CPU}
	-funsigned-char -funsigned-bitfields -DDEBUG
    -MD -MP -MF "$(@:%.o=%.d)" -MT "$(@:%.o=%.d)" -MT "$(@:%.o=%.o)"
	-Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall
)

# linker options for library
target_link_options( ${PROJECT_NAME}
	PRIVATE
	-Wl,--gc-sections
)

# link with required MCAL libraries
target_link_libraries(${PROJECT_NAME} PRIVATE MGIE)

# in order to allow main to use .h & pbcfg.h -> make them interface
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# std_lib will be public to anyone who wants to use through this MCAL lib
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../STD_LIB/inc)

# GIE lib will be public to anyone who wants to use it throught this MCAL lib
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/GIE/inc)

# registers should ABSOLUTELY BE private
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/inc)