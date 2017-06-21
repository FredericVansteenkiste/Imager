#ifndef CSTATEMACHINE_H
#define CSTATEMACHINE_H

#include <QObject>

class CStateMachine : public QObject
{
   Q_OBJECT

public:
   CStateMachine();
   virtual ~CStateMachine();

   typedef enum
   {
      NONE,
      DEFAULT,
      PEN,
      PIPETTE
   } e_state_machine;

   virtual void Execute(void) = 0;

   virtual e_state_machine eCurrentState(void) = 0;

signals:
   void ButtonPenChecked(bool bIsFlat);
   void ButtonPipetteChecked(bool bIsFlat);

public slots:
   virtual e_state_machine eButtonPenClicked(void) = 0;
   virtual e_state_machine eButtonPipetteClicked(void) = 0;
};

#endif // CSTATEMACHINE_H
