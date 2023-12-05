//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "on_board_computer.h"
#include "date_and_time.h"
#include "matrix_keypad.h"
#include "code.h"
#include "pc_serial.h"

//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============

InterruptIn gateOpenButton(PF_9);
InterruptIn gateCloseButton(PF_8);

DigitalOut incorrectCodeLed(LED3);
DigitalOut systemBlockedLed(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

char codeSequenceFromUserInterface[CODE_NUMBER_OF_KEYS];

//=====[Declaration and initialization of private global variables]============


static bool incorrectCodeState = OFF;
static bool systemBlockedState = OFF;

static bool codeComplete = false;
static int numberOfCodeChars = 0;

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceMatrixKeypadUpdate();
static void incorrectCodeIndicatorUpdate();
static void systemBlockedIndicatorUpdate();


//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    matrixKeypadInit( SYSTEM_TIME_INCREMENT_MS );
}

void userInterfaceUpdate()
{
    userInterfaceMatrixKeypadUpdate();
}

bool incorrectCodeStateRead()
{
    return incorrectCodeState;
}

void incorrectCodeStateWrite( bool state )
{
    incorrectCodeState = state;
}

bool systemBlockedStateRead()
{
    return systemBlockedState;
}

void systemBlockedStateWrite( bool state )
{
    systemBlockedState = state;
}

bool userInterfaceCodeCompleteRead()
{
    return codeComplete;
}

void userInterfaceCodeCompleteWrite( bool state )
{
    codeComplete = state;
}

//=====[Implementations of private functions]==================================
#define TECLA_UNO '1'
#define TECLA_DOS '2'
#define TECLA_TRES '3'
#define TECLA_CUATRO '4'
#define TECLA_CINCO '5'
#define TECLA_SEIS '6'
#define TECLA_SIETE '7'
#define TECLA_OCHO '8'
#define TECLA_NUEVE '9'
#define TECLA_CERO '0'
#define TECLA_A 'A'
#define TECLA_B 'B'
#define TECLA_C 'C'
#define TECLA_D 'D'
#define TECLA_ASTERISCO '*'
#define TECLA_NUMERAL '#'

static void userInterfaceMatrixKeypadUpdate()
{
    char keyReleased = matrixKeypadUpdate();

    if( keyReleased != '\0' ) {

        switch (keyReleased) {
            case TECLA_UNO:
                pcSerialComStringWrite("Se presionó la tecla 1\n");
                break;
            case TECLA_DOS:
                pcSerialComStringWrite("Se presionó la tecla 2\n");
                break;
            case TECLA_TRES:
                pcSerialComStringWrite("Se presionó la tecla 3\n");
                break;
            case TECLA_CUATRO:
                pcSerialComStringWrite("Se presionó la tecla 4\n");
                break;
            case TECLA_CINCO:
                pcSerialComStringWrite("Se presionó la tecla 5\n");
                break;
            case TECLA_SEIS:
                pcSerialComStringWrite("Se presionó la tecla 6\n");
                break;
            case TECLA_SIETE:
                pcSerialComStringWrite("Se presionó la tecla 7\n");
                break;
            case TECLA_OCHO:
                pcSerialComStringWrite("Se presionó la tecla 8\n");
                break;
            case TECLA_NUEVE:
                pcSerialComStringWrite("Se presionó la tecla 9\n");
                break;
            case TECLA_CERO:
                pcSerialComStringWrite("Se presionó la tecla 0\n");
                break;
            case TECLA_A:
                pcSerialComStringWrite("Se presionó la tecla A\n");
                break;
            case TECLA_B:
                pcSerialComStringWrite("Se presionó la tecla B\n");
                break;
            case TECLA_C:
                pcSerialComStringWrite("Se presionó la tecla C\n");
                break;
            case TECLA_D:
                pcSerialComStringWrite("Se presionó la tecla D\n");
                break;
            case TECLA_ASTERISCO:
                pcSerialComStringWrite("Se presionó la tecla *\n");
                break;
            case TECLA_NUMERAL:
                pcSerialComStringWrite("Se presionó la tecla #\n");
                break;
            default:
                //pcSerialComStringWrite("Tecla no reconocida\n");
                break;
        }
    }
}