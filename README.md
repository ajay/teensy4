# teensy4 setup

## Installation / Environment

#### Dependencies:
- `arm-none-eabi-gcc`
- `libusb-dev`
- `picocom`

#### Installation
- `sudo apt install gcc-arm-none-eabi libusb-dev picocom`

- In order for serial comm to work properly:
    - Get udev rules from here: https://www.pjrc.com/teensy/00-teensy.rules
    - Copy udev rules to `/etc/udev/rules.d/`:
        `sudo cp 00-teensy.rules /etc/udev/rules.d/`
