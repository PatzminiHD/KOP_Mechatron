#include <Arduino.h>
#include "../vars/constants.h"

class Buzzer
{
    public:
    enum Songs
    {
        TEST,
        ImperialMarch,
        NGGYU,
        Tetris,
    };

    void init()
    {
        ledcAttachPin(constants::pins::buzzer::buzzer_pin, constants::pins::buzzer::pwm_channel);
    }

    void PlaySong(Songs song)
    {
        switch(song)
        {
            case TEST:
                PlayTEST();
                break;

            case ImperialMarch:
                PlayImperialMarch();
                break;

            case NGGYU:
                PlayNGGYU();
                break;
                
            case Tetris:
                PlayTetris();
                break;
        }
        ledcWrite(constants::pins::buzzer::pwm_channel, 0);
    }

    private:

    struct noteEntry
    {
        note_t note;
        uint8_t octave;
        uint32_t duration;
    };

    struct freqEntry
    {
        uint32_t freq;
        uint16_t duration;
    };

    void PlayNote(uint8_t channel, note_t note, uint8_t octave, uint32_t duration)
    {
        if(note == NOTE_MAX)
        {
            delay(duration);
            return;
        }
        ledcWriteNote(channel, note, octave);
        delay(duration);
        ledcWrite(constants::pins::buzzer::pwm_channel, 0);
        delay(2);
    }
    void PlayFreq(uint8_t channel, uint32_t freq, uint16_t duration)
    {
        ledcWriteTone(channel, freq);
        delay(duration);
        ledcWrite(constants::pins::buzzer::pwm_channel, 0);
        delay(2);
    }

    void PlayTEST()
    {
        for (size_t i = 0; i < 8; i++)
        {
            PlayNote(constants::pins::buzzer::pwm_channel, songTEST[i].note, songTEST[i].octave, songTEST[i].duration);
        }
    }

    void PlayImperialMarch()
    {
        for (size_t i = 0; i < 18; i++)
        {
            PlayFreq(constants::pins::buzzer::pwm_channel, songImperialMarch[i].freq, songImperialMarch[i].duration);
        }
    }
    void PlayNGGYU()
    {
        for (size_t i = 0; i < 339; i++)
        {
            PlayNote(constants::pins::buzzer::pwm_channel, songNGGYU[i].note, songNGGYU[i].octave, songNGGYU[i].duration);
        }
    }

    void PlayTetris()
    {
        for (size_t i = 0; i < 99; i++)
        {
            PlayNote(constants::pins::buzzer::pwm_channel, songTetris[i].note, songTetris[i].octave, songTetris[i].duration);
        }
    }

    noteEntry songTetris[99]
    {
        //Whole Note: 1667
        {NOTE_E, 5, 417},
        {NOTE_B, 4, 208},
        {NOTE_C, 5, 208},
        {NOTE_D, 5, 417},
        {NOTE_C, 5, 208},
        {NOTE_B, 4, 208},
        {NOTE_A, 4, 417},
        {NOTE_A, 4, 208},
        {NOTE_C, 5, 208},
        {NOTE_E, 5, 417},
        {NOTE_D, 5, 208},
        {NOTE_C, 5, 208},
        {NOTE_B, 4, 625},
        {NOTE_C, 5, 208},
        {NOTE_D, 5, 417},
        {NOTE_E, 5, 417},
        {NOTE_C, 5, 417},
        {NOTE_A, 4, 417},
        {NOTE_A, 4, 208},
        {NOTE_A, 4, 417},
        {NOTE_B, 4, 208},
        {NOTE_C, 5, 208},
        {NOTE_D, 5, 625},
        {NOTE_F, 5, 208},
        {NOTE_A, 5, 417},
        {NOTE_G, 5, 208},
        {NOTE_F, 5, 208},
        {NOTE_E, 5, 625},
        {NOTE_C, 5, 208},
        {NOTE_E, 5, 417},
        {NOTE_D, 5, 208},
        {NOTE_C, 5, 208},
        {NOTE_B, 4, 417},
        {NOTE_B, 4, 208},
        {NOTE_C, 5, 208},
        {NOTE_D, 5, 417},
        {NOTE_E, 5, 417},
        {NOTE_C, 5, 417},
        {NOTE_A, 4, 417},
        {NOTE_A, 4, 417},
        {NOTE_MAX, 0, 417},
        {NOTE_E, 5, 417},
        {NOTE_B, 4, 208},
        {NOTE_C, 5, 208},
        {NOTE_D, 5, 417},
        {NOTE_C, 5, 208},
        {NOTE_B, 4, 208},
        {NOTE_A, 4, 417},
        {NOTE_A, 4, 208},
        {NOTE_C, 5, 208},
        {NOTE_E, 5, 417},
        {NOTE_D, 5, 208},
        {NOTE_C, 5, 208},
        {NOTE_B, 4, 625},
        {NOTE_C, 5, 208},
        {NOTE_D, 5, 417},
        {NOTE_E, 5, 417},
        {NOTE_C, 5, 417},
        {NOTE_A, 4, 417},
        {NOTE_A, 4, 208},
        {NOTE_A, 4, 417},
        {NOTE_B, 4, 208},
        {NOTE_C, 5, 208},
        {NOTE_D, 5, 625},
        {NOTE_F, 5, 208},
        {NOTE_A, 5, 417},
        {NOTE_G, 5, 208},
        {NOTE_F, 5, 208},
        {NOTE_E, 5, 625},
        {NOTE_C, 5, 208},
        {NOTE_E, 5, 417},
        {NOTE_D, 5, 208},
        {NOTE_C, 5, 208},
        {NOTE_B, 4, 417},
        {NOTE_B, 4, 208},
        {NOTE_C, 5, 208},
        {NOTE_D, 5, 417},
        {NOTE_E, 5, 417},
        {NOTE_C, 5, 417},
        {NOTE_A, 4, 417},
        {NOTE_A, 4, 417},
        {NOTE_MAX, 0, 417},
        {NOTE_E, 5, 834},
        {NOTE_C, 5, 834},
        {NOTE_D, 5, 834},
        {NOTE_B, 4, 834},
        {NOTE_C, 5, 834},
        {NOTE_A, 4, 834},
        {NOTE_Gs, 4, 834},
        {NOTE_B, 4, 417},
        {NOTE_MAX, 0, 208},
        {NOTE_E, 5, 834},
        {NOTE_C, 5, 834},
        {NOTE_D, 5, 834},
        {NOTE_B, 4, 834},
        {NOTE_C, 5, 417},
        {NOTE_E, 5, 417},
        {NOTE_A, 5, 834},
        {NOTE_Gs, 5, 834},
    };

