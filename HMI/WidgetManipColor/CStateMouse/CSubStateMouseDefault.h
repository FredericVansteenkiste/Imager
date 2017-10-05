#ifndef CSubStateMouseDefault_H
#define CSubStateMouseDefault_H

#include <QObject>

#include "CSubStateMouse.h"

class CSubStateMouseDefault : public CSubStateMouse
{
   Q_OBJECT

public:
   CSubStateMouseDefault();
   virtual ~CSubStateMouseDefault();

   virtual void Execute(void) final;

   virtual CSubStateMouse::e_state_machine eCurrentState(void) const final;

public slots:
   virtual CSubStateMouse::e_state_machine eButtonPenClicked(void) final;
   virtual CSubStateMouse::e_state_machine eButtonPipetteClicked(void) final;
};

#endif // CSubStateMouseDefault_H
