#include "Sound.hpp"

using namespace console;

Sound::Sound()
{

}

Sound::~Sound()
{

}

void Sound::setPin(const int& buzzer_pin)
{
    buzzer_pin_ = buzzer_pin;
}

void Sound::init()
{
    pinMode(buzzer_pin_, OUTPUT);
}

void Sound::setCallback(std::function<void()> callback)
{
    done_callback_ = callback;
}

void Sound::check()
{
    if (playing_)
    {
        unsigned long int now = millis();

        if (source_ == SoundSource::SIMPLE_TONE)
        {
            // Check when to stop
            if (now - none_duration_ > note_start_timestamp_)
            {
                noTone(buzzer_pin_);
                playing_ = false;

                if (done_callback_)
                {
                    done_callback_();
                }
                
            }
        }
        else
        {
            // Source is melody

            // Melody is coded as [NOTE1, duration1, NOTE2, duration2]
            // Duration is a divider:
            // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
            // negative numbers are used to represent dotted notes

            if (melody_play_next_)
            {
                // When note must be updated

                const int tempo = 120; // Change this to make it faster or slower

                const int wholenote = (60000 * 4) / tempo; // Duration of whole note in ms

                // Calculate the duration of each note
                int divider = melody_[melody_cursor_ + 1];

                if (divider > 0)
                {
                    none_duration_ = (wholenote) / divider; // regular note, just proceed
                } 
                else if (divider < 0) 
                {
                    none_duration_ = (wholenote) / abs(divider);
                    none_duration_ *= 1.5; // increases the duration in half for dotted notes
                }
                
                note_start_timestamp_ = millis();
                tone(buzzer_pin_, melody_[melody_cursor_]);

                melody_play_next_ = false;
            }
            else
            {
                if (now - none_duration_ > note_start_timestamp_)
                {
                    // Note done
                    if (melody_cursor_ + 2 == melody_size_)
                    {
                        // Last note done
                        noTone(buzzer_pin_);
                        playing_ = false;

                        if (done_callback_)
                        {
                            done_callback_();
                        }
                    }
                    else
                    {
                        // Increment cursor
                        melody_cursor_ += 2;
                        melody_play_next_ = true;
                    }
                }
            }
        }
    }
}

void Sound::play(unsigned int frequency, unsigned long int duration)
{
    source_ = SoundSource::SIMPLE_TONE;
    none_duration_ = duration;
    note_start_timestamp_ = millis();
    playing_ = true;

    tone(buzzer_pin_, frequency);
}

void Sound::play(const int melody[], const int melody_array_size_bytes, bool repeat)
{
    source_ = SoundSource::MELODY;
    melody_repeat_ = repeat;
    playing_ = true;

    melody_ = melody;
    melody_size_ = melody_array_size_bytes / sizeof(int);
    melody_cursor_ = 0; // Start
    melody_play_next_ = true;
}

void Sound::stop()
{
    noTone(buzzer_pin_);
    playing_ = false;
}