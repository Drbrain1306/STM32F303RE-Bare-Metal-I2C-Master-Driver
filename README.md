## Repo Description
A register-level bare-metal I2C master driver implemented on the STM32F303RE (ARM Cortex-M4) communicating with an Arduino Uno (ATmega328P) slave receiver.

## Hardware Setup & Pinout
| Signal  |  STM32F303RE Pin | Arduino Uno Pin | Description |

| **SDA** | PB9 (AF4) |             A4         | I2C Serial Data line |
| **SCL** | PB8 (AF4) |             A5         | I2C Serial Clock line |
| **GND** |   GND     |            GND         | Common Ground Reference |

## Features & Implementation Details
- **Pure Register Access:** Configured without vendor HAL or standard peripheral libraries.
- **GPIO Setup:** Configured `PB8` and `PB9` in Open-Drain mode with internal pull-ups enabled via `PUPDR`.
- **Clock & Timing:** Configured `I2C1_TIMINGR` for standard 100 kHz bus speed using the 8 MHz internal clock (HSI).
- **Auto-End Generation:** Leveraged hardware `AUTOEND` and `TXIS`/`STOPF` polling inside `I2C1_ISR` for efficient message sequencing.

## Challenges Solved
- Handled buffer sizing constraints between master frames and the AVR `Wire.h` 32-byte hardware buffer limit.
- Verified 7-bit slave address alignment in `I2C_CR2` bits `[7:1]`.
