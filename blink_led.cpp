#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "st7735cpp.hpp" // Include the ST7735 library (you can find this in Pico SDK or online)

int main()
{
    stdio_init_all(); // Initialize standard I/O (for debugging via USB)

    auto screen = st7735cpp::TftScreen();
    screen.init();
    screen.draw_char(1, 1, 'C', st7735cpp::color::kBlue, st7735cpp::color::kBlack);

    while (1)
    {
        sleep_ms(1000); // Sleep for a while
    }

    return 0;
}
