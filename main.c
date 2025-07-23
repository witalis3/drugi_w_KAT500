/*
 * File:   main.c
 * Author: George.Nikolaidis
 *
 * Created on Mar 09, 2022, 18:00 PM
 */

// PIC12F615 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select (8 MHz)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 8000000
#define DISABLE_PWM_Service()               (CCP1CON = 0x0)

void SYSTEM_Initialize()
{
    /* CONFIGURATION OF GPIO
     * INPUTs (BAND DATA):
     * GP0 BAND2
     * GP1 BAND3
     * GP2 BAND1
     * GP4 BAND0
     * OUTPUT:
     * GP5 - sygnał WAKE2 
     */
    
    ANSEL = 0x0;        // wszystkie GPIO digital
    
    TRISA = 0b00011111;     // GP0, GP1, GP2, GP4 - INPUT (BAND DATA); GP5 sygnał WAKE2 
    CMCON0 = 0x07;      //comparators disabled
    //CMCON0bits_t.CMON = 0;    
    GPIObits.GP5 = 0x0;     // stan aktywny wysoki dla WAKE2

    OPTION_REG   = 0b00000000;  
                            /* 10000000,
                           * GPIO pull-ups enable 0,
                           * INTEDG on rising     0, 
                           * TOSC FOSC/4 TOSE     0, 
                           * PSA                  0, 
                           * PS                   000 1:2 */
    WPU = 0b00011111;            /* Enable weak pull ups on BAND DATA pins */
    OPTION_REGbits.nGPPU = 0;   // dubel
    IOC = 0x0;            /* Interrupt on change disabled */ 
    DISABLE_PWM_Service();
}
void main(void) {
    SYSTEM_Initialize();
    
    do
    {
        // ToDo
        /*
         * detekcja zmiany kodu na BAND DATA i wysłanie impulsu na wy WAKE2
         * impuls WAKE2 min 100ms
         */
        __delay_ms(25);
    }
    while(1);
}

