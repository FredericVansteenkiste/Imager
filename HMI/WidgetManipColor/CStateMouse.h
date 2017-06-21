#ifndef CSTATEMOUSE_H
#define CSTATEMOUSE_H

#include <QObject>

#include "CStateMachine/CStateMachine.h"
#include "CStateMouseDefault.h"
#include "CStateMousePen.h"
#include "CStateMousePipette.h"

class CStateMouse : public CStateMachine
{
   Q_OBJECT

public:
   CStateMouse();
   virtual ~CStateMouse();

   virtual void Execute(void);

   virtual e_state_machine eCurrentState(void);

public slots:
   virtual e_state_machine eButtonPenClicked(void);
   virtual e_state_machine eButtonPipetteClicked(void);

private:
   CStateMachine* m_pCurrentState;

   void Connect(void) const;
};

#endif // CSTATEMOUSE_H
