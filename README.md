This is a simple implementation of the Reed-Solomon code in C++. The implementation only supports encoding and erasure correction (it is not a full decoder).

This codec is part of my [SOP](https://eng.uvm.dk/upper-secondary-education/national-upper-secondary-education-programmes/the-higher-technical-examination-programme--htx-).
The project report, can be read [here](https://github.com/Sveske-Juice/hamming7-4-codec/blob/dd7fc7e6e56def173401aa85b3a24f58be36c71a/error_correction_codes_carl_benjamin_s_dreyer_sop_2023.pdf) (in danish).

## Build
If you're on Linux just type `make` in the root directory and it will build the program and unit tests for you.

Manual:
```
mkdir -p build/
cd build/
cmake ..
```
Then to only build program:\
`make rsc`\
the unit tests:\
`make tests`\
or build all:\
`make`


## How to use
see [main.cpp](https://github.com/Sveske-Juice/reed-solomon-codec/blob/master/main.cpp) for an example of how to use the encoding decoding facade functions.

resource: https://en.wikiversity.org/wiki/Reed%E2%80%93Solomon_codes_for_coders
