#include "SubWindow.h"

SubWindow::SubWindow(const QImage& qImage,
                     QWidget* pParent):
                           QMdiSubWindow(pParent),
                           m_pqMainWindow(dynamic_cast<MainWindow*>(pParent)),
                           m_pqWidgetManipImage(nullptr),
                           m_qImage(qImage),
                           m_pqActionSelectImage(nullptr)
{
   m_pqWidgetManipImage = new WidgetManipImage(this);

   setMouseTracking(true);
   setAttribute(Qt::WA_DeleteOnClose);

   m_pqWidgetManipImage->setImage(m_qImage);
   setWidget(*m_pqWidgetManipImage);

   m_pqWidgetManipImage->setBackgroundBrush(Qt::black);
}

SubWindow::~SubWindow()
{
   emit closeWindow(this);
}

void SubWindow::SetActionSelectImage(QAction* pActionSelectImage)
{
   m_pqActionSelectImage = pActionSelectImage;
}

QAction* SubWindow::pqActionSelectImage(void)
{
   return m_pqActionSelectImage;
}

void SubWindow::SelectSubWindow(void)
{
   mdiArea()->setActiveSubWindow(this);
}

void SubWindow::moveEvent(QMoveEvent* pqEvent)
{
   QMdiSubWindow::moveEvent(pqEvent);

   emit RedrawAllImage();
}

void SubWindow::resizeEvent(QResizeEvent* pqEvent)
{
   QMdiSubWindow::resizeEvent(pqEvent);

   emit RedrawAllImage();
}

void SubWindow::mouseMoveEvent(QMouseEvent* pqEvent)
{
   QMdiSubWindow::mouseMoveEvent(pqEvent);
}

void SubWindow::closeEvent(QCloseEvent* pqEvent)
{
   pqEvent->accept();
}

void SubWindow::Redraw(void)
{
   m_pqWidgetManipImage->pImageView()->resetCachedContent();
}

WidgetManipImage& SubWindow::GetWidgetManipImage(void)
{
   return *m_pqWidgetManipImage;
}

QPixmap SubWindow::qPixmap(void) const
{
   return m_pqWidgetManipImage->qPixmap();
}

QImage SubWindow::qImage(void) const
{
   return m_qImage;
}
