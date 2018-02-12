#ifndef MDIAREA_H
#define MDIAREA_H

#include <QtWidgets>

#include "SubWindow.h"

class MdiArea : public QMdiArea
{
   Q_OBJECT
public:
   MdiArea(QWidget* pParent = nullptr);
   virtual ~MdiArea();

public slots:
   void setCheckedBackground(void);
   void askBackgroundColor(void);

signals:
   void CleanStatusBar(void);
   void NewFileReceived(const QStringList& qlstrListFiles);

protected:
   virtual void mouseMoveEvent(QMouseEvent* pqEvent);
   virtual void dragEnterEvent(QDragEnterEvent* pqEvent);
   virtual void dropEvent(QDropEvent* pqEvent);
};

#endif // MDIAREA_H
