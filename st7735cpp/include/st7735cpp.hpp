#ifndef ST7735CPP
#define ST7735CPP

#include <pico/stdlib.h>
#include <concepts>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
struct Rect
{
    static_assert(std::is_arithmetic<T>::value, "Template type must be numeric");
    T x;
    T y;
    T w;
    T h;
};

namespace st7735cpp
{

    namespace color
    {
        inline constexpr int kBlack = 0x0000;
        inline constexpr int kBlue = 0xF800;
    }

    class TftScreen
    {
    public:
        void init();
        void draw_char(uint16_t x, uint16_t y, const uint8_t *char_data, uint16_t color, uint16_t bg);

    private:
        void reset();
        void write_command(unsigned char cmd);
        void write_data(uint8_t *data, size_t len);
        void set_address_window(Rect<uint16_t> rect);
    };
}

#endif
