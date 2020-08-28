#include "buttons.h"

void BUTTON_Enable(BUTTON button)
{
    switch (button)
    {
        case SW1: SW1_TRIS = 1;
        break;
        case SW2: SW2_TRIS = 1;
        break;
        case SW3: SW3_TRIS = 1;
        break;
        case SW4: SW4_TRIS = 1;
    }

}

bool BUTTON_IsPressed(BUTTON button)
{
    switch (button)
    {
        case SW1: return (SW1_PORT == BUTTON_PRESSED? true : false);
        case SW2: return (SW2_PORT == BUTTON_PRESSED? true : false);
        case SW3: return (SW3_PORT == BUTTON_PRESSED? true : false);
        case SW4: return (SW4_PORT == BUTTON_PRESSED? true : false);
    }
}
