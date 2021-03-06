#include "CSubStateMousePipette.h"

CSubStateMousePipette::CSubStateMousePipette():CSubStateMouse()
{
   emit ButtonPipetteChecked(true);
   emit ButtonPenChecked(false);
}

CSubStateMousePipette::~CSubStateMousePipette()
{
   emit ButtonPipetteChecked(false);
}

void CSubStateMousePipette::Execute(void)
{
}

CSubStateMouse::e_state_machine CSubStateMousePipette::eCurrentState(void) const
{
   return PIPETTE;
}

CSubStateMouse::e_state_machine CSubStateMousePipette::eButtonPenClicked(void)
{
   return PEN;
}

CSubStateMouse::e_state_machine CSubStateMousePipette::eButtonPipetteClicked(
                                                                           void)
{
   return DEFAULT;
}
