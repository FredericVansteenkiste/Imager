#include "CStateMouseDefault.h"

CStateMouseDefault::CStateMouseDefault()
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

CState::e_state_machine CStateMouseDefault::eCurrentState(void)
{
   return DEFAULT;
}

CState::e_state_machine CStateMouseDefault::eButtonPenClicked(void)
{
   return PEN;
}

CState::e_state_machine CStateMouseDefault::eButtonPipetteClicked(void)
{
   return PIPETTE;
}
