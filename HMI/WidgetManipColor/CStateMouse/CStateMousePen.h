#ifndef CSTATEMOUSEPEN_H
#define CSTATEMOUSEPEN_H

#include <QObject>

#include "CSubStateMouse.h"

class CStateMousePen : public CSubStateMouse
{
   Q_OBJECT

public:
   CStateMousePen();
   virtual ~CStateMousePen();

   virtual void Execute(void) final;

   virtual CSubStateMouse::e_state_machine eCurrentState(void) const final;

public slots:
   virtual CSubStateMouse::e_state_machine eButtonPenClicked(void) final;
   virtual CSubStateMouse::e_state_machine eButtonPipetteClicked(void) final;
};

#endif // CSTATEMOUSEPEN_H
