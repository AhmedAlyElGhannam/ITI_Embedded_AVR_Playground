# Unit Tests Using Unity

```bash
gprof UNIT_TEST.elf gmon.out --graph > analysis.txt # checking for execution time and number of calls for each function
valgrind ./UNIT_TEST.elf # checking for undefined behaviour 
```