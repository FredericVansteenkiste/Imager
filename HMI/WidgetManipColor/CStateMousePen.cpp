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

CStateMachine::e_state_machine CStateMousePen::eCurrentState(void)
{
   return PEN;
}

CStateMachine::e_state_machine CStateMousePen::eButtonPenClicked(void)
{
   return DEFAULT;
}

CStateMachine::e_state_machine CStateMousePen::eButtonPipetteClicked(void)
{
   return PIPETTE;
}
