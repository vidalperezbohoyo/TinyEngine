#pragma once
#include "Arduino.h"
#include <functional>
#include "Melody.hpp"

namespace console
{

// Following values from https://github.com/robsoncouto/arduino-songs
enum class NoteDuration {
    WHOLE,      // (1)
    HALF,       // (1/2)
    QUARTER = 4,    // (1/4)
    EIGHTH = 8,     // (1/8)
    SIXTEENTH,  // (1/16)
    THIRTY_SECOND, // (1/32)
    SIXTY_FOURTH   // (1/64)
};

enum class SoundSource
{
    SIMPLE_TONE,
    MELODY
};

class Sound
{
private:
    /* data */
public:
    Sound();
    ~Sound();

    void check();

    void setPin(const int& buzzer_pin);

    void setCallback(std::function<void()> callback);

    void init();

    void play(unsigned int frequency, unsigned long int duration);

    void play(const int melody[], const int melody_array_size_bytes, bool repeat = false);

    void stop();
    
private:
    int buzzer_pin_; 
    bool playing_ = false; // When playing sound, no other sound can be played
    SoundSource source_;

    unsigned long int none_duration_;
    unsigned long int note_start_timestamp_; // Stores the millis() when the note starts to play to known when to stop
    
    const int* melody_; // Pointer to the playing array
    int melody_size_;
    int melody_cursor_ = 0; // Cursor to the current note in the melody
    bool melody_repeat_ = false; 
    bool melody_play_next_ = false;

    std::function<void()> done_callback_;


};
}