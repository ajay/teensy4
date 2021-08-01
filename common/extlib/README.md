# Teensy external libraries

## core
- repo - [github.com/PaulStoffregen/cores](https://github.com/PaulStoffregen/cores)
- version: [Teensyduino 1.54](https://github.com/PaulStoffregen/cores/releases/tag/1.54)
- commit: [7f0c153](https://github.com/PaulStoffregen/cores/commit/7f0c1531ec29c5b75a4c3dc446e4b09c3731c090)
- notes:
    - `teensy4` directory is taken and extracted into `extlib/core`, all other files are ignored
    - `teensy4/main.cpp` is deleted
    - all linker files have `DTCM AT>` added to `.text.csf` to resolve linker errors - see [here](https://forum.pjrc.com/threads/67252-Teensyduino-1-54-Beta-9?p=279524&viewfull=1#post279524)

## fastled
- repo - [github.com/FastLED/FastLED](https://github.com/FastLED/FastLED)
- version: [3.4.0](https://github.com/FastLED/FastLED/releases/tag/3.4.0)
- commit: [2fe6aeb](https://github.com/FastLED/FastLED/commit/2fe6aebc778a836a8556b8e4508381e9c847f7a3)
- notes:
    - contents of `src` taken and placed into `extlib/fastled`, all other files are ignored

## smartmatrix
- repo - [github.com/pixelmatix/SmartMatrix](https://github.com/pixelmatix/SmartMatrix)
- version: [4.0.3](https://github.com/pixelmatix/SmartMatrix/releases/tag/4.0.3)
- commit: [1c6e53c](https://github.com/pixelmatix/SmartMatrix/commit/1c6e53c8b4317419b4b56ec49235e9ffb92581db)
- notes:
    - contents of `src` taken and placed into `extlib/smartmatrix`, all other files are ignored


## spi
- repo - [github.com/PaulStoffregen/SPI](https://github.com/PaulStoffregen/SPI)
- version: N/A
- commit: [574ab8c](https://github.com/PaulStoffregen/SPI/commit/574ab8c7a8a45ea21cc56dcc6b7361da90868e86)
- notes:
    - `SPI.cpp` / `SPI.h` taken and placed into `extlib/spi`, all other files are ignored
