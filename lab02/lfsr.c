#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

#define MAX_uint16_t 65535

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
        uint16_t temp_bit = 1;
        uint16_t new_bit = 1;
        new_bit &= *reg;
        temp_bit &= (*reg)>>2;
        new_bit ^= temp_bit;
        temp_bit = 1;
        temp_bit &= (*reg)>>3;
        new_bit ^= temp_bit;
        temp_bit = 1;
        temp_bit &=  (*reg)>>5;
        new_bit ^= temp_bit;

        *reg = *reg >> 1;
        *reg = *reg + (new_bit<<15);
    

}

