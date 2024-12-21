# set minimum required version of cmake to avoid errors
cmake_minimum_required(VERSION 3.22)

# project name + defining used languages
project(MDIO C) 

# collect library source files
file(GLOB MDIO_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# collect library header files
file(GLOB MDIO_LIB_INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
file(GLOB MDIO_STDLIB_INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../STD_LIB/inc/*.h)
file(GLOB MDIO_COMMON_INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/inc/*.h)

# combine all header file variables into a single variable
set(MDIO_INC_FILES ${MDIO_LIB_INC_FILES} ${MDIO_STDLIB_INC_FILES} ${MDIO_COMMON_INC_FILES})

# include directory for all .h files used by this MCAL lib
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../STD_LIB/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/inc
)

# create a static library
add_library(${PROJECT_NAME} STATIC ${MDIO_SRC_FILES} ${MDIO_INC_FILES})

# in order to allow main to use .h & pbcfg.h -> make them interface
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# std_lib will be public to anyone who wants to use though this MCAL lib
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../STD_LIB/inc)

# registers should ABSOLUTELY BE private
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/inc)
