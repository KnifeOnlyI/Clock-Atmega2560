#include "header/display.hpp"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

U8G2_SSD1306_128X64_NONAME_F_HW_I2C getDisplay() {
    return u8g2;
}

void displayBegin()
{
    u8g2.begin();
}

void displayPrepare()
{
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
}