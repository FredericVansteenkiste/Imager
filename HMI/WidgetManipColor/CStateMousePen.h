#ifndef CSTATEMOUSEPEN_H
#define CSTATEMOUSEPEN_H

#include <QObject>

#include "CStateMachine/CStateMachine.h"

class CStateMousePen : public CStateMachine
{
   Q_OBJECT

public:
   CStateMousePen();
   virtual ~CStateMousePen();

   virtual void Execute(void);

   virtual e_state_machine eCurrentState(void);

public slots:
   virtual e_state_machine eButtonPenClicked(void);
   virtual e_state_machine eButtonPipetteClicked(void);
};

#endif // CSTATEMOUSEPEN_H
