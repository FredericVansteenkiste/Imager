#ifndef MDIAREA_H
#define MDIAREA_H

#include <QtWidgets>

class MdiArea : public QMdiArea
{
   Q_OBJECT
public:
   MdiArea(QWidget* pParent = nullptr);
   virtual ~MdiArea();

signals:
   void CleanStatusBar(void);

protected:
   virtual void mouseMoveEvent(QMouseEvent* pqEvent);
};

#endif // MDIAREA_H
