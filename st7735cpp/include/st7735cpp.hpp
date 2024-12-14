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
        // Define RGB565 colors using inline constexpr
        inline constexpr uint16_t kBlack = 0x0000;       // RGB(0, 0, 0)
        inline constexpr uint16_t kWhite = 0xFFFF;       // RGB(255, 255, 255)
        inline constexpr uint16_t kRed = 0xF800;         // RGB(255, 0, 0)
        inline constexpr uint16_t kGreen = 0x07E0;       // RGB(0, 255, 0)
        inline constexpr uint16_t kBlue = 0x001F;        // RGB(0, 0, 255)
        inline constexpr uint16_t kCyan = 0x07FF;        // RGB(0, 255, 255)
        inline constexpr uint16_t kMagenta = 0xF81F;     // RGB(255, 0, 255)
        inline constexpr uint16_t kYellow = 0xFFE0;      // RGB(255, 255, 0)
        inline constexpr uint16_t kGray = 0x8410;        // RGB(128, 128, 128)
        inline constexpr uint16_t kOrange = 0xFC00;      // RGB(255, 165, 0)
        inline constexpr uint16_t kPurple = 0x8010;      // RGB(128, 0, 128)
        inline constexpr uint16_t kPink = 0xF81F;        // RGB(255, 182, 193)
        inline constexpr uint16_t kBrown = 0xBBCA;       // RGB(165, 42, 42)
        inline constexpr uint16_t kLightBlue = 0x5DFF;   // RGB(135, 206, 250)
        inline constexpr uint16_t kCustomColor = 0x7A9F; // RGB(100, 150, 200)

    }

    class TftScreen
    {
    public:
        void init();
        void draw_char(uint16_t x, uint16_t y, const char letter, uint16_t color, uint16_t bg);
        void fill(uint16_t color);

    private:
        void reset();
        void write_command(unsigned char cmd);
        void write_data(uint8_t *data, size_t len);
        void set_address_window(Rect<uint16_t> rect);
    };
}

#endif
