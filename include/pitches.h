#ifndef PITCHES_H
#define PITCHES_H

// Calculation for ATmega328P @ 16MHz
// Formula: OCR1A = (F_CPU / (2 * Prescaler * Frequency)) - 1
// Prescaler (N) = 8

#define NOTE_C4  3821 // C (261.63 Hz)
#define NOTE_D4  3404 // D (293.66 Hz)
#define NOTE_E4  3032 // E (329.63 Hz)
#define NOTE_F4  2862 // F (349.23 Hz)
#define NOTE_G4  2550 // G (392.00 Hz)
#define NOTE_A4  2271 // A (440.00 Hz)
#define NOTE_B4  2023 // B (493.88 Hz)

#endif