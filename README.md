# ITI_Embedded_AVR_Playground

## Introduction
This repository contains my work in Embedded Firmware Development for AVR microcontrollers as part of the Embedded Software Architecture course taught by Eng. [Romario Bassem](https://github.com/RomarioBasm) in Information Technology Institute (ITI)'s 9-month Professional Training Program --- Embedded Systems Track.

## Overview
Since AVR architecture is fairly simple, it was a golden opportunity to learn how to design low-level drivers through intricate techniques and utilize tools like [CMake](https://gitlab.kitware.com/cmake/cmake) for building and flashing, [Unity Test Framework](https://github.com/ThrowTheSwitch/Unity) for writing unit tests for drivers, and [cppcheck](https://github.com/danmar/cppcheck) to test how compliant the software I wrote is with MISRAC standard.

### Progress---MCAL
- [x] MDIO (Tested on Hardware && Proteus)
- [x] MPORT (Tested on Hardware && Proteus)
- [x] MGIE (Tested on Proteus)
- [x] MEXTI (Tested on Proteus)
- [x] MTIMER (Tested TIMER0 on Proteus)


### Progress---HAL
- [x] HLED (Tested on Hardware && Proteus)
- [x] HSWITCH (Tested on Hardware && Proteus)
- [x] H7SEGMENT (Tested on Hardware && Proteus)
- [x] HLCD (Tested on Proteus)
- [x] HKEYPAD (Tested on Proteus)

## Prerequisites
Install the following packages:
```bash
sudo apt install gcc-avr avr-libc avrdude
# gcc-avr -> avr toolchain
# avr-libc -> avr c library with avr-headers
# avrdude -> for flashing hex/bin files
```

## Compiling, Building, and Flashing
```bash
cmake -S . -B build 
cmake --build build
cd build
make flash
```

## Simulating Using SimulAVR && Debugging Using GDB

> Open a terminal and execute the following:

```bash
simulavr -d atmega32 -f AVR_PROJECT.elf --gdbserver
```

> In another terminal, run:

```bash
avr-gdb AVR_PROJECT.elf
```

> In order to begin debugging using GDB, connect it with SimulAVR using the following command. Port 1212 is the default port for SimulAVR; make sure it matches the port returned by SimulAVR upon starting it.

```bash
target remote localhost:1212
```

> Symbol Table is read by GDB by default if `-g` compiler flag was used to add debugging symbols.

### Common GDB Commands

1. To place a breakpoint:
   ```bash
   break LABEL_NAME
   ```

1. To continue executing until breakpoint is reached:
   ```bash
   c
   ```

1. To print a variable's value (if it is a pointer for example):
   ```bash
   print *PTR_NAME
   ```

1. To single step in C code:
   ```bash
   n
   ```

1. To switch code layout from C to Assembly:
   ```bash
   layout asm
   ```

1. To single step in Assembly code:
    ```bash
    stepi
    ```
    ```bash
    si
    ```

1. To switch code layout back to C:
   ```bash
   layout src
   ```

## Simulating Using SimulAVR && Debugging Using GDB Through VSCode

## Labs: Overview
### Lab 1
> Requirements: 4 applications in total.

1. Task 1 -> Toggle an LED every 500ms.
1. Task 2 -> Turn an LED on and off every 500ms.
1. Task 3 -> If a button is pressed, turn on an LED; else, turn it off.
1. Task 4 -> Pressing a button increments a 4-bit binary counter whose output is shown on 4 LEDs.


### Lab 2
> Requirements: DIO driver with 5 APIs + 2 tasks.

```c
MDIO_enuErrorStatus_t MDIO_enuSetPinConfigration(Copy_enuPortNum,Copy_enuPinNum,Copy_enuConfigration);

MDIO_enuErrorStatus_t 
MDIO_enuSetPortConfigration(Copy_enuPortNum,Copy_enuConfigration);

MDIO_enuErrorStatus_t 
MDIO_enuSetPinValue( Copy_enuPortNum, Copy_enuPinNum, Copy_enuState);

MDIO_enuErrorStatus_t 
MDIO_enuSetPortValue(Copy_enuPortNum,Copy_enuPortState);

MDIO_enuErrorStatus_t 
MDIO_enuGetPinValue(Copy_enuPortNum,Copy_enuPinNum,u8* Add_pu8PinValue);
```

1. Task 1 -> Multiple buttons control the states of multiple LEDs.
1. Task 2 -> Pressing a button should start an 8-bit binary counter whose output is displayed on 8 LEDs.


### Lab 3
> Requirements: An additional API for DIO driver + 1 task.

```c
void MDIO_vInit(void);
```

1. Task 1 -> Toggle 3 LEDs' state using 3 buttons. These components should all be initialized using the newly-created API.


### Lab 4
> Requirements: MPORT driver with 2 APIs + migrate `MDIO_vInit` to MPORT driver.

```c
MPORT_enuErrorStatus_t 
MPORT_enuSetPinDirection( u8 Copy_enuPinNum  ,  u8  Copy_enuPinDirection  );

MPORT_enuErrorStatus_t 
MPORT_enuSetPinMode( u8 Copy_enuPinNum  ,  MPORT_enuPinMode_t Copy_enuPinMode );

void
MPORT_voidInit(void);
```

### Lab 5
> Requirements: HAL drivers for LED and SWITCH; each with 2 APIs.

```c
/* LED */
void LED_init(void);
LED_enuErrorStatus_t LED_enuSetLedState(u8 Copy_u8LedName, u8 Copy_u8State);
```

```c
/* SWITCH */
void SWITCH_init(void);
SWITCH_enuErrorStatus_t SWITCH_enuGetSwitchState(u8 Copy_u8SwitchName, u8* Add_pu8State);
```

### Lab 5.5 (EXTRA)
> Requirements: Modify all already-implemented drivers to match MISRA C guidelines.
> Details: Eliminated all `goto` statements + added `else` for every `if` + used C's commenting style `/**/` instead of Cpp's `//`.


### Lab 6
> Requirements: HAL driver for 7 Segment Display with 3 APIs.

```c
void HSEVENSEG_vInit(void);
void HSEVENSEG_vSetValue(u8 Copy_enuSevenSegNum , u8 Copy_u8Value);
HSEVENSEG_enuErrorStatus_t HSEVENSEG_enuSetMultiDigitValue(u16 Copy_u16Value);
```


### Lab 7
> Requirements: HAL driver for LCD with 7 APIs.

```c
void HLCD_voidInit(void);
void HLCD_voidWriteData(char data);
void HLCD_voidWriteCommand(uint8_t command);
void HLCD_voidGoToXY(uint8_t X, uint8_t Y);
void HLCD_voidDisplaySpecialChar(char* pattern, uint8_t X, uint8_t Y);
void HLCD_voidWriteString(char* str);
void HLCD_voidWriteNumber(uint32_t number);
```


### Lab 8
> Requirements: HAL driver for Keypad with 2 APIs.

```c
void HKEYPAD_voidInit(void);
ErrorStatus_t HKEYPAD_enuGetKey(uint8_t* char);
```


### Lab 9
> Requirements: MCAL driver for EXTI with 2 APIs.
```c
void EXTI_init(void);
void EXTI_registerCBF(EXTI_CBF_t cbf);
```


### Lab 10
> Requirements: MCAL driver for Timer with 6 APIs.
```c
MTIMER_enuErrorStatus_t MTIMER_enuInit(MTIMER_enuTimers_t copy_enuTimer);
MTIMER_enuErrorStatus_t MTIMER_enuSetOverflowVal(MTIMER_enuTimers_t copy_enuTimer, uint32_t copy_uint32PreloadVal);
MTIMER_enuErrorStatus_t MTIMER_enuSetClkSelection(MTIMER_enuTimers_t copy_enuTimer, MTIMER_enuClockSelection_t copy_enuClkSel);
MTIMER_enuErrorStatus_t MTIMER_enuSetOutputCompareVal(MTIMER_enuTimers_t copy_enuTimer, uint8_t copy_uint32PreloadVal);
MTIMER_enuErrorStatus_t MTIMER_enuGetCounterVal(MTIMER_enuTimers_t copy_enuTimer, uint32_t* ptr_uint32CounterVal);
MTIMER_enuErrorStatus_t MTIMER_enuSetTimerCallBack(MGIE_CallBackFunction_t ptr_ISR, MGIE_enuVectorTable_t copy_enuISRNum);
```


## Labs: Progress
### Lab 1
- [x] Task 1 (Tested on Hardware)

- [x] Task 2 (Tested on Hardware)

- [x] Task 3 (Tested on Hardware)

- [x] Task 4 (Tested on Hardware)


### Lab 2
- [x] MDIO Driver (Tested on Hardware && Proteus)

- [x] Task 1 (Tested on Proteus)

- [x] Task 2 (Tested on Proteus)

#### Sequence Diagrams
![](SequenceDiagrams/MDIO/MDIO_enuGetPinValue.png)
![](SequenceDiagrams/MDIO/MDIO_enuSetPinConfigration.png)
![](SequenceDiagrams/MDIO/MDIO_enuSetPinValue.png)
![](SequenceDiagrams/MDIO/MDIO_enuSetPortConfigration.png)
![](SequenceDiagrams/MDIO/MDIO_enuSetPortValue.png)


### Lab 3
- [x] Task 1 (Tested on Proteus)

#### Sequence Diagram
![](SequenceDiagrams/MDIO/MDIO_voidInit.png)


### Lab 4
- [x] MPORT Driver (Tested on Hardware && Proteus)
- [x] Task 1 (Tested on Hardware && Proteus)

#### Sequence Diagrams 
![](SequenceDiagrams/MPORT/MPORT_enuSetPinDirection.png)
![](SequenceDiagrams/MPORT/MPORT_enuSetPinMode.png)
![](SequenceDiagrams/MPORT/MPORT_voidInit.png)


### Lab 5
- [x] HLED Driver (Tested on Hardware && Proteus)
- [x] HSWITCH Driver (Tested on Hardware && Proteus)

#### Sequence Diagrams (HLED)
![](SequenceDiagrams/HLED/HLED_voidInit.png)
![](SequenceDiagrams/HLED/HLED_uint8SetLEDValue.png)

#### SequenceDiagrams (HSWITCH)
![](SequenceDiagrams/HSWITCH/HSWITCH_voidInit.png)
![](SequenceDiagrams/HSWITCH/HSWITCH_enuGetSwitchValue.png)


### Lab 5.5 (EXTRA)
- [x] Used [cppcheck](https://github.com/danmar/cppcheck) to see if my code breaks MISRA-C's guidelines.


### Lab 6
- [x] H7SEGMENT Driver (Tested on Hardware && Proteus)

#### Sequence Diagrams
![](SequenceDiagrams/H7SEGMENT/H7SEGMENT_voidInit.png)
![](SequenceDiagrams/H7SEGMENT/H7SEGMENT_enuWriteDigit.png)
![](SequenceDiagrams/H7SEGMENT/H7SEGMENT_enuWriteMultiDigitValue.png)


### Lab 7
- [x] HLCD Driver (Tested on Proteus)

#### Sequence Diagrams
![](SequenceDiagrams/HLCD/HLCD_enuInit.png)
![](SequenceDiagrams/HLCD/HLCD_voidWriteCommand.png)
![](SequenceDiagrams/HLCD/HLCD_enuGoToXY.png)

![](SequenceDiagrams/HLCD/HLCD_enuGoToCGRAM.png)
![](SequenceDiagrams/HLCD/HLCD_enuStoreSpecialCharacter.png)
![](SequenceDiagrams/HLCD/HLCD_enuDisplaySpecialCharacter.png)

![](SequenceDiagrams/HLCD/HLCD_enuWriteCharacter.png)
![](SequenceDiagrams/HLCD/HLCD_enuWriteInteger.png)
![](SequenceDiagrams/HLCD/HLCD_enuWriteString.png)


![](SequenceDiagrams/HLCD/HLCD_enuClrDisplay.png)
![](SequenceDiagrams/HLCD/HLCD_enuReturnHome.png)

![](SequenceDiagrams/HLCD/HLCD_enuCursorBlinkOnOff.png)
![](SequenceDiagrams/HLCD/HLCD_enuCursorShiftLeft.png)
![](SequenceDiagrams/HLCD/HLCD_enuCursorShiftLeft.png)
![](SequenceDiagrams/HLCD/HLCD_enuCursorShiftRight.png)

![](SequenceDiagrams/HLCD/HLCD_enuDisplayOnOff.png)
![](SequenceDiagrams/HLCD/HLCD_enuDisplayShiftLeft.png)
![](SequenceDiagrams/HLCD/HLCD_enuDisplayShiftRight.png)

 

### Lab 8
- [x] HKEYPAD Driver (Tested on Proteus)

#### Sequence Diagrams
![](SequenceDiagrams/HKEYPAD/HKEYPAD_enuInit.png)
![](SequenceDiagrams/HKEYPAD/HKEYPAD_enuGetPressedKey.png)



### Lab 9
- [x] MEXTI Driver (Builds Successfully But Not Tested Yet)
- [x] GIE Driver (Builds Successfully But Not Tested Yet --- **EXTRA**)

#### Sequence Diagrams 
![](SequenceDiagrams/MEXTI/MEXTI_enuInit.png)
![](SequenceDiagrams/MEXTI/MEXTI_enuRegisterCallBackFunc.png)


### Lab 10
- [x] MTIMER Driver (Tested Timer0 on Proteus)
![](./SequenceDiagrams/MTIMER/MTIMER_enuInit.png)
![](./SequenceDiagrams/MTIMER/MTIMER_enuSetClkSelection.png)
![](./SequenceDiagrams/MTIMER/MTIMER_enuSetOutputCompareVal.png)
![](./SequenceDiagrams/MTIMER/MTIMER_enuSetOverflowVal.png)
![](./SequenceDiagrams/MTIMER/MTIMER_enuGetCounterVal.png)
![](./SequenceDiagrams/MTIMER/MTIMER_enuSetTimerCallBack.png)
