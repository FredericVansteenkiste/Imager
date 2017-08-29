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

   virtual void Execute(void);

   virtual CSubStateMouse::e_state_machine eCurrentState(void) const;

public slots:
   virtual CSubStateMouse::e_state_machine eButtonPenClicked(void);
   virtual CSubStateMouse::e_state_machine eButtonPipetteClicked(void);
};

#endif // CSTATEMOUSEPEN_H
