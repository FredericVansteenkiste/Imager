#include "CStateMousePen.h"

CStateMousePen::CStateMousePen()
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

CState::e_state_machine CStateMousePen::eCurrentState(void) const
{
   return PEN;
}

CState::e_state_machine CStateMousePen::eButtonPenClicked(void)
{
   return DEFAULT;
}

CState::e_state_machine CStateMousePen::eButtonPipetteClicked(void)
{
   return PIPETTE;
}