    noteEntry songNGGYU[339]
    {
        //Whole Note: 2105
        {NOTE_D, 5, 789},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 526},
        {NOTE_E, 5, 789},
        {NOTE_Fs, 5, 789},
        {NOTE_A, 5, 132},
        {NOTE_G, 5, 132},
        {NOTE_Fs, 5, 263},
        {NOTE_D, 5, 789},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 1053},
        {NOTE_A, 4, 132},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 263},
        {NOTE_D, 5, 132},
        {NOTE_D, 5, 789},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 526},
        {NOTE_E, 5, 789},
        {NOTE_Fs, 5, 789},
        {NOTE_A, 5, 132},
        {NOTE_G, 5, 132},
        {NOTE_Fs, 5, 263},
        {NOTE_D, 5, 789},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 1053},
        {NOTE_A, 4, 132},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 263},
        {NOTE_D, 5, 132},
        {NOTE_MAX, 0, 526},
        {NOTE_B, 4, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_Cs, 5, 394},
        {NOTE_B, 4, 132},
        {NOTE_A, 4, 1053},
        {NOTE_MAX, 0, 526},
        {NOTE_MAX, 0, 263},
        {NOTE_B, 4, 263},
        {NOTE_B, 4, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_B, 4, 526},
        {NOTE_A, 4, 263},
        {NOTE_A, 5, 263},
        {NOTE_MAX, 0, 263},
        {NOTE_A, 5, 263},
        {NOTE_E, 5, 789},
        {NOTE_MAX, 0, 526},
        {NOTE_B, 4, 263},
        {NOTE_B, 4, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_D, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_MAX, 0, 263},
        {NOTE_MAX, 0, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 789},
        {NOTE_MAX, 0, 526},
        {NOTE_MAX, 0, 263},
        {NOTE_B, 4, 263},
        {NOTE_B, 4, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 526},
        {NOTE_E, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_Fs, 5, 263},
        {NOTE_E, 5, 526},
        {NOTE_MAX, 0, 526},
        {NOTE_D, 5, 1053},
        {NOTE_E, 5, 263},
        {NOTE_Fs, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_Fs, 5, 263},
        {NOTE_E, 5, 526},
        {NOTE_A, 4, 526},
        {NOTE_MAX, 0, 1053},
        {NOTE_B, 4, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_MAX, 0, 263},
        {NOTE_E, 5, 263},
        {NOTE_Fs, 5, 263},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_Fs, 5, 394},
        {NOTE_Fs, 5, 394},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_E, 5, 394},
        {NOTE_E, 5, 394},
        {NOTE_D, 5, 394},
        {NOTE_Cs, 5, 132},
        {NOTE_B, 4, 394},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 526},
        {NOTE_E, 5, 263},
        {NOTE_Cs, 5, 394},
        {NOTE_B, 4, 132},
        {NOTE_A, 4, 263},
        {NOTE_A, 4, 263},
        {NOTE_A, 4, 263},
        {NOTE_E, 5, 526},
        {NOTE_D, 5, 1053},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_Fs, 5, 394},
        {NOTE_Fs, 5, 394},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_A, 5, 526},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 394},
        {NOTE_Cs, 5, 132},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 526},
        {NOTE_E, 5, 263},
        {NOTE_Cs, 5, 394},
        {NOTE_B, 4, 132},
        {NOTE_A, 4, 526},
        {NOTE_A, 4, 263},
        {NOTE_E, 5, 526},
        {NOTE_D, 5, 1053},
        {NOTE_MAX, 0, 526},
        {NOTE_MAX, 0, 263},
        {NOTE_B, 4, 263},
        {NOTE_D, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_D, 5, 263},
        {NOTE_E, 5, 526},
        {NOTE_MAX, 0, 263},
        {NOTE_MAX, 0, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 789},
        {NOTE_MAX, 0, 526},
        {NOTE_MAX, 0, 263},
        {NOTE_B, 4, 263},
        {NOTE_B, 4, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 526},
        {NOTE_MAX, 0, 263},
        {NOTE_A, 5, 263},
        {NOTE_A, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_Fs, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_MAX, 0, 263},
        {NOTE_A, 4, 263},
        {NOTE_B, 4, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_MAX, 0, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 789},
        {NOTE_MAX, 0, 526},
        {NOTE_B, 4, 263},
        {NOTE_B, 4, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 526},
        {NOTE_MAX, 0, 263},
        {NOTE_MAX, 0, 263},
        {NOTE_E, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_Fs, 5, 526},
        {NOTE_E, 5, 789},
        {NOTE_D, 5, 1053},
        {NOTE_D, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_Fs, 5, 263},
        {NOTE_E, 5, 526},
        {NOTE_E, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_Fs, 5, 263},
        {NOTE_E, 5, 263},
        {NOTE_A, 4, 263},
        {NOTE_A, 4, 526},
        {NOTE_MAX, 0, 789},
        {NOTE_A, 4, 263},
        {NOTE_B, 4, 263},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 263},
        {NOTE_B, 4, 263},
        {NOTE_MAX, 0, 263},
        {NOTE_E, 5, 263},
        {NOTE_Fs, 5, 263},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_Fs, 5, 394},
        {NOTE_Fs, 5, 394},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_E, 5, 394},
        {NOTE_E, 5, 394},
        {NOTE_D, 5, 394},
        {NOTE_Cs, 5, 132},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 526},
        {NOTE_E, 5, 263},
        {NOTE_Cs, 5, 394},
        {NOTE_B, 4, 132},
        {NOTE_A, 4, 526},
        {NOTE_A, 4, 263},
        {NOTE_E, 5, 526},
        {NOTE_D, 5, 1053},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_Fs, 5, 394},
        {NOTE_Fs, 5, 394},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_A, 5, 526},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 394},
        {NOTE_Cs, 5, 132},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 526},
        {NOTE_E, 5, 263},
        {NOTE_Cs, 5, 394},
        {NOTE_B, 4, 132},
        {NOTE_A, 4, 526},
        {NOTE_A, 4, 263},
        {NOTE_E, 5, 526},
        {NOTE_D, 5, 1053},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_Fs, 5, 394},
        {NOTE_Fs, 5, 394},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_A, 5, 526},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 394},
        {NOTE_Cs, 5, 132},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 526},
        {NOTE_E, 5, 263},
        {NOTE_Cs, 5, 394},
        {NOTE_B, 4, 132},
        {NOTE_A, 4, 526},
        {NOTE_A, 4, 263},
        {NOTE_E, 5, 526},
        {NOTE_D, 5, 1053},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_Fs, 5, 394},
        {NOTE_Fs, 5, 394},
        {NOTE_E, 5, 789},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_A, 5, 526},
        {NOTE_Cs, 5, 263},
        {NOTE_D, 5, 394},
        {NOTE_Cs, 5, 132},
        {NOTE_B, 4, 263},
        {NOTE_A, 4, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 132},
        {NOTE_B, 4, 132},
        {NOTE_D, 5, 526},
        {NOTE_E, 5, 263},
        {NOTE_Cs, 5, 394},
        {NOTE_B, 4, 132},
        {NOTE_A, 4, 526},
        {NOTE_A, 4, 263},
        {NOTE_E, 5, 526},
        {NOTE_D, 5, 1053},
    };

    noteEntry songTEST[8]
    {
        {NOTE_C, 4, 250},
        {NOTE_D, 4, 250},
        {NOTE_E, 4, 250},
        {NOTE_F, 4, 250},
        {NOTE_G, 4, 250},
        {NOTE_A, 4, 250},
        {NOTE_B, 4, 250},
        {NOTE_C, 5, 250},
    };

    freqEntry songImperialMarch[18]
    {
        {440, 400},
        {440, 400},
        {440, 400},
        {349, 300},
        {349, 300},
        {523, 100},
        {440, 400},
        {523, 100},
        {440, 800},
        {659, 400},
        {659, 400},
        {659, 400},
        {698, 300},
        {523, 100},
        {523, 100},
        {415, 400},
        {349, 300},
        {440, 800},
    };

    
};