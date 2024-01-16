#include "rotary_encoder/rotary_encoder.h"
#include <LiquidCrystal_I2C.h>
#include <ArduinoSTL.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
RotaryEncoder rotaryEncoder;

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

struct DisplayEntry
{
    String line;
    void (*func)(void);
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
                        lines[i] = menuEntries[i].line;
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
                for (uint8_t i = cursorPos - 3; i < cursorPos + 1; i++)
                {
                    if(i < menuEntries.size())
                        lines[tmp] = menuEntries[i].line;
                    else
                        lines[tmp] = "";
                    tmp++;
                }
                
            }
            UpdateLines();
        }

        void UpdateLines()
        {
            for (uint8_t i = 0; i < 4; i++)
            {
                lcd.setCursor(1, i);
                lcd.print(lines[i].substring(0, 19));
                for (uint8_t j = lines[i].length(); j < 19; j++)
                {
                    lcd.print(" ");
                }
            }

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

        uint8_t cursorPosPrev;
    public:
        std::vector<DisplayEntry> menuEntries;
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
            Serial.println("Update Int");
            Clear();
            cursorPos = 3;
            lines[0] = "  Update  Variable  ";
            lines[1] = "--------------------";
            rotaryEncoder.buttonPressed = false;
            while(!rotaryEncoder.buttonPressed)
            {
                Serial.println("Update Loop");
                lines[3] = varName + " = " + (String)*variable;
                UpdateLines();
                while(rotaryEncoder.movesToMake == 0 && !rotaryEncoder.buttonPressed) { ; }
                Serial.println("Changed");
                variable += rotaryEncoder.movesToMake * stepSize;
                rotaryEncoder.movesToMake = 0;
            }
            rotaryEncoder.buttonPressed = false;
        }

        void init()
        {
            lcd.init();
            lcd.backlight();
            lcd.createChar(0, Cursor);
            rotaryEncoder.init(2, 4, 3);
        }

        void loop()
        {
            if(RotaryEncoder::movesToMake != 0)
            {
                if(RotaryEncoder::movesToMake < 0 && cursorPos + RotaryEncoder::movesToMake >= 0)
                {
                    cursorPos += RotaryEncoder::movesToMake;
                    Update();
                }
                else if (RotaryEncoder::movesToMake > 0)
                {
                    cursorPos += RotaryEncoder::movesToMake;
                    Update();
                }
                RotaryEncoder::movesToMake = 0;
                delay(2);
            }

            if(RotaryEncoder::buttonPressed)
            {
                RotaryEncoder::buttonPressed = false;
                menuEntries[cursorPos].func();
                delay(2);
            }
        }

        void Clear()
        {
            cursorPos = 0;
            menuEntries.clear();
            Update();
        }

        void Update()
        {
            if(cursorPos > menuEntries.size() - 1)
            {
                cursorPos = menuEntries.size() - 1;
            }
            UpdateDisplay();
        }
};