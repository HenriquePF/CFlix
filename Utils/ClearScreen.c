#include "ClearScreen.h"

void ClearScreen(void) {
    printf("\e[1;1H\e[2J");
}
