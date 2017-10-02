#include "CStateMouseDefault.h"

CStateMouseDefault::CStateMouseDefault():CSubStateMouse()
{
   emit ButtonPipetteChecked(false);
   emit ButtonPenChecked(false);
}

CStateMouseDefault::~CStateMouseDefault()
{
}

void CStateMouseDefault::Execute(void)
{
}

CSubStateMouse::e_state_machine CStateMouseDefault::eCurrentState(void) const
{
   return CSubStateMouse::DEFAULT;
}

CSubStateMouse::e_state_machine CStateMouseDefault::eButtonPenClicked(void)
{
   return CSubStateMouse::PEN;
}

CSubStateMouse::e_state_machine CStateMouseDefault::eButtonPipetteClicked(void)
{
   return CSubStateMouse::PIPETTE;
}
