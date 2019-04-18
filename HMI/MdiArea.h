#ifndef MDIAREA_H
#define MDIAREA_H
#pragma once

#include <QtWidgets>

#include "SubWindow.h"

class MdiArea : public QMdiArea
{
   Q_OBJECT
public:
   explicit MdiArea(QWidget* pParent = nullptr);
   virtual ~MdiArea();

public slots:
   void setCheckedBackground(void);
   void askBackgroundColor(void);

protected:
   virtual void mouseMoveEvent(QMouseEvent* pqEvent);
   virtual void dragEnterEvent(QDragEnterEvent* pqEvent);
   virtual void dropEvent(QDropEvent* pqEvent);

private slots:
   void UpdateMenuWindow(QMdiSubWindow* pqWindow) const;

signals:
   void CleanStatusBar(void);
   void NewFileReceived(const QStringList& qlstrListFiles);
};

#endif // MDIAREA_H
