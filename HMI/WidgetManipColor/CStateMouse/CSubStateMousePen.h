#ifndef CSubStateMousePen_H
#define CSubStateMousePen_H

#include <QObject>

#include "CSubStateMouse.h"

class CSubStateMousePen : public CSubStateMouse
{
   Q_OBJECT

public:
   CSubStateMousePen();
   virtual ~CSubStateMousePen();

   virtual void Execute(void) final;

   virtual CSubStateMouse::e_state_machine eCurrentState(void) const final;

public slots:
   virtual CSubStateMouse::e_state_machine eButtonPenClicked(void) final;
   virtual CSubStateMouse::e_state_machine eButtonPipetteClicked(void) final;
};

#endif // CSubStateMousePen_H
