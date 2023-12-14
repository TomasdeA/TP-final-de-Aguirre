//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "on_board_computer.h"
#include "matrix_keypad.h"
#include "pc_serial.h"
#include "pdc.h"
#include "dimming.h"

//=====[Declaration of private defines]========================================
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

#define DOUBLE_TAP_TIME 400ms
//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============


static bool isFirstTapDetected = false;  // Agregar esta variable global


//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============


//=====[Declaration and initialization of private global variables]============

Ticker tickerluzInterior;
Ticker tickerluzGuardabarro;

static int tickRateMSDimming = 1;

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceMatrixKeypadUpdate();


//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    matrixKeypadInit( SYSTEM_TIME_INCREMENT_MS );
}

void userInterfaceUpdate()
{
    userInterfaceMatrixKeypadUpdate();
}

//=====[Implementations of private functions]==================================

void setDimmingLightOneTap(lucesPwm_t luzIndex){
    //OFF
    if(!getOnMode(luzIndex))
        setOnMode(luzIndex, true);
    //ON - DIMMING
    else if(getDimmingMode(luzIndex))
        setDimmingMode(luzIndex, false);
    //ON
    else 
        setOnMode(luzIndex, false);
}

void setDimmingLightDobleTap(lucesPwm_t luzIndex){
    //OFF
    if(!getOnMode(luzIndex)){
        setOnMode(luzIndex, true);
        setDimmingMode(luzIndex, true);
    }
    //ON - DIMMING
    else if(getDimmingMode(luzIndex))
        setDimmingMode(luzIndex, false);
    //ON 
    else 
        setDimmingMode(luzIndex, true);
}
// Callback para el Ticker
void luzInteriorCallback() {
    // Si el ticker se activa, asumimos que fue un simple tap
    isFirstTapDetected = false;
    // Single Tap
    setDimmingLightOneTap(LUZ_INTERIOR);
    tickerluzInterior.detach();
}

void luzGuardabarroCallback() {
    // Si el ticker se activa, asumimos que fue un simple tap
    isFirstTapDetected = false;
    // Single Tap
    setDimmingLightOneTap(LUZ_GUARDABARRO);
    tickerluzInterior.detach();
}

static void userInterfaceMatrixKeypadUpdate()
{
    char keyReleased = matrixKeypadUpdate();

    if( keyReleased != '\0' ) {

        switch (keyReleased) {
            case TECLA_UNO:
                pcSerialComStringWrite("Se presionó la tecla 1\n");
                // Cambiar el estado del PDC
                pdcActiveState = !pdcActiveState;
                
                // Opcional: Imprimir mensaje en la consola para indicar el cambio de estado
                if (pdcActiveState) {
                    pcSerialComStringWrite("PDC Activado\n");
                } else {
                    pcSerialComStringWrite("PDC Desactivado\n");
                }
            
                break;
            case TECLA_DOS:
                pcSerialComStringWrite("Se presionó la tecla 2\n");
                if(!isFirstTapDetected){
                    isFirstTapDetected = true;
                    tickerluzInterior.attach(&luzInteriorCallback, DOUBLE_TAP_TIME);
                }else {
                    tickerluzInterior.detach();
                    isFirstTapDetected = false;
                    setDimmingLightDobleTap(LUZ_INTERIOR);
                }
                break;
            case TECLA_TRES:
                pcSerialComStringWrite("Se presionó la tecla 3\n");
                if(!isFirstTapDetected){
                    isFirstTapDetected = true;
                    tickerluzInterior.attach(&luzGuardabarroCallback, DOUBLE_TAP_TIME);
                }else {
                    tickerluzInterior.detach();
                    isFirstTapDetected = false;
                    setDimmingLightDobleTap(LUZ_GUARDABARRO);
                }
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