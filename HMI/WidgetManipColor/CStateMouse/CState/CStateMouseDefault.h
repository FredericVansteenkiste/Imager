#ifndef CSTATEMOUSEDEFAULT_H
#define CSTATEMOUSEDEFAULT_H

#include <QObject>

#include "../CState.h"

class CStateMouseDefault : public CState
{
   Q_OBJECT

public:
   CStateMouseDefault();
   virtual ~CStateMouseDefault();

   virtual void Execute(void);

   virtual e_state_machine eCurrentState(void) const;

public slots:
   virtual e_state_machine eButtonPenClicked(void);
   virtual e_state_machine eButtonPipetteClicked(void);
};

#endif // CSTATEMOUSEDEFAULT_H
