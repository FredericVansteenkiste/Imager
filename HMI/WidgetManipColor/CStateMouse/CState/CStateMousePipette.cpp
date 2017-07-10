#include "CStateMousePipette.h"

CStateMousePipette::CStateMousePipette()
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

CState::e_state_machine CStateMousePipette::eCurrentState(void) const
{
   return PIPETTE;
}

CState::e_state_machine CStateMousePipette::eButtonPenClicked(void)
{
   return PEN;
}

CState::e_state_machine CStateMousePipette::eButtonPipetteClicked(void)
{
   return DEFAULT;
}
