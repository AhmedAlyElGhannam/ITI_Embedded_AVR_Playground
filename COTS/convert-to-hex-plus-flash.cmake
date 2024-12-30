macro(convert_to_hex_and_flash PROJECT_NAME TARGET_MCU PROGRAMMER)
    # setting flash flags
    set(FLASH_FLAGS "-R .eeprom -R .lock -R .signature")

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
    COMMAND avrdude -c ${PROGRAMMER} -p ${TARGET_MCU} -U flash:w:${PROJECT_NAME}.hex:i -B 1
    COMMENT "Burning .hex file into mcu flash"
    )    
endmacro()




# # setting avrdude flash flags
     

    # # Add custom target for generating .hex file from .elf
    # add_custom_target(
    #     flash
    #     ALL
    #     DEPENDS ${PROJECT_NAME}.elf
    #     COMMAND avr-objcopy ${FLASH_FLAGS} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    #     VERBATIM
    #     COMMENT "Generating .hex file from .elf file"
    # )
    
    # # Modify the clean build rule to delete the .hex file
    # set_directory_properties(
    #     PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_NAME}.hex
    # )
    
    # # Add custom target for burning the .hex file onto the MCU
    # add_custom_target(
    #     burn
    #     DEPENDS flash
    #     COMMAND avrdude -c ${PROGRAMMER} -p ${MCU2} -U flash:w:${PROJECT_NAME}.hex:i -B 1
    #     VERBATIM
    #     COMMENT "Burning .hex file into MCU flash"
    # )
