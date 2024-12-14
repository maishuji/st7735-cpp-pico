# ST7735 C++ Library for Raspberry Pi Pico

This project is a C++ library to interface with the ST7735 TFT LCD display using the Raspberry Pi Pico and the Pico SDK. 

## Features

    - SPI Communication
    - CPP implementation (C++20+)

## Wire Connections

| ST7735 PIN | Pico Pin | Description |
| ---------- | -------- | ----------- |
| VCC | 3.3V | Power supply |
| GND | GND | Ground |
| SCL (CLK) | GP10 (SPI0 SCK) | SPI Clock|
| SDA (DIN) | GP11 (SPI0 MOSI) | SPI Data (Master Out Slave In): </br> The Master sends data to slave device (receiver)|
| RES | GP12 |  Reset Signal |
| DC | GP13 |  Data/Command select |
| CS | GP14 |  Chip Select (optional) | 

## Requirements

    - Raspberry Pi Pico (or another RP2040-based board)
    - ST7735 TFT Display
    - Pico SDK installed and configured
    - A C++20-compatible compiler

## Building the Project

Create build directory
```bash
mkdir build && cd build
```
Configure the project
```bash
cmake -DPICO_SDK_PATH=<path-to-pico-sdk> ..
```
Build the project
```bash
make
```

## Licensing
This project is provided under the MIT License, allowing you to use, modify, and distribute it freely.