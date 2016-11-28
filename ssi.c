#include <stdint.h>

#include "../inc/tm4c123gh6pm.h"

void ssi_init(void) {
  SYSCTL_RCGCSSI_R |= 0x02;  // activate SSI1
  SYSCTL_RCGCGPIO_R |= 0x08; // activate port D
  while((SYSCTL_PRGPIO_R&0x08)==0x00){}; // allow time for clock to start

  GPIO_PORTD_AFSEL_R |= 0x0F;           // enable alt funct on PD0,1,2,3
  GPIO_PORTD_DEN_R |= 0x0F;             // enable digital I/O on PD0,1,2,3
                                        // configure PD0,1,2,3 as SSI
  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xFFFF0000)+0x00002222;
  GPIO_PORTD_AMSEL_R &= ~(0x0F);          // disable analog functionality on PD
  SSI1_CR1_R = 0x00000000;
  /* SSI1_CR1_R &= ~SSI_CR1_SSE; */
  /* SSI1_CR1_R &= ~SSI_CR1_MS; */
  SSI1_CPSR_R = 0x02;
  /* SSI1_CPSR_R = (SSI1_CPSR_R&~SSI_CPSR_CPSDVSR_M) + 8; */
  /* SSI1_CR0_R &= ~(0x0000FFF0); */
  SSI1_CR0_R &= ~(SSI_CR0_SCR_M);
  SSI1_CR0_R |= (SSI_CR0_SPH | SSI_CR0_SPO); // CPHA=1, CPOL=1
  SSI1_CR0_R = (SSI1_CR0_R&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO;
  SSI1_CR0_R = (SSI1_CR0_R&~SSI_CR0_DSS_M)+SSI_CR0_DSS_8;
  SSI1_DR_R = 0x0000;
  SSI1_CR1_R |= 0x00000002;
  /* SSI1_CR1_R |= SSI_CR1_SSE; */

}

uint8_t ssi_transfer(uint8_t data) {
    /* while((SSI1_SR_R&0x00000002)==0){}; */
    while((SSI1_SR_R&0x2)==0){};
    SSI1_DR_R = data;
    while((SSI1_SR_R & SSI_SR_RNE) == 0) {};
    return SSI1_DR_R;
}
