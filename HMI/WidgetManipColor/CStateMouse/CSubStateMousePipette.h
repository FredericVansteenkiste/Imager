#ifndef CSubStateMousePipette_H
#define CSubStateMousePipette_H

#include <QObject>

#include "CSubStateMouse.h"

class CSubStateMousePipette : public CSubStateMouse
{
   Q_OBJECT

public:
   CSubStateMousePipette();
   virtual ~CSubStateMousePipette();

   virtual void Execute(void) final;

   virtual CSubStateMouse::e_state_machine eCurrentState(void) const final;

public slots:
   virtual CSubStateMouse::e_state_machine eButtonPenClicked(void) final;
   virtual CSubStateMouse::e_state_machine eButtonPipetteClicked(void) final;
};

#endif // CSubStateMousePipette_H
