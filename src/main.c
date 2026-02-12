#include <avr/io.h>
#include "pitches.h"

// Pin definitions
#define BUZZER_PIN  PB1  // Digital Pin 9 (Buzzer) (OC1A)
#define BUTTON_C    PC0  // A0 (Button) (Port C)
#define BUTTON_D    PC1  // A1 (Button) (Port C)
#define BUTTON_E    PC2  // A2 (Button) (Port C)
#define BUTTON_F    PC3  // A3 (Button) (Port C)
#define BUTTON_G    PC4  // A4 (Button) (Port C)
#define BUTTON_A    PC5  // A5 (Button) (Port C)
#define BUTTON_B    PD2  // Digital Pin 2 (Button) (Port D)

// Timer 1 Abstraction (Registers and Bits)
#define TIMER_CONTROL_A   TCCR1A  // Control Register A
#define TIMER_CONTROL_B   TCCR1B  // Control Register B
#define SPEAKER_TOGGLE    COM1A0  // Toggle Output on Compare Match
#define CTC_MODE          WGM12   // Clear Timer on Compare Match
#define PRESCALER_8       CS11    // Clock Select: Prescaler = 8
#define COMPARE_REGISTER  OCR1A   // Register to set the note frequency

typedef enum 
{
    SILENCE, // No sound output
    PLAYING // Sound output active
} SynthState;

void setup_hardware (void) 
{
    // ----- GPIO Configuration -----

    // Set Digital Pin 9 as output
    DDRB |= (1 << BUZZER_PIN); 
    
    // Enable internal pull-up resistors for Port C buttons (A0-A5)
    PORTC |= (1 << BUTTON_C) | (1 << BUTTON_D) | (1 << BUTTON_E) | (1 << BUTTON_F) | (1 << BUTTON_G) | (1 << BUTTON_A); 
    
    // Enable internal pull-up resistor for Port D button (Digital Pin 2)
    PORTD |= (1 << BUTTON_B);



    // ----- Timer 1 Configuration -----

    // Initialize Timer 1 in CTC mode with a prescaler of 8
    TIMER_CONTROL_B |= (1 << CTC_MODE) | (1 << PRESCALER_8);
    
    // Ensure the output compare register is initialized to 0
    COMPARE_REGISTER = 0;

    // NOTE: TIMER_CONTROL_A is kept at 0 to keep the speaker silent at startup
}

int main (void)
{
    setup_hardware ();

    // Declare the state variable
    SynthState mode;

    // Keep track of the previous note
    uint16_t last_note = 0;

    while (1)
    {
        // ----- Reset state for this loop iteration -----

        uint16_t current_note = 0;
        mode = SILENCE;



        // ----- Polling: Check which button is pressed -----

        // C4
        if (!(PINC & (1 << BUTTON_C))) 
        { 
            current_note = NOTE_C4;
            mode = PLAYING; 
        }
        
        // D4
        else if (!(PINC & (1 << BUTTON_D))) 
        {
            current_note = NOTE_D4; 
            mode = PLAYING;
        }
            
        // E4
        else if (!(PINC & (1 << BUTTON_E))) 
        {
            current_note = NOTE_E4;
            mode = PLAYING;
        }

        // F4
        else if (!(PINC & (1 << BUTTON_F))) 
        {
            current_note = NOTE_F4;
            mode = PLAYING;
        }

        // G4
        else if (!(PINC & (1 << BUTTON_G))) 
        {
            current_note = NOTE_G4; 
            mode = PLAYING;
        }

        // A4
        else if (!(PINC & (1 << BUTTON_A))) 
        { 
            current_note = NOTE_A4; 
            mode = PLAYING;
        }

        // B4
        else if (!(PIND & (1 << BUTTON_B))) 
        {
            current_note = NOTE_B4; 
            mode = PLAYING;
        }



        // ------ Execution: Apply the state to the hardware

        // Update frequency and connect the buzzer
        if (mode == PLAYING)
        {
            if (current_note != last_note)
            {
                COMPARE_REGISTER = current_note;
                TCNT1 = 0; // Reset the timer counter to start the new note immediately
                TIMER_CONTROL_A |= (1 << SPEAKER_TOGGLE);
            }
            
            last_note = current_note;
        }
        
        // Disconnect the buzzer (silence)
        else
        {
            if (last_note != 0)
            {
                TIMER_CONTROL_A &= ~(1 << SPEAKER_TOGGLE);
                last_note = 0;
            }
        }   
    }   
}