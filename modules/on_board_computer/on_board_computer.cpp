//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "on_board_computer.h"

#include "user_interface.h"
#include "pdc.h"
//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================
// Estado del PDC
extern bool pdcActiveState;

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void onBoardComputerInit()
{
    userInterfaceInit();
    pdcInit();
}

void onBoardComputerUpdate()
{
    userInterfaceUpdate();
    pdcUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
