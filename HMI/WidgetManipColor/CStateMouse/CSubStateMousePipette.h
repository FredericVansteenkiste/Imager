#ifndef CSubStateMousePipette_H
#define CSubStateMousePipette_H

#include <QObject>

#include "CSubStateMouse.h"

class CSubStateMousePipette final : public CSubStateMouse
{
   Q_OBJECT

public:
   CSubStateMousePipette();
   virtual ~CSubStateMousePipette();

   void Execute(void) final;

   e_state_machine eCurrentState(void) const final;

public slots:
   e_state_machine eButtonPenClicked(void) final;
   e_state_machine eButtonPipetteClicked(void) final;
};

#endif // CSubStateMousePipette_H
