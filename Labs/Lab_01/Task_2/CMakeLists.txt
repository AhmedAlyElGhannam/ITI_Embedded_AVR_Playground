# set minimum required version of cmake to avoid errors
cmake_minimum_required(VERSION 3.22)

# to make sure CMake knows that the target will not be executed on this machine
set(CMAKE_SYSTEM_NAME Generic)

# set C && Cpp versions
set(CMAKE_C_STANDARD 99)
#set(CMAKE_CXX_STANDARD 99)

# project name + defining used languages (C && Cpp)
project(AVR_TRIAL C CXX)

# avr mcu is ATMEGA32 clocked @16MHz
set(MCU atmega32) 	# for compiler
set(MCU2 m32)    	# for avrdude
#set(FCPU 16000000UL)	# for frequency

# programmer type 
set(PROGRAMMER usbasp) 

# collect all .c files
file(GLOB SRC_FILES *.c)

# setting default compiler for C && Cpp
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

# setting compiler flags for C && Cpp
# set(COMMON_FLAGS "-Wall -Os -mmcu=${MCU} -DF_CPU=${FCPU}")
# set(CMAKE_C_FLAGS "${COMMON_FLAGS}")
# set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")
#add_compile_options(-Wall -Os -mmcu=${MCU} -DF_CPU=${F_CPU})
add_compile_options(-Wall -Os -mmcu=${MCU})

# setting linker flags
# set(LINKER_FLAGS "-Wl,--gc-sections")
add_link_options(-mmcu=${MCU} -Wl,--gc-sections)

# setting avrdude flash flags
set(FLASH_FLAGS "-R .eeprom -R .lock -R .signature")

# compiling and getting .elf file
add_executable(${PROJECT_NAME}.elf ${SRC_FILES}) # main target

# adding a custom target/build rule for creating .hex file
add_custom_target(flash 
	ALL
	DEPENDS ${PROJECT_NAME}.elf
	COMMAND avr-objcopy ${FLASH_FLAGS} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
	COMMENT "Generating .hex file from .elf file"
	)

# modify the clean build rule to delete the .hex file
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_NAME}.hex)


# adding a custom target/build rule for burning .hex file on mcu using avrdude
add_custom_target(burn
	DEPENDS flash
	COMMAND avrdude -c ${PROGRAMMER} -p ${MCU2} -U flash:w:${PROJECT_NAME}.hex:i -B 1
    COMMENT "Burning .hex file into mcu flash"
	)
