#include "CStateMouse.h"

CStateMouse::CStateMouse():CStateMachine(),
                           m_pCurrentState(nullptr)
{
   m_pCurrentState = new CSubStateMouseDefault();
   Connect();
}

CStateMouse::~CStateMouse()
{
   delete m_pCurrentState;
}

void CStateMouse::Execute(void)
{
}

CSubStateMouse::e_state_machine CStateMouse::eCurrentState(void) const
{
   if(m_pCurrentState == nullptr)
   {
      return CSubStateMouse::NONE;
   }
   else
   {
      return m_pCurrentState->eCurrentState();
   }
}

CSubStateMouse::e_state_machine CStateMouse::eButtonPenClicked(void)
{
   CSubStateMouse::e_state_machine eChangeState =
                                          m_pCurrentState->eButtonPenClicked();

   if(eChangeState != CSubStateMouse::NONE)
   {
      delete m_pCurrentState;

      if(eChangeState == CSubStateMouse::DEFAULT)
      {
         m_pCurrentState = new CSubStateMouseDefault();
      }
      else if(eChangeState == CSubStateMouse::PEN)
      {
         m_pCurrentState = new CSubStateMousePen();
      }
      else
      {
         m_pCurrentState = new CSubStateMousePipette();
      }
      Connect();
   }

   return eCurrentState();
}

CSubStateMouse::e_state_machine CStateMouse::eButtonPipetteClicked(void)
{
   CSubStateMouse::e_state_machine eChangeState =
                                       m_pCurrentState->eButtonPipetteClicked();

   if(eChangeState != CSubStateMouse::NONE)
   {
      delete m_pCurrentState;

      if(eChangeState == CSubStateMouse::DEFAULT)
      {
         m_pCurrentState = new CSubStateMouseDefault();
      }
      else if(eChangeState == CSubStateMouse::PEN)
      {
         m_pCurrentState = new CSubStateMousePen();
      }
      else
      {
         m_pCurrentState = new CSubStateMousePipette();
      }
      Connect();
   }

   return eCurrentState();
}

void CStateMouse::Connect(void) const
{
   connect(m_pCurrentState, &CSubStateMouse::ButtonPenChecked,
           this,            &CStateMouse::ButtonPenChecked);
   connect(m_pCurrentState, &CSubStateMouse::ButtonPipetteChecked,
           this,            &CStateMouse::ButtonPipetteChecked);
}
