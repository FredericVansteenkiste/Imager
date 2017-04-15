#include "MdiArea.h"

MdiArea::MdiArea(QWidget* pParent):QMdiArea(pParent)
{
   setMouseTracking(true);
}

MdiArea::~MdiArea()
{
}

void MdiArea::mouseMoveEvent(QMouseEvent* pqEvent)
{
   emit CleanStatusBar();

   QMdiArea::mouseMoveEvent(pqEvent);
}
