# teensy4

![CI Status](https://github.com/ajay/teensy4/actions/workflows/c-cpp.yml/badge.svg)

## Installation / Environment

#### Dependencies:
- `arm-none-eabi-gcc`
- `clang-format`
- `libusb-dev`
- `picocom`

#### Installation
- `sudo apt install gcc-arm-none-eabi clang-format libusb-dev picocom`

- In order for serial comm to work properly:
    - Get udev rules from here: https://www.pjrc.com/teensy/00-teensy.rules
    - Copy udev rules to `/etc/udev/rules.d/`:
        `sudo cp 00-teensy.rules /etc/udev/rules.d/`
