
# Add the library
add_library(st7735cpp
    src/st7735cpp.cpp
)
target_compile_features(st7735cpp PUBLIC cxx_std_20)


# Specify include directories for the library
target_include_directories(st7735cpp PUBLIC include)

# Link Pico SDK libraries to your library
target_link_libraries(st7735cpp pico_stdlib hardware_spi)