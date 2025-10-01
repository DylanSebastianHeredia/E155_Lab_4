// Sebastian Heredia
// dheredia@g.hmc.edu
// September 30, 2025
// FLAHS.c contains code to implement FLASH functions.

#include "FLASH.h"

void configureFlash() {
    FLASH->ACR |= (0b100); // Set to 4 waitstates
    FLASH->ACR |= (1 << 8); // Turn on the ART
}