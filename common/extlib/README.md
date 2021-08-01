# Teensy external libraries

## core
- repo - [github.com/PaulStoffregen/cores](https://github.com/PaulStoffregen/cores)
- version: [Teensyduino 1.54](https://github.com/PaulStoffregen/cores/releases/tag/1.54)
- commit: [7f0c153](https://github.com/PaulStoffregen/cores/commit/7f0c1531ec29c5b75a4c3dc446e4b09c3731c090)
- notes:
    - `teensy4` directory is taken and extracted into `extlib/core`, all other files are ignored
    - `teensy4/main.cpp` is deleted
    - all linker files have `DTCM AT>` added to `.text.csf` to resolve linker errors - see [here](https://forum.pjrc.com/threads/67252-Teensyduino-1-54-Beta-9?p=279524&viewfull=1#post279524)

## spi
- repo - [github.com/PaulStoffregen/SPI](https://github.com/PaulStoffregen/SPI)
- version: N/A
- commit: [574ab8c](https://github.com/PaulStoffregen/SPI/commit/574ab8c7a8a45ea21cc56dcc6b7361da90868e86)
- notes:
    - `SPI.cpp` / `SPI.h` taken and placed into `extlib/spi`, all other files are ignored