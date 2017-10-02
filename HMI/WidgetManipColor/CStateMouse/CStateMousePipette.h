#ifndef CSTATEMOUSEPIPETTE_H
#define CSTATEMOUSEPIPETTE_H

#include <QObject>

#include "CSubStateMouse.h"

class CStateMousePipette : public CSubStateMouse
{
   Q_OBJECT

public:
   CStateMousePipette();
   virtual ~CStateMousePipette();

   virtual void Execute(void) final;

   virtual CSubStateMouse::e_state_machine eCurrentState(void) const final;

public slots:
   virtual CSubStateMouse::e_state_machine eButtonPenClicked(void) final;
   virtual CSubStateMouse::e_state_machine eButtonPipetteClicked(void) final;
};

#endif // CSTATEMOUSEPIPETTE_H
