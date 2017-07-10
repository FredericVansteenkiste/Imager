#ifndef CSTATEMOUSEPEN_H
#define CSTATEMOUSEPEN_H

#include <QObject>

#include "../CState.h"

class CStateMousePen : public CState
{
   Q_OBJECT

public:
   CStateMousePen();
   virtual ~CStateMousePen();

   virtual void Execute(void);

   virtual e_state_machine eCurrentState(void) const;

public slots:
   virtual e_state_machine eButtonPenClicked(void);
   virtual e_state_machine eButtonPipetteClicked(void);
};

#endif // CSTATEMOUSEPEN_H
