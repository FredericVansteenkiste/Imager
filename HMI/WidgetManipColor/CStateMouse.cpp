#include "CStateMouse.h"

CStateMouse::CStateMouse():CStateMachine(),
                           m_pCurrentState(nullptr)
{
   m_pCurrentState = new CStateMouseDefault();
   Connect();
}

CStateMouse::~CStateMouse()
{
   delete m_pCurrentState;
}

void CStateMouse::Execute(void)
{
}

CStateMachine::e_state_machine CStateMouse::eCurrentState(void)
{
   return NONE;
}

CStateMachine::e_state_machine CStateMouse::eButtonPenClicked(void)
{
   e_state_machine eChangeState = m_pCurrentState->eButtonPenClicked();

   if(eChangeState != NONE)
   {
      delete m_pCurrentState;

      if(eChangeState == DEFAULT)
      {
         m_pCurrentState = new CStateMouseDefault();
      }
      else if(eChangeState == PEN)
      {
         m_pCurrentState = new CStateMousePen();
      }
      else
      {
         m_pCurrentState = new CStateMousePipette();
      }
      Connect();
   }

   return NONE;
}

CStateMachine::e_state_machine CStateMouse::eButtonPipetteClicked(void)
{
   e_state_machine eChangeState = m_pCurrentState->eButtonPipetteClicked();

   if(eChangeState != NONE)
   {
      delete m_pCurrentState;

      if(eChangeState == DEFAULT)
      {
         m_pCurrentState = new CStateMouseDefault();
      }
      else if(eChangeState == PEN)
      {
         m_pCurrentState = new CStateMousePen();
      }
      else
      {
         m_pCurrentState = new CStateMousePipette();
      }
      Connect();
   }

   return NONE;
}

void CStateMouse::Connect(void) const
{
   connect(m_pCurrentState, &CStateMachine::ButtonPenChecked,
           this,            &CStateMouse::ButtonPenChecked);
   connect(m_pCurrentState, &CStateMachine::ButtonPipetteChecked,
           this,            &CStateMouse::ButtonPipetteChecked);
}
