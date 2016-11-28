/*
 * Blinky -- Template project for Tiva Launchpad
 */

#include <stdio.h>
#include <stdint.h>

#include "inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "UART.h"
#include "ST7735.h"

#define PF1                     (*((volatile uint32_t *)0x40025008))
#define PF2                     (*((volatile uint32_t *)0x40025010))

#define DELAY_TIME 200000

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

void PortF_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x20;        // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20)==0){}; // allow time for clock to start
  GPIO_PORTF_DIR_R |= 0x06;             // make PF2, PF1 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x06;          // disable alt funct on PF2, PF1
  GPIO_PORTF_DEN_R |= 0x06;             // enable digital I/O on PF2, PF1
                                        // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF00F)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;               // disable analog functionality on PF

  PF2 = 0;                      // turn off LED
}

int main() {
    PLL_Init(Bus80MHz);
    UART_Init();
    printf("Hello, world! Time to blink!\n\n");
    volatile uint32_t delay;
    while(1) {
        PF2 ^= 0x04;
        for(delay = 0; delay < DELAY_TIME; delay++){}
    }
}
