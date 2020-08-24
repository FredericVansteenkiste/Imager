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

private slots:
   void UpdateMenuWindow(QMdiSubWindow* pqWindow) const;

signals:
   void NewFileReceived(const QStringList& qlstrListFiles);
};

#endif // MDIAREA_H
