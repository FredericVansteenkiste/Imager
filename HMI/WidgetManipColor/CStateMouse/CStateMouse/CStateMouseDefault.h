#ifndef CSTATEMOUSEDEFAULT_H
#define CSTATEMOUSEDEFAULT_H

#include <QObject>

#include "CSubStateMouse.h"

class CStateMouseDefault : public CSubStateMouse
{
   Q_OBJECT

public:
   CStateMouseDefault();
   virtual ~CStateMouseDefault();

   virtual void Execute(void);

   virtual CSubStateMouse::e_state_machine eCurrentState(void) const;

public slots:
   virtual CSubStateMouse::e_state_machine eButtonPenClicked(void);
   virtual CSubStateMouse::e_state_machine eButtonPipetteClicked(void);
};

#endif // CSTATEMOUSEDEFAULT_H
