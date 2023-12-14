//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "on_board_computer.h"

#include "user_interface.h"
#include "pdc.h"
#include "dimming.h"

void onBoardComputerInit()
{
    userInterfaceInit();
    pdcInit();
    dimmingInit();
}

void onBoardComputerUpdate()
{
    userInterfaceUpdate();
    pdcUpdate();
    dimmingUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==========================|========
