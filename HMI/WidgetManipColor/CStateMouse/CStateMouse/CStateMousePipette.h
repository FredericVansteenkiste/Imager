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

   virtual void Execute(void);

   virtual CSubStateMouse::e_state_machine eCurrentState(void) const;

public slots:
   virtual CSubStateMouse::e_state_machine eButtonPenClicked(void);
   virtual CSubStateMouse::e_state_machine eButtonPipetteClicked(void);
};

#endif // CSTATEMOUSEPIPETTE_H
