# set minimum required version of cmake to avoid errors
cmake_minimum_required(VERSION 3.22)

# project name + defining used languages
project(HLED) 
enable_language(C)

# collect library source files
file(GLOB_RECURSE ${PROJECT_NAME}_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# defining a list of MCAL libraries used in this HAL library
set(MCAL_LIB
	MDIO
	MPORT	
)

# create a static library
add_library(${PROJECT_NAME} STATIC "${${PROJECT_NAME}_SRC_FILES}")

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
target_link_libraries(${PROJECT_NAME} PRIVATE ${MCAL_LIB})

# in order to allow main to use .h & pbcfg.h -> make them interface
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# std_lib will be public to anyone who wants to use though this MCAL lib
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../STD_LIB/inc)
