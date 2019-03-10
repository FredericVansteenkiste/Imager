#ifndef CSubStateMousePen_H
#define CSubStateMousePen_H

#include <QObject>

#include "CSubStateMouse.h"

class CSubStateMousePen final : public CSubStateMouse
{
   Q_OBJECT

public:
   explicit CSubStateMousePen();
   virtual ~CSubStateMousePen() final;

   void Execute(void) final;

   e_state_machine eCurrentState(void) const final;

public slots:
   e_state_machine eButtonPenClicked(void) final;
   e_state_machine eButtonPipetteClicked(void) final;
};

#endif // CSubStateMousePen_H
