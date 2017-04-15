#include "SubWindow.h"

SubWindow::SubWindow(const QFileInfo& qFileInfo,
                     const QImage& qImage,
                     QWidget *parent):QMdiSubWindow(parent),
                                      m_WidgetManipImage(this),
                                      m_qFileInfo(qFileInfo),
                                      m_pqActionSelectImage(nullptr)
{
   setAttribute(Qt::WA_DeleteOnClose);
   setWindowTitle(m_qFileInfo.fileName());
   setWindowIcon(QIcon(":HMI/Icones/image.png"));

   m_WidgetManipImage.setImage(qImage);
   setWidget(m_WidgetManipImage);
}

SubWindow::~SubWindow()
{
   emit closeWindow(this);
}

QString SubWindow::qstrAbsoluteFilePath(void) const
{
   return m_qFileInfo.absoluteFilePath();
}

void SubWindow::SetActionSelectImage(QAction* pActionSelectImage)
{
   m_pqActionSelectImage = pActionSelectImage;
}

QAction* SubWindow::pqActionSelectImage(void)
{
   return m_pqActionSelectImage;
}

void SubWindow::ResizeTransparency(void)
{
   QImage qCurrentImage(qstrAbsoluteFilePath());

   int  iFirstLineVisible(0);
   bool bIsFound = false;
   for(int y = 0; y < qCurrentImage.height(); y++)
   {
      iFirstLineVisible = y;
      for(int x = 0; x < qCurrentImage.width(); x++)
      {
         QRgb qColorPixel = qCurrentImage.pixel(x, y);
         if(qAlpha(qColorPixel) != 0)
         {
            bIsFound = true;
            break;
         }
      }
      if(bIsFound == true)
      {
         break;
      }
   }

   int  iLastLineVisible(0);
   bIsFound = false;
   for(int y = (qCurrentImage.height() - 1); y >= 0; y--)
   {
      iLastLineVisible = y;
      for(int x = 0; x < qCurrentImage.width(); x++)
      {
         QRgb qColorPixel = qCurrentImage.pixel(x, y);
         if(qAlpha(qColorPixel) != 0)
         {
            bIsFound = true;
            break;
         }
      }
      if(bIsFound == true)
      {
         break;
      }
   }

   int  iFirstColumnVisible(0);
   bIsFound = false;
   for(int x = 0; x < qCurrentImage.width(); x++)
   {
      iFirstColumnVisible = x;
      for(int y = 0; y < qCurrentImage.height(); y++)
      {
         QRgb qColorPixel = qCurrentImage.pixel(x, y);
         if(qAlpha(qColorPixel) != 0)
         {
            bIsFound = true;
            break;
         }
      }
      if(bIsFound == true)
      {
         break;
      }
   }

   int  iLastColumnVisible(0);
   bIsFound = false;
   for(int x = (qCurrentImage.width() - 1); x >= 0; x--)
   {
      iLastColumnVisible = x;
      for(int y = 0; y < qCurrentImage.height(); y++)
      {
         QRgb qColorPixel = qCurrentImage.pixel(x, y);
         if(qAlpha(qColorPixel) != 0)
         {
            bIsFound = true;
            break;
         }
      }
      if(bIsFound == true)
      {
         break;
      }
   }

   // Si aucun changement n'est recquis, on quitte la macro:
   if(  (iFirstColumnVisible == 0)
      &&(iFirstLineVisible   == 0)
      &&(iLastColumnVisible  == qCurrentImage.width() - 1)
      &&(iLastLineVisible    == qCurrentImage.height() - 1))
   {
      return;
   }

   QImage qNewImage = qCurrentImage.copy(
                                 iFirstColumnVisible,
                                 iFirstLineVisible,
                                 iLastColumnVisible - iFirstColumnVisible + 1,
                                 iLastLineVisible - iFirstLineVisible + 1);
   QString qstrSuffix = m_qFileInfo.suffix();
   QString qstrFileName = m_qFileInfo.fileName();
   qstrFileName.replace("." + qstrSuffix, "")
               .append("_")
               .append(QString::number(iFirstColumnVisible))
               .append("x")
               .append(QString::number(iFirstLineVisible))
               .append(".")
               .append(qstrSuffix);
   m_qFileInfo.setFile(m_qFileInfo.absolutePath() + "/" + qstrFileName);
   qNewImage.save(m_qFileInfo.absoluteFilePath());

   setWindowTitle(m_qFileInfo.fileName());
   m_WidgetManipImage.setImage(qNewImage);
   m_pqActionSelectImage->setText(m_qFileInfo.fileName());
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

void SubWindow::Redraw(void)
{
   m_WidgetManipImage.pImageView()->resetCachedContent();
}

WidgetManipImage& SubWindow::GetWidgetManipImage(void)
{
   return m_WidgetManipImage;
}

QPixmap SubWindow::qPixmap(void) const
{
   return m_WidgetManipImage.qPixmap();
}
