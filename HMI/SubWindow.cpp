#include "SubWindow.h"

SubWindow::SubWindow(const QFileInfo& qFileInfo, QWidget *parent):
                                                QMdiSubWindow(parent),
                                                m_WidgetManipImage(true, this),
                                                m_qFileInfo(qFileInfo),
                                                m_pActionSelectImage(nullptr)
{
   setAttribute(Qt::WA_DeleteOnClose);
   setWindowTitle(m_qFileInfo.fileName());
   setWindowIcon(QIcon(":HMI/Icones/image.png"));

   m_WidgetManipImage.setImage(QImage(qstrAbsoluteFilePath()));
//   m_pqWidgetManipImage->setBackgroundBrush(QBrush(QColor(0x7F,0x7F,0x7F)));
//   m_pqWidgetManipImage->setBackgroundBrush(QBrush(QPixmap(":/HMI/Icones/ArrierePlan.png")));
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
   m_pActionSelectImage = pActionSelectImage;
}

QAction* SubWindow::pqActionSelectImage(void)
{
   return m_pActionSelectImage;
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
   m_pActionSelectImage->setText(m_qFileInfo.fileName());
}

void SubWindow::SelectSubWindow(void)
{
   mdiArea()->setActiveSubWindow(this);
}
