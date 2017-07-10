#ifndef CSTATEMOUSE_H
#define CSTATEMOUSE_H

#include <QObject>

#include "CState.h"
#include "CState/CStateMouseDefault.h"
#include "CState/CStateMousePen.h"
#include "CState/CStateMousePipette.h"

class CStateMouse : public CState
{
   Q_OBJECT

public:
   CStateMouse();
   virtual ~CStateMouse();

   virtual void Execute(void);

   virtual e_state_machine eCurrentState(void) const;

public slots:
   virtual e_state_machine eButtonPenClicked(void);
   virtual e_state_machine eButtonPipetteClicked(void);

private:
   CState* m_pCurrentState;

   void Connect(void) const;
};

#endif // CSTATEMOUSE_H
