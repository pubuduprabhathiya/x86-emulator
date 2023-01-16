# x86-emulator
Developing an x86 Processor Instruction Emulator

## Build instructions

```bash
mkdir build
cd build
cmake .. 
make
```

## Run tests

```bash
./main -t
```
## Run Instruction sequence
 
```bash
./main -s [path to input file]
```

eg:- ```./main -s ../sequence/seq0```

## Run Instruction 

```bash
./main [Instruction sequence]
```

eg:- ```./main 00 00```