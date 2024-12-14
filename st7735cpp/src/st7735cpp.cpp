#include "st7735cpp.hpp"

#include <pico/stdlib.h>
#include <hardware/spi.h>
#include <unordered_map>
#include <array>

namespace
{
    constexpr int SPI_SPEED = 10000000; // SPI speed (10 MHz)

    // SPI 01 settings for PICO
    spi_inst_t &SPI_PORT_REF = *spi0;
    const uint8_t PIN_CS = 17;
    const uint8_t PIN_RESET = 18;
    const uint8_t PIN_DC = 19;
    const uint8_t PIN_SCK = 14;
    const uint8_t PIN_MOSI = 15;

    // A simple 5x8 font for the character "C" (example binary representation)
    constexpr int CHAR_WIDTH = 5;
    constexpr int CHAR_HEIGHT = 8;
    using CharBitmap = std::array<uint8_t, CHAR_HEIGHT>;
    const uint8_t font_C[8] = {
        0x3E, // 00111110
        0x63, // 01100011
        0x60, // 01100000
        0x60, // 01100000
        0x60, // 01100000
        0x63, // 01100011
        0x3E, // 00111110
        0x00  // Padding
    };

    std::unordered_map<char, CharBitmap> map_char_to_data = {
        {'C', {0b01110, 0b10001, 0b10000, 0b10000, 0b10000, 0b10001, 0b01110, 0b00000}}};
}

namespace st7735cpp
{

    // Function to initialize SPI for TFT
    void init_spi()
    {
        spi_init(&SPI_PORT_REF, SPI_SPEED);         // Initialize SPI with speed
        gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);  // Set GPIO for SPI SCK
        gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI); // Set GPIO for SPI MOSI
        gpio_init(PIN_CS);                          // Chip Select
        gpio_set_dir(PIN_CS, GPIO_OUT);
        gpio_init(PIN_RESET); // Reset pin
        gpio_set_dir(PIN_RESET, GPIO_OUT);
        gpio_init(PIN_DC); // Data/Command pin
        gpio_set_dir(PIN_DC, GPIO_OUT);

        gpio_put(PIN_CS, 1); // Ensure CS is high at the start
    }

    void TftScreen::write_command(unsigned char cmd)
    {
        gpio_put(PIN_DC, 0); // DC = 0 for command
        gpio_put(PIN_CS, 0); // Select the screen
        spi_write_blocking(&SPI_PORT_REF, &cmd, 1);
        gpio_put(PIN_CS, 1); // Deselect the screen
    }

    void TftScreen::write_data(uint8_t *data, size_t len)
    {
        gpio_put(PIN_DC, 1); // Data mode
        gpio_put(PIN_CS, 0); // Select display
        spi_write_blocking(spi0, data, len);
        gpio_put(PIN_CS, 1); // Deselect display
    }

    void TftScreen::init()
    {
        init_spi();
        reset();

        // Initialization command
    }

    void TftScreen::fill(uint16_t color)
    {
        uint16_t w = 128;
        uint16_t h = 160;
        set_address_window(Rect<uint16_t>{0, 0, w, h});
        uint16_t colorBuffer[w * h];
        for (int i = 0; i < w * h; i++)
        {
            colorBuffer[i] = color;
        }
        write_data((uint8_t *)colorBuffer, sizeof(colorBuffer));
    }

    void TftScreen::reset()
    {
        gpio_put(PIN_RESET, 0); // Reset the screen
        sleep_ms(50);           // Hold reset for 50ms
        gpio_put(PIN_RESET, 1); // Release reset
        sleep_ms(150);          // Wait for the screen to initialize
    }

    void TftScreen::set_address_window(Rect<uint16_t> rect)
    {
        write_command(0x2A); // CASET (Column Address Set)
        uint8_t data_x[4] = {static_cast<uint8_t>((rect.x >> 8) & 0xFF),
                             static_cast<uint8_t>(rect.x & 0xFF),
                             static_cast<uint8_t>(((rect.x + rect.w - 1) >> 8) & 0xFF),
                             static_cast<uint8_t>((rect.x + rect.w - 1) & 0xFF)};
        write_data(data_x, 4);

        write_command(0x2B); // RASET (Row Address Set)
        uint8_t data_y[4] = {static_cast<uint8_t>((rect.y >> 8) & 0xFF),
                             static_cast<uint8_t>(rect.y & 0xFF),
                             static_cast<uint8_t>(((rect.y + rect.h - 1) >> 8) & 0xFF),
                             static_cast<uint8_t>((rect.y + rect.h - 1) & 0xFF)};
        write_data(data_y, 4);

        write_command(0x2C); // RAMWR (Write to RAM)
    }

    // Draw a single character using the font array
    void TftScreen::draw_char(uint16_t x, uint16_t y, const char letter, uint16_t color, uint16_t bg)
    {
        if (auto it = map_char_to_data.find(letter); it != map_char_to_data.end())
        {
            auto data = it->second;
            set_address_window(Rect<uint16_t>{x, y, 5, 8}); // 5x8 character

            for (uint8_t row = 0; row < 8; row++)
            {
                uint8_t pixels = data[row];
                for (uint8_t col = 0; col < 5; col++)
                {
                    uint16_t pixel_color = (pixels & (1 << (4 - col))) ? color : bg;
                    uint8_t pixel_data[2] = {static_cast<uint8_t>(pixel_color >> 8),
                                             static_cast<uint8_t>(pixel_color & 0xFF)};
                    write_data(pixel_data, 2);
                }
            }
        }
    }

} // namespace st7735cpp