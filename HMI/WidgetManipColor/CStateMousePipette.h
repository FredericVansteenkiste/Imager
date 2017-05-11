#ifndef CSTATEMOUSEPIPETTE_H
#define CSTATEMOUSEPIPETTE_H

#include <QObject>

#include "CStateMachine/CStateMachine.h"

class CStateMousePipette : public CStateMachine
{
   Q_OBJECT

public:
   CStateMousePipette();
   virtual ~CStateMousePipette();

   virtual void Execute(void);

   virtual e_state_machine eCurrentState(void);

public slots:
   virtual e_state_machine eButtonPenClicked(void);
   virtual e_state_machine eButtonPipetteClicked(void);
};

#endif // CSTATEMOUSEPIPETTE_H
