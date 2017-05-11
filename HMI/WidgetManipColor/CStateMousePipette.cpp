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

CStateMachine::e_state_machine CStateMousePipette::eCurrentState(void)
{
   return PIPETTE;
}

CStateMachine::e_state_machine CStateMousePipette::eButtonPenClicked(void)
{
   return PEN;
}

CStateMachine::e_state_machine CStateMousePipette::eButtonPipetteClicked(void)
{
   return DEFAULT;
}
