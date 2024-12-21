# ITI_Embedded_AVR_Playground
```bash
cmake -S . -B build -DCMAKE_C_COMPILER=/usr/bin/avr-gcc
cmake --build build
cd build
make flash
make burn
simulavr --device atmega32 --gdbserver --file AVR_TRIAL.elf
```

in a new tab, run:

```bash
avr-gdb AVR_TRIAL.elf
target remote localhost:1212
```
