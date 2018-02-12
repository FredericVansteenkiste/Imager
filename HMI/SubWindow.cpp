#include "SubWindow.h"

SubWindow::SubWindow(const QFileInfo& qFileInfo,
                     const QImage& qImage,
                     QWidget* pParent):QMdiSubWindow(pParent),
                                       m_pWidgetManipImage(nullptr),
                                       m_qFileInfo(qFileInfo),
                                       m_qImage(qImage),
                                       m_pqActionSelectImage(nullptr),
                                       m_qCurrentColor(Qt::black)

{
   m_pWidgetManipImage = new WidgetManipImage(this);

   // On choisi une couleur de travail
   if(m_qImage.colorTable().isEmpty() == false)
   {
      m_qCurrentColor = m_qImage.colorTable()[0];
   }

   setMouseTracking(true);
   setAttribute(Qt::WA_DeleteOnClose);
   setWindowTitle(m_qFileInfo.fileName());
   setWindowIcon(QIcon(":HMI/Icones/image.png"));

   m_pWidgetManipImage->setImage(m_qImage);
   setWidget(*m_pWidgetManipImage);

   QSettings qSettings(ORGANISATION, NAME_APPLICATION);
   QVariant qVarBckgrndBrush = qSettings.value(  m_qFileInfo.absoluteFilePath()
                                               + "/QBrush");
   if(qVarBckgrndBrush == QVariant())
   {
      qSettings.setValue(  m_qFileInfo.absoluteFilePath()
                           + "/QBrush",
                           m_pWidgetManipImage->backgroundBrush());
   }
   else
   {
      m_pWidgetManipImage->setBackgroundBrush(qVarBckgrndBrush.value<QBrush>());
   }
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
   int  iFirstLineVisible(0);
   bool bIsFound = false;
   for(int y = 0; y < m_qImage.height(); y++)
   {
      iFirstLineVisible = y;
      for(int x = 0; x < m_qImage.width(); x++)
      {
         QRgb qColorPixel = m_qImage.pixel(x, y);
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
   for(int y = (m_qImage.height() - 1); y >= 0; y--)
   {
      iLastLineVisible = y;
      for(int x = 0; x < m_qImage.width(); x++)
      {
         QRgb qColorPixel = m_qImage.pixel(x, y);
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
   for(int x = 0; x < m_qImage.width(); x++)
   {
      iFirstColumnVisible = x;
      for(int y = 0; y < m_qImage.height(); y++)
      {
         QRgb qColorPixel = m_qImage.pixel(x, y);
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
   for(int x = (m_qImage.width() - 1); x >= 0; x--)
   {
      iLastColumnVisible = x;
      for(int y = 0; y < m_qImage.height(); y++)
      {
         QRgb qColorPixel = m_qImage.pixel(x, y);
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
      &&(iLastColumnVisible  == (m_qImage.width() - 1))
      &&(iLastLineVisible    == (m_qImage.height() - 1)))
   {
      return;
   }

   m_qImage = m_qImage.copy(iFirstColumnVisible,
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
   m_qImage.save(m_qFileInfo.absoluteFilePath());

   setWindowTitle(m_qFileInfo.fileName());
   m_pWidgetManipImage->setImage(m_qImage);
   m_pqActionSelectImage->setText(m_qFileInfo.fileName());

   emit UpdateWidgetManipColor();
}

void SubWindow::AppelMacro(void)
{
   int x(9);
   int y(308);
   int iWidth(76);
   int iHeight(55);
   m_qImage = m_qImage.copy(x, y, iWidth, iHeight);
   QString qstrSuffix = m_qFileInfo.suffix();
   QString qstrFileName = m_qFileInfo.fileName();
   qstrFileName.replace("." + qstrSuffix, "")
               .append("_")
               .append(QString::number(x))
               .append("x")
               .append(QString::number(y))
               .append(".")
               .append(qstrSuffix);
   m_qFileInfo.setFile(m_qFileInfo.absolutePath() + "/" + qstrFileName);
   m_qImage.save(m_qFileInfo.absoluteFilePath());

   setWindowTitle(m_qFileInfo.fileName());
   m_pWidgetManipImage->setImage(m_qImage);
   m_pqActionSelectImage->setText(m_qFileInfo.fileName());
}

void SubWindow::CreatePalette(void)
{
   // Si l'image courante à déjà une palette ...
   if(m_qImage.format() == QImage::Format_Indexed8)
   {
      // ... alors on sort de la fonction sans rien faire.
      return;
   }

   // On crée une palette pour l'image.
   m_qImage = m_qImage.convertToFormat(QImage::Format_Indexed8,
                                         Qt::ColorOnly
                                       | Qt::ThresholdDither
                                       | Qt::DiffuseAlphaDither
                                       | Qt::PreferDither
                                       | Qt::NoOpaqueDetection);

   // On sauvegarde notre image
   QString qstrSuffix = m_qFileInfo.suffix();
   QString qstrFileName = m_qFileInfo.fileName();
   qstrFileName.replace("." + qstrSuffix, "")
               .append("_WithPalette.")
               .append(qstrSuffix);
   m_qFileInfo.setFile(m_qFileInfo.absolutePath() + "/" + qstrFileName);
   m_qImage.save(m_qFileInfo.absoluteFilePath());

   setWindowTitle(m_qFileInfo.fileName());
   m_pWidgetManipImage->setImage(m_qImage);
   m_pqActionSelectImage->setText(m_qFileInfo.fileName());

   emit UpdateWidgetManipColor();
}

void SubWindow::SupprPalette(void)
{
   // Si l'image courante n'a pas de palette ...
   if(m_qImage.format() != QImage::Format_Indexed8)
   {
      // ... alors on sort de la fonction sans rien faire.
      return;
   }

   // On crée une palette pour l'image.
   m_qImage = m_qImage.convertToFormat(QImage::Format_ARGB32);

   // On sauvegarde notre image
   QString qstrSuffix = m_qFileInfo.suffix();
   QString qstrFileName = m_qFileInfo.fileName();
   qstrFileName.replace("." + qstrSuffix, "")
               .append("_WithoutPalette.")
               .append(qstrSuffix);
   m_qFileInfo.setFile(m_qFileInfo.absolutePath() + "/" + qstrFileName);
   m_qImage.save(m_qFileInfo.absoluteFilePath());

   setWindowTitle(m_qFileInfo.fileName());
   m_pWidgetManipImage->setImage(m_qImage);
   m_pqActionSelectImage->setText(m_qFileInfo.fileName());

   emit UpdateWidgetManipColor();
}

void SubWindow::SelectSubWindow(void)
{
   mdiArea()->setActiveSubWindow(this);
}

void SubWindow::setCheckedBackground(void)
{
   // On applique le damier à l'arrière plan.
   m_pWidgetManipImage->setBackgroundBrush(QBrush(
                                 QPixmap(ADRESS_CHECKED_BACKGROUND_PICTURE)));
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);
   qSettings.setValue(  m_qFileInfo.absoluteFilePath()
                      + "/QBrush",
                      m_pWidgetManipImage->backgroundBrush());
}

void SubWindow::askBackgroundColor(void)
{
   // On demande à l'utilisateur de sélectionner une couleur
   QColor qColor = m_pWidgetManipImage->backgroundBrush().color();
   QColorDialog* pqColorDialog = new QColorDialog(qColor, this);
   pqColorDialog->setOptions(  QColorDialog::NoButtons
                             | QColorDialog::DontUseNativeDialog);

   connect(pqColorDialog, &QColorDialog::currentColorChanged,
           this,          &SubWindow::setBackgroundColor);
   connect(pqColorDialog, &QColorDialog::colorSelected,
           this,          &SubWindow::setBackgroundColor);

   pqColorDialog->open();
}

void SubWindow::setBackgroundColor(const QColor& qColor)
{
   m_pWidgetManipImage->setBackgroundBrush(QBrush(qColor));
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);
   qSettings.setValue(  m_qFileInfo.absoluteFilePath()
                      + "/QBrush",
                      m_pWidgetManipImage->backgroundBrush());

   MdiArea* pMdiArea = dynamic_cast<MdiArea*>(mdiArea());
   if(pMdiArea != nullptr)
   {
      emit pMdiArea->subWindowActivated(this);
   }
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
   emit CleanStatusBar();

   QMdiSubWindow::mouseMoveEvent(pqEvent);
}

void SubWindow::Redraw(void)
{
   m_pWidgetManipImage->pImageView()->resetCachedContent();
}

WidgetManipImage& SubWindow::GetWidgetManipImage(void)
{
   return *m_pWidgetManipImage;
}

bool SubWindow::bIsPalette(void) const
{
   if(m_qImage.colorCount() == 0)
   {
      return false;
   }
   else
   {
      return true;
   }
}

unsigned int SubWindow::uiNbColorDefined(void) const
{
   QMap<QRgba64, unsigned int> qmapColor;
   for(int x = 0; x < m_qImage.width(); x++)
   {
      for(int y = 0; y < m_qImage.height(); y++)
      {
         QColor qColorPix = m_qImage.pixelColor(x, y);
         qmapColor[qColorPix.rgba64()]++;
      }
   }

   return qmapColor.size();
}

QPixmap SubWindow::qPixmap(void) const
{
   return m_pWidgetManipImage->qPixmap();
}

QImage SubWindow::qImage(void) const
{
   return m_qImage;
}
