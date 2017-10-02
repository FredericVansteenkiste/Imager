#ifndef CSTATEMOUSE_H
#define CSTATEMOUSE_H

#include <QObject>

#include "../../CStateMachine/CStateMachine.h"
#include "CStateMouse/CSubStateMouse.h"
#include "CStateMouse/CStateMouseDefault.h"
#include "CStateMouse/CStateMousePen.h"
#include "CStateMouse/CStateMousePipette.h"

class CStateMouse : public CStateMachine
{
   Q_OBJECT

public:
   CStateMouse();
   virtual ~CStateMouse();

   virtual void Execute(void) final;

   CSubStateMouse::e_state_machine eCurrentState(void) const;

public slots:
   virtual CSubStateMouse::e_state_machine eButtonPenClicked(void);
   virtual CSubStateMouse::e_state_machine eButtonPipetteClicked(void);

signals:
   void ButtonPenChecked(bool bIsFlat);
   void ButtonPipetteChecked(bool bIsFlat);

private:
   CSubStateMouse* m_pCurrentState;

   void Connect(void) const;
};

#endif // CSTATEMOUSE_H
