
#include "on_board_computer.h"
// main() runs in its own thread in the OS
int main()
{
    onBoardComputerInit();
    while (true) {
        onBoardComputerUpdate();
    }
}

