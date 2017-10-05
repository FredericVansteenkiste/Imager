#include "CSubStateMouseDefault.h"

CSubStateMouseDefault::CSubStateMouseDefault():CSubStateMouse()
{
   emit ButtonPipetteChecked(false);
   emit ButtonPenChecked(false);
}

CSubStateMouseDefault::~CSubStateMouseDefault()
{
}

void CSubStateMouseDefault::Execute(void)
{
}

CSubStateMouse::e_state_machine CSubStateMouseDefault::eCurrentState(void) const
{
   return CSubStateMouse::DEFAULT;
}

CSubStateMouse::e_state_machine CSubStateMouseDefault::eButtonPenClicked(void)
{
   return CSubStateMouse::PEN;
}

CSubStateMouse::e_state_machine CSubStateMouseDefault::eButtonPipetteClicked(void)
{
   return CSubStateMouse::PIPETTE;
}
