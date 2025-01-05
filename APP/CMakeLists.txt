# set minimum required version of cmake to avoid errors
cmake_minimum_required(VERSION 3.22)

# to make sure CMake knows that the target will not be executed on this machine
set(CMAKE_SYSTEM_NAME Generic)

# setting target architecture to AVR
set(CMAKE_SYSTEM_PROCESSOR avr)

# set C && Cpp versions
set(CMAKE_C_STANDARD 99)

# project name + defining used languages 
project(AVR_PROJECT C)

# include ,cmake script for converting .elf to .hex and flashing
include(${CMAKE_CURRENT_SOURCE_DIR}/../COTS/convert-to-hex-plus-flash.cmake)

# avr mcu is ATMEGA32 clocked @16MHz
set(COMPILE_MCU_NAME atmega32) 	# for compiler
set(FLASH_MCU_NAME m32)    	# for avrdude
#set(FCPU 16000000UL)	# for frequency

# programmer type 
set(PROGRAMMER usbasp) 

# setting avrdude flash flags
set(FLASH_FLAGS "-R .eeprom -R .lock -R .signature")

# collect all .c files
file(GLOB_RECURSE ${PROJECT_NAME}_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# defining a list of MCAL libraries that will be used to build HAL libraries
set(MCAL_LIB
	MDIO
	MPORT	
)

# looping over all libs to build them
foreach(mcal_lib ${MCAL_LIB})
	add_subdirectory(
	    "${CMAKE_CURRENT_SOURCE_DIR}/../COTS/MCAL/${mcal_lib}/"
	    "${CMAKE_BINARY_DIR}/${mcal_lib}/"
	)
endforeach()

# defining a list of HAL libraries that app depends on
set(HAL_LIB
	HLED
	HSWITCH
	H7SEGMENT
)

# looping over all HAL libs to build them
foreach(hal_lib ${HAL_LIB})
	add_subdirectory(
	    "${CMAKE_CURRENT_SOURCE_DIR}/../COTS/HAL/${hal_lib}"
	    "${CMAKE_BINARY_DIR}/${hal_lib}"
	)
endforeach()

# setting default compiler for C in this CMake file
set(CMAKE_C_COMPILER avr-gcc)

# setting default ar (lib archiving) tool in this CMake file
set(CMAKE_AR avr-ar)

# setting default linker in this CMake file
set(CMAKE_LINKER avr-ld)

# setting compiler flags for C && Cpp
add_compile_options(-Wall -Os -g -mmcu=${COMPILE_MCU_NAME})

## TO DO
# add_compiler_definitions() # to define macros

# setting linker flags
add_link_options(-mmcu=${COMPILE_MCU_NAME} -Wl,--gc-sections)

# compiling and getting .elf file
add_executable(${PROJECT_NAME}.elf "${${PROJECT_NAME}_SRC_FILES}") # main target
target_link_libraries(${PROJECT_NAME}.elf PRIVATE ${MCAL_LIB} ${HAL_LIB})

# calling macro for converting .elf into .hex and flashing it on specified mcu
convert_to_hex_and_flash(${PROJECT_NAME} ${FLASH_MCU_NAME} ${PROGRAMMER})

# modify the clean build rule to delete the .hex file
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_NAME}.hex)
