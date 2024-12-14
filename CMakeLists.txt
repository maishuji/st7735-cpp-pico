cmake_minimum_required(VERSION 3.13)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
message(STATUS "PICO_SDK --> ${PICO_SDK_PATH}")
# Include the Pico SDK
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

# Set the project name
project(blink_led_pico)



# Initialize the Pico SDK
pico_sdk_init()





# Add the executable
add_executable(blink_led blink_led.cpp)


add_subdirectory(st7735cpp)

target_include_directories(blink_led PRIVATE st7735cpp)
# Link the standard Pico libraries
target_link_libraries(blink_led PRIVATE st7735cpp pico_stdlib hardware_spi)

# Disable/Enable USB output (optional, useful for debugging)
pico_enable_stdio_usb(blink_led 1)
# Enable UART output to the serial port
pico_enable_stdio_uart(blink_led 1)

# Create the UF2 file
pico_add_extra_outputs(blink_led)


