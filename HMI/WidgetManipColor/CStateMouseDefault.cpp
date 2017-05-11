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

CStateMachine::e_state_machine CStateMouseDefault::eCurrentState(void)
{
   return DEFAULT;
}

CStateMachine::e_state_machine CStateMouseDefault::eButtonPenClicked(void)
{
   return PEN;
}

CStateMachine::e_state_machine CStateMouseDefault::eButtonPipetteClicked(void)
{
   return PIPETTE;
}
