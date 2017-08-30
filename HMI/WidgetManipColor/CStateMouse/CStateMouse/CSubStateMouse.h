#ifndef CSUBSTATEMOUSE_H
#define CSUBSTATEMOUSE_H

#include <QObject>

#include "../../../../CStateMachine/CStateMachine.h"

class CSubStateMouse : public CStateMachine
{
   Q_OBJECT

public:
   CSubStateMouse();
   virtual ~CSubStateMouse();

   typedef enum
   {
      NONE,
      DEFAULT,
      PEN,
      PIPETTE
   } e_state_machine;

   virtual void Execute(void) = 0;

   virtual e_state_machine eCurrentState(void) const = 0;

signals:
   void ButtonPenChecked(bool bIsFlat);
   void ButtonPipetteChecked(bool bIsFlat);

public slots:
   virtual e_state_machine eButtonPenClicked(void) = 0;
   virtual e_state_machine eButtonPipetteClicked(void) = 0;
};

#endif // CSUBSTATEMOUSE_H
