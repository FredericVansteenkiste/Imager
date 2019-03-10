#ifndef CSTATEMACHINE_H
#define CSTATEMACHINE_H

#include <QObject>

class CStateMachine : public QObject
{
   Q_OBJECT

public:
   explicit CStateMachine();
   virtual ~CStateMachine();

   virtual void Execute(void) = 0;
};

#endif // CSTATEMACHINE_H
