# set minimum required version of cmake to avoid errors
cmake_minimum_required(VERSION 3.22)

# to make sure CMake knows that the target will not be executed on this machine
set(CMAKE_SYSTEM_NAME Generic)

# set C && Cpp versions
set(CMAKE_C_STANDARD 99)

# project name + defining used languages 
project(AVR_PROJECT C)

# avr mcu is ATMEGA32 clocked @16MHz
set(MCU atmega32) 	# for compiler
set(MCU2 m32)    	# for avrdude
#set(FCPU 16000000UL)	# for frequency

# programmer type 
set(PROGRAMMER usbasp) 

# setting avrdude flash flags
set(FLASH_FLAGS "-R .eeprom -R .lock -R .signature")

# collect all .c files
file(GLOB_RECURSE ${PROJECT_NAME}_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# collect all .h files
file(GLOB_RECURSE ${PROJECT_NAME}_INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)

# defining a list of MCAL libraries
set(MCAL_LIB
	MDIO
	MPORT	
)

# looping over all libs to build them
foreach(mcal_lib ${MCAL_LIB})
	add_subdirectory(
	    ${CMAKE_CURRENT_SOURCE_DIR}/../COTS/MCAL/${mcal_lib}
	    ${CMAKE_BINARY_DIR}/${mcal_lib}
	)
endforeach()

# setting default compiler for C
set(CMAKE_C_COMPILER /usr/bin/avr-gcc)

# setting compiler flags for C && Cpp
add_compile_options(-Wall -Os -g -mmcu=${MCU})

## TO DO
# add_compiler_definitions() # to define macros

# setting linker flags
add_link_options(-mmcu=${MCU} -Wl,--gc-sections)

# compiling and getting .elf file
add_executable(${PROJECT_NAME}.elf "${${PROJECT_NAME}_SRC_FILES}" "${${PROJECT_NAME}_INC_FILES}") # main target
target_link_libraries(${PROJECT_NAME}.elf PRIVATE ${MCAL_LIB})

# adding a custom target/build rule for creating .hex file
add_custom_target(convert-elf-to-hex 
	ALL
	DEPENDS ${PROJECT_NAME}.elf
	COMMAND avr-objcopy ${FLASH_FLAGS} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
	COMMENT "Generating .hex file from .elf file"
	)

# adding a custom target/build rule for burning .hex file on mcu using avrdude
add_custom_target(flash
	DEPENDS convert-elf-to-hex
	COMMAND avrdude -c ${PROGRAMMER} -p ${MCU2} -U flash:w:${PROJECT_NAME}.hex:i -B 1
    COMMENT "Burning .hex file into mcu flash"
	)

# modify the clean build rule to delete the .hex file
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_NAME}.hex)
