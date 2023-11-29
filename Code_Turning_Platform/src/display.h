#include <LiquidCrystal_I2C.h>
#include <ArduinoSTL.h>
//#include <List.hpp>
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
            if(cursorPos < 4)
            {
                Serial.println("Cursor Pos= " + (String)cursorPos + " < 4");
                Serial.println("menuEntries Size = " + (String)menuEntries.size());
                
                for (uint8_t i = 0; i < 4; i++)
                {
                    if(i < menuEntries.size())
                    {
                        lines[i] = menuEntries[i];
                    }
                    else
                    {
                        lines[i] = "";
                    }
                    Serial.println("Line" + (String)i + " = " + lines[i]);
                }
            }
            else
            {
                Serial.println("Cursor Pos= " + (String)cursorPos + " >= 4");
                uint8_t tmp = 0;
                for (uint8_t i = cursorPos; i < cursorPos + 4; i++)
                {
                    if(i < menuEntries.size())
                        lines[tmp] = menuEntries[i];
                    else
                        lines[tmp] = "";
                    tmp++;
                }
                
            }
            for (uint8_t i = 0; i < 4; i++)
            {
                if(linesPrev[i] != lines[i])
                {
                    lcd.setCursor(1, i);
                    lcd.print(lines[i].substring(0, 19));
                    for (uint8_t i = lines[i].length(); i < 20; i++)
                    {
                        lcd.print(" ");
                    }
                    linesPrev[i] = lines[i];
                }
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
                if(cursorPos < 4)
                    lcd.setCursor(0, cursorPos);
                else
                    lcd.setCursor(0, 3);
                lcd.write(0);
                cursorPosPrev = cursorPos;
            }
        }

        String linesPrev[4];
        uint8_t cursorPosPrev;
    public:
        std::vector<String> menuEntries;
        String lines[4];
        uint8_t cursorPos;
        Display()
        {
            cursorPos = 0;
            cursorPosPrev = 1;

            menuEntries.clear();
        }

        void UpdateInt(size_t * variable, uint8_t stepSize, String varName)
        {
            Clear();
            lines[0] = "  Update  Variable  ";
            lines[1] = "--------------------";
            lines[3] = varName + " = " + (String)*variable;
        }

        void init()
        {
            lcd.init();
            lcd.backlight();
            lcd.createChar(0, Cursor);
        }

        void Clear()
        {
            //menuEntries.clear();
            Update();
        }

        void Update()
        {
            /*if(cursorPos > menuEntries.getSize() - 1)
            {
                cursorPos = menuEntries.getSize() - 1;
            }*/

            if(cursorPos < 4)
            {
                
            }

            UpdateDisplay();
        }
};