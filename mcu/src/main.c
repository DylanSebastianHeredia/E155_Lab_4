// Sebastian Heredia
// dheredia@g.hmc.edu
// September 28, 2025
// main.c contains starter code to play Fur Elise and Blue.

#include "../lib/TIM.h"
#include "RCC.h"
#include "TIM.h"

#include "fur_elise.h"
#include "blue.h"

int main(void) {
    // configureFlash();
    configureClock();	
    
    // Number of notes in Blue
    // int notes_in_blue = sizeof(blue_notes) / sizeof(blue_notes[0]);

    // Fur Elise
    int i = 0;
    
    while (fur_elise_notes[i][1] != 0) {
        PWM(fur_elise_notes[i][0]);             // Frequency
        delay_millis(fur_elise_notes[i][1]);    // Duration
        i++;
    }

    // Stop for 1 second
    PWM(0);
    delay_millis(1000);

    // Blue (Da Ba Dee)
    i = 0;                                      // Reset, not redeclared
    while (blue_notes[i][1] != 0) {
        PWM(blue_notes[i][0]);
        delay_millis(blue_notes[i][1]);
        i++;
    }

    PWM(0);
}

