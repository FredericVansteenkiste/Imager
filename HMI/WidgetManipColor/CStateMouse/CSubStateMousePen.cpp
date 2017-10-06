#include "CSubStateMousePen.h"

CSubStateMousePen::CSubStateMousePen():CSubStateMouse()
{
   emit ButtonPenChecked(true);
   emit ButtonPipetteChecked(false);
}

CSubStateMousePen::~CSubStateMousePen()
{
   emit ButtonPenChecked(false);
}

void CSubStateMousePen::Execute(void)
{
}

CSubStateMouse::e_state_machine CSubStateMousePen::eCurrentState(void) const
{
   return PEN;
}

CSubStateMouse::e_state_machine CSubStateMousePen::eButtonPenClicked(void)
{
   return DEFAULT;
}

CSubStateMouse::e_state_machine CSubStateMousePen::eButtonPipetteClicked(void)
{
   return PIPETTE;
}
