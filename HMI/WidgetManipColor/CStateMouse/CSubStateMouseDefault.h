#ifndef CSubStateMouseDefault_H
#define CSubStateMouseDefault_H

#include <QObject>

#include "CSubStateMouse.h"

class CSubStateMouseDefault final : public CSubStateMouse
{
   Q_OBJECT

public:
   explicit CSubStateMouseDefault();
   virtual ~CSubStateMouseDefault() final;

   void Execute(void) final;

   e_state_machine eCurrentState(void) const final;

public slots:
   e_state_machine eButtonPenClicked(void) final;
   e_state_machine eButtonPipetteClicked(void) final;
};

#endif // CSubStateMouseDefault_H
