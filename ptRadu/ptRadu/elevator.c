#include "elevator.h"

#define _XTAL_FREQ 64000000UL

// Motor Driver Pins - Write Only.
#define MOTOR_DIRECTION LATEbits.LATE0
#define MOTOR_STEP LATEbits.LATE1

// Directions.
#define DOWN 0
#define UP 1

// Speed
#define SLOW 0
#define FAST 1

// Floor Positioning Registers - Read Only.
#define FLOOR0_POS_SWITCH PORTAbits.RA0
#define FLOOR1_POS_SWITCH PORTAbits.RA1
#define FLOOR2_POS_SWITCH PORTAbits.RA2
#define FLOOR3_POS_SWITCH PORTAbits.RA3

// Floor Positioning Interrupts Flags
#define FLOOR0_POS_INTERRUPT IOCAFbits.IOCAF0
#define FLOOR1_POS_INTERRUPT IOCAFbits.IOCAF1
#define FLOOR2_POS_INTERRUPT IOCAFbits.IOCAF2
#define FLOOR3_POS_INTERRUPT IOCAFbits.IOCAF3

// Floor Positioning Lights - Write Only.
#define FLOOR0_POS_LED LATAbits.LATA7
#define FLOOR1_POS_LED LATAbits.LATA6
#define FLOOR2_POS_LED LATAbits.LATA5
#define FLOOR3_POS_LED LATAbits.LATA4

// Floor Call Buttons - Read Only.
#define FLOOR0_CALL_BUTTON PORTCbits.RC0
#define FLOOR1_CALL_BUTTON PORTCbits.RC1
#define FLOOR2_CALL_BUTTON PORTCbits.RC2
#define FLOOR3_CALL_BUTTON PORTCbits.RC3

// Floor Call Interrupts Flags
#define FLOOR0_CALL_INTERRUPT IOCCFbits.IOCCF0
#define FLOOR1_CALL_INTERRUPT IOCCFbits.IOCCF1
#define FLOOR2_CALL_INTERRUPT IOCCFbits.IOCCF2
#define FLOOR3_CALL_INTERRUPT IOCCFbits.IOCCF3

#define FLOORS 4

volatile uint8_t currentFloor = 0;
volatile uint8_t floorCalls = 0b00000000;
volatile uint8_t activeCall = 0;

void init(void) {


    TRISE &= 0b11111100; // Set RE0 - MOTOR_DIRECTION, RE1 - MOTOR_STEP as outputs .

    TRISA &= 0b00001111;
    ANSELA &= 0b11110000; // Set RA0-3 as digital - Floor Position Buttons.
    ANSELC &= 0b11110000; // Set RC0 - RC3 as digital - Floor Call Buttons.
    WPUA |= 0b00001111; // Set weak pull-up on RA0-3.
    WPUC |= 0b00001111; // Set weak pull-up on RC0-3.

    FLOOR0_POS_LED = 1;
    FLOOR1_POS_LED = 1;
    FLOOR2_POS_LED = 1;
    FLOOR3_POS_LED = 1;

    reset();

    FLOOR0_POS_LED = 0;
    FLOOR1_POS_LED = 0;
    FLOOR2_POS_LED = 0;
    FLOOR3_POS_LED = 0;

    IOCAP |= 0b00001111; // Enable interrupt-on change for RA0-3 on positive edge
    IOCCN |= 0b00001111; // Enable interrupt-on change for RC0-3 on negative edge

    IOCAF &= 0b11110000;  // Clear the interrupt flag on port A
    IOCCF &= 0b11110000; // Clear the interrupt flag on port C

    PIE0bits.IOCIE = 1; // Enable interrupt on change

    INTCONbits.GIE = 1; // Enable global interrupts
    INTCONbits.PEIE = 1; // Enable peripheral interrupts

}

void start(void) {
    init();

    while (1) {
        updateLedIndicatior();
        moveMotor();
        logic();
    }
}

void logic() { // asta nu merge
    if (floorCalls != 0) {

    }


}

void moveMotor() {
    if (floorCalls != 0) {
        MOTOR_STEP = 0;
        __delay_ms(1);
        MOTOR_STEP = 1;
        __delay_ms(1);
    }
}


void reset() {

    MOTOR_DIRECTION = DOWN;

    while (1) {

        // elevator is already at floor0
        if (FLOOR0_POS_SWITCH == 0) {
            return;
        }
        MOTOR_STEP = 0;
        __delay_ms(1);
        MOTOR_STEP = 1;
        __delay_ms(1);
        moveMotor();
    }
}

void updateLedIndicatior(void) {
    switch (currentFloor) {
    case 0:
        FLOOR0_POS_LED = 1;
        FLOOR1_POS_LED = 0;
        FLOOR2_POS_LED = 0;
        FLOOR3_POS_LED = 0;
        break;

    case 1:
        FLOOR0_POS_LED = 0;
        FLOOR1_POS_LED = 1;
        FLOOR2_POS_LED = 0;
        FLOOR3_POS_LED = 0;
        break;

    case 2:
        FLOOR0_POS_LED = 0;
        FLOOR1_POS_LED = 0;
        FLOOR2_POS_LED = 1;
        FLOOR3_POS_LED = 0;
        break;

    case 3:
        FLOOR0_POS_LED = 0;
        FLOOR1_POS_LED = 0;
        FLOOR2_POS_LED = 0;
        FLOOR3_POS_LED = 1;
        break;

    default:
        break;
    }
}

// this is spaghetti code but i don't have time for a better implementation
void __interrupt()interr(void) {
    //__delay_ms(250);

    // Floor Positioning
    if (FLOOR0_POS_INTERRUPT) {

        currentFloor = 0;

        // Clear the interrupt flag
        FLOOR0_POS_INTERRUPT = 0;
    }

    if (FLOOR1_POS_INTERRUPT) {

        currentFloor = 1;

        // Clear the interrupt flag
        FLOOR1_POS_INTERRUPT = 0;
    }

    if (FLOOR2_POS_INTERRUPT) {

        currentFloor = 2;

        // Clear the interrupt flag
        FLOOR2_POS_INTERRUPT = 0;
    }

    if (FLOOR3_POS_INTERRUPT) {

        currentFloor = 3;

        // Clear the interrupt flag
        FLOOR3_POS_INTERRUPT = 0;
    }


    // Floor Call
    if (FLOOR0_CALL_INTERRUPT) {

        floorCalls |= 0b00000001;

        // Clear the interrupt flag
        FLOOR0_CALL_INTERRUPT = 0;
    }

    if (FLOOR1_CALL_INTERRUPT) {

        floorCalls |= 0b00000010;

        // Clear the interrupt flag
        FLOOR1_CALL_INTERRUPT = 0;
    }

    if (FLOOR2_CALL_INTERRUPT) {

        floorCalls |= 0b00000100;

        // Clear the interrupt flag
        FLOOR2_CALL_INTERRUPT = 0;
    }

    if (FLOOR3_CALL_INTERRUPT) {

        floorCalls |= 0b00001000;

        // Clear the interrupt flag
        FLOOR3_CALL_INTERRUPT = 0;
    }
}
