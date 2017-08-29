#include "CStateMousePipette.h"

CStateMousePipette::CStateMousePipette():CSubStateMouse()
{
   emit ButtonPipetteChecked(true);
   emit ButtonPenChecked(false);
}

CStateMousePipette::~CStateMousePipette()
{
   emit ButtonPipetteChecked(false);
}

void CStateMousePipette::Execute(void)
{
}

CSubStateMouse::e_state_machine CStateMousePipette::eCurrentState(void) const
{
   return CSubStateMouse::PIPETTE;
}

CSubStateMouse::e_state_machine CStateMousePipette::eButtonPenClicked(void)
{
   return CSubStateMouse::PEN;
}

CSubStateMouse::e_state_machine CStateMousePipette::eButtonPipetteClicked(void)
{
   return CSubStateMouse::DEFAULT;
}
