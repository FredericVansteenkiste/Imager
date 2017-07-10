#ifndef CSTATE_H
#define CSTATE_H

#include <QObject>

#include "../../CStateMachine/CStateMachine.h"

class CState : public CStateMachine
{
   Q_OBJECT

public:
   CState();
   virtual ~CState();

   typedef enum
   {
      NONE,
      DEFAULT,
      PEN,
      PIPETTE
   } e_state_machine;

   virtual e_state_machine eCurrentState(void) const = 0;

signals:
   void ButtonPenChecked(bool bIsFlat);
   void ButtonPipetteChecked(bool bIsFlat);

public slots:
   virtual e_state_machine eButtonPenClicked(void) = 0;
   virtual e_state_machine eButtonPipetteClicked(void) = 0;
};

#endif // CSTATE_H
