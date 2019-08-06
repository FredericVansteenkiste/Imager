#include "SubWindow.h"

SubWindow::SubWindow(const QFileInfo& qFileInfo,
                     const QImage& qImage,
                     QWidget* pParent):
                           QMdiSubWindow(pParent),
                           m_pqMainWindow(dynamic_cast<MainWindow*>(pParent)),
                           m_pqWidgetManipImage(nullptr),
                           m_pqWidgetPalette(nullptr),
                           m_qFileInfo(qFileInfo),
                           m_qImage(qImage),
                           m_pqActionSelectImage(nullptr)
{
   m_pqWidgetManipImage = new WidgetManipImage(this);

   setMouseTracking(true);
   setAttribute(Qt::WA_DeleteOnClose);
   setWindowTitle(m_qFileInfo.fileName());
   setWindowIcon(QIcon(":HMI/Icones/image.png"));

   m_pqWidgetManipImage->setImage(m_qImage);
   setWidget(*m_pqWidgetManipImage);

   // On crée la palette correspondante à notre image
   m_pqWidgetPalette = new WidgetPalette(m_qImage.colorTable(), this);
   m_pqMainWindow->pWidgetManipColor()
                 ->pqPaletteLayout()
                 ->insertWidget(1, m_pqWidgetPalette);

   // On met à jour la variable QSettings
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);
   QVariant qVarBckgrndBrush = qSettings.value(  m_qFileInfo.absoluteFilePath()
                                               + "/QBrush");
   if(qVarBckgrndBrush == QVariant())
   {
      // Si l'arrière plan n'a pas été définis, par défaut on le met en noir
      m_pqWidgetManipImage->setBackgroundBrush(Qt::black);
      qSettings.setValue(  m_qFileInfo.absoluteFilePath()
                         + "/QBrush",
                         m_pqWidgetManipImage->backgroundBrush());
   }
   else
   {
      m_pqWidgetManipImage->setBackgroundBrush(
                                             qVarBckgrndBrush.value<QBrush>());
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
   // On recherche où se trouve les bords de l'image
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

   // J'extrais la partie de l'image qui nous intéresse
   m_qImage = m_qImage.copy(iFirstColumnVisible,
                            iFirstLineVisible,
                            iLastColumnVisible - iFirstColumnVisible + 1,
                            iLastLineVisible - iFirstLineVisible + 1);
   // Je copie le fichier dans un nouveau nom indiquant les coordonnées de la
   // nouvelle image dans l'ancienne
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

   // Et l'image crée devient la nouvelle image de la fenêtre
   setWindowTitle(m_qFileInfo.fileName());
   m_pqWidgetManipImage->setImage(m_qImage);
   m_pqActionSelectImage->setText(m_qFileInfo.fileName());

   emit UpdateWidgetManipColor();
}

void SubWindow::AppelMacro(void)
{
   // Changement de taille
//   int x(20);
//   int y(364);
//   int iWidth(149);
//   int iHeight(70);
//   m_qImage = m_qImage.copy(x, y, iWidth, iHeight);
//   QString qstrSuffix = m_qFileInfo.suffix();
//   QString qstrFileName = m_qFileInfo.fileName();
//   qstrFileName.replace("." + qstrSuffix, "")
//               .append("_")
//               .append(QString::number(x))
//               .append("x")
//               .append(QString::number(y))
//               .append(".")
//               .append(qstrSuffix);
//   m_qFileInfo.setFile(m_qFileInfo.absolutePath() + "/" + qstrFileName);
//   m_qImage.save(m_qFileInfo.absoluteFilePath());

//   setWindowTitle(m_qFileInfo.fileName());
//   m_pqWidgetManipImage->setImage(m_qImage);
//   m_pqActionSelectImage->setText(m_qFileInfo.fileName());

   // Changement de couleur
   for(int i = 0; i < m_qImage.width(); i++)
   {
      for(int j = 0; j < m_qImage.height(); j++)
      {
         if(m_qImage.pixelColor(i, j).alpha() == 0)
         {
            continue;
         }
         QColor qColorPixel(m_qImage.pixelColor(i, j));
         qColorPixel.setRed(223);
         qColorPixel.setGreen(65);
         qColorPixel.setBlue(19);
         m_qImage.setPixelColor(i, j, qColorPixel);
      }
   }
   QString qstrSuffix = m_qFileInfo.suffix();
   QString qstrFileName = m_qFileInfo.fileName();
   qstrFileName.replace("." + qstrSuffix, "")
               .append("EnRouge")
               .append(".")
               .append(qstrSuffix);
   m_qFileInfo.setFile(m_qFileInfo.absolutePath() + "/" + qstrFileName);
   m_qImage.save(m_qFileInfo.absoluteFilePath());

   setWindowTitle(m_qFileInfo.fileName());
   m_pqWidgetManipImage->setImage(m_qImage);
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
   m_pqWidgetManipImage->setImage(m_qImage);
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

   // On convertit l'image à un format sans palette.
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
   m_pqWidgetManipImage->setImage(m_qImage);
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
   m_pqWidgetManipImage->setBackgroundBrush(QBrush(
                                 QPixmap(ADRESS_CHECKED_BACKGROUND_PICTURE)));
   m_pqWidgetPalette->repaint();
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);
   qSettings.setValue(  m_qFileInfo.absoluteFilePath()
                      + "/QBrush",
                      m_pqWidgetManipImage->backgroundBrush());
}

void SubWindow::askBackgroundColor(void)
{
   // On demande à l'utilisateur de sélectionner une couleur
   QColorDialog* pqColorDialog = new QColorDialog(Qt::white, this);
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
   QColor qTempColor = qColor;
   qTempColor.setAlpha(255);
   m_pqWidgetManipImage->setBackgroundBrush(QBrush(qTempColor));
   m_pqWidgetPalette->repaint();
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);
   qSettings.setValue(  m_qFileInfo.absoluteFilePath()
                      + "/QBrush",
                      m_pqWidgetManipImage->backgroundBrush());

   MdiArea* pMdiArea = dynamic_cast<MdiArea*>(mdiArea());
   if(pMdiArea != nullptr)
   {
      emit pMdiArea->subWindowActivated(this);
   }
}

QBrush SubWindow::backgroundBrush(void) const
{
   return m_pqWidgetManipImage->backgroundBrush();
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

void SubWindow::closeEvent(QCloseEvent* event)
{
   m_pqMainWindow->pWidgetManipColor()
                 ->pqPaletteLayout()
                 ->removeWidget(m_pqWidgetPalette);
   m_pqWidgetPalette->setParent(this);

   event->accept();
}

void SubWindow::Redraw(void)
{
   m_pqWidgetManipImage->pImageView()->resetCachedContent();
}

WidgetManipImage& SubWindow::GetWidgetManipImage(void)
{
   return *m_pqWidgetManipImage;
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

WidgetPalette* SubWindow::pqWidgetPalette(void) const
{
   return m_pqWidgetPalette;
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

   return static_cast<unsigned int>(qmapColor.size());
}

QPixmap SubWindow::qPixmap(void) const
{
   return m_pqWidgetManipImage->qPixmap();
}

QImage SubWindow::qImage(void) const
{
   return m_qImage;
}
