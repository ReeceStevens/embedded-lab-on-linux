#include <stdint.h>

#include "../inc/tm4c123gh6pm.h"

void ssi_init(void);
uint8_t ssi_transfer(uint8_t data);
uint8_t read_register(uint8_t address);
