#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

byte Cursor[] = {
  0b01000,
  0b00100,
  0b00010,
  0b11111,
  0b00010,
  0b00100,
  0b01000,
  0b00000
};

class Display
{
    private:
        void UpdateDisplay()
        {
            if(line0prev != line0)
            {
                lcd.setCursor(1, 0);
                lcd.print(line0.substring(0, 19));
                for (uint8_t i = line0.length(); i < 20; i++)
                {
                    lcd.print(" ");
                }
                line0prev = line0;
            }
            if(line1prev != line1)
            {
                lcd.setCursor(1, 1);
                lcd.print(line1.substring(0, 19));
                for (uint8_t i = line1.length(); i < 20; i++)
                {
                    lcd.print(" ");
                }
                line1prev = line1;
            }
            if(line2prev != line2)
            {
                lcd.setCursor(1, 2);
                lcd.print(line2.substring(0, 19));
                for (uint8_t i = line2.length(); i < 20; i++)
                {
                    lcd.print(" ");
                }
                line2prev = line2;
            }
            if(line3prev != line3)
            {
                lcd.setCursor(1, 3);
                lcd.print(line3.substring(0, 19));
                for (uint8_t i = line3.length(); i < 20; i++)
                {
                    lcd.print(" ");
                }
                line3prev = line3;
            }
            if(cursorPosPrev != cursorPos)
            {
                lcd.setCursor(0, 0);
                lcd.print(" ");
                lcd.setCursor(0, 1);
                lcd.print(" ");
                lcd.setCursor(0, 2);
                lcd.print(" ");
                lcd.setCursor(0, 3);
                lcd.print(" ");
                lcd.setCursor(0, cursorPos);
                lcd.write(0);
                cursorPosPrev = cursorPos;
            }
        }

        String line0prev, line1prev, line2prev, line3prev;
        uint8_t cursorPosPrev;
    public:
        String line0, line1, line2, line3;
        uint8_t cursorPos;
        Display()
        {
            cursorPos = 0;
            cursorPosPrev = 1;

            line0 = "";
            line1 = "";
            line2 = "";
            line3 = "";
            line0prev = " ";
            line1prev = " ";
            line2prev = " ";
            line3prev = " ";
        }

        void init()
        {
            lcd.init();
            lcd.backlight();
            lcd.createChar(0, Cursor);
        }

        void Update()
        {
            UpdateDisplay();
        }
};