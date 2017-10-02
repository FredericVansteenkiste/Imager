#include "CStateMousePen.h"

CStateMousePen::CStateMousePen():CSubStateMouse()
{
   emit ButtonPenChecked(true);
   emit ButtonPipetteChecked(false);
}

CStateMousePen::~CStateMousePen()
{
   emit ButtonPenChecked(false);
}

void CStateMousePen::Execute(void)
{
}

CSubStateMouse::e_state_machine CStateMousePen::eCurrentState(void) const
{
   return CSubStateMouse::PEN;
}

CSubStateMouse::e_state_machine CStateMousePen::eButtonPenClicked(void)
{
   return CSubStateMouse::DEFAULT;
}

CSubStateMouse::e_state_machine CStateMousePen::eButtonPipetteClicked(void)
{
   return CSubStateMouse::PIPETTE;
}
