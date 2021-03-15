#include "SubWindow.h"

SubWindow::SubWindow(const QFileInfo& qFileInfo,
                     const QImage& qImage,
                     QWidget* pParent):
                           QMdiSubWindow(pParent),
                           m_pqMainWindow(dynamic_cast<MainWindow*>(pParent)),
                           m_pqWidgetManipImage(nullptr),
                           m_pqWidgetPalette(nullptr),
                           m_qFileInfo(qFileInfo),
                           m_pqActionSelectImage(nullptr)
{
   // On met à jour la variable QSettings et on regarde dans celle-ci pour voir
   // s'il y a déjà un pinceau décrit pour l'arrière plan
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);
   QVariant qVarBckgrndBrush = qSettings.value(  m_qFileInfo.absoluteFilePath()
                                               + "/QBrush");
   resize(qImage.size() + QSize(10, 10));
   if(qVarBckgrndBrush == QVariant())
   {
      // Si l'arrière plan n'a pas été définis, par défaut on le met en noir
      m_pqWidgetManipImage = new WidgetManipImage(qImage, Qt::black, this);
      qSettings.setValue(  m_qFileInfo.absoluteFilePath()
                         + "/QBrush",
                         m_pqWidgetManipImage->backgroundBrush());
   }
   else
   {
      m_pqWidgetManipImage = new WidgetManipImage(
                                             qImage,
                                             qVarBckgrndBrush.value<QBrush>(),
                                             this);
   }

   setMouseTracking(true);
   setAttribute(Qt::WA_DeleteOnClose);
   setWindowTitle(m_qFileInfo.fileName());
   setWindowIcon(QIcon(":HMI/Icones/image.png"));

   setWidget(m_pqWidgetManipImage);

   // On crée la palette correspondante à notre image
   m_pqWidgetPalette = new WidgetPalette(qImage.colorTable(), this);
   m_pqMainWindow->pWidgetManipColor()
                 ->pqPaletteLayout()
                 ->insertWidget(1, m_pqWidgetPalette);
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
   for(int y = 0; y < qImage().height(); y++)
   {
      iFirstLineVisible = y;
      for(int x = 0; x < qImage().width(); x++)
      {
         QRgb qColorPixel = qImage().pixel(x, y);
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
   for(int y = (qImage().height() - 1); y >= 0; y--)
   {
      iLastLineVisible = y;
      for(int x = 0; x < qImage().width(); x++)
      {
         QRgb qColorPixel = qImage().pixel(x, y);
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
   for(int x = 0; x < qImage().width(); x++)
   {
      iFirstColumnVisible = x;
      for(int y = 0; y < qImage().height(); y++)
      {
         QRgb qColorPixel = qImage().pixel(x, y);
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
   for(int x = (qImage().width() - 1); x >= 0; x--)
   {
      iLastColumnVisible = x;
      for(int y = 0; y < qImage().height(); y++)
      {
         QRgb qColorPixel = qImage().pixel(x, y);
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
      &&(iLastColumnVisible  == (qImage().width() - 1))
      &&(iLastLineVisible    == (qImage().height() - 1)))
   {
      return;
   }

   // J'extrais la partie de l'image qui nous intéresse
   m_pqWidgetManipImage->SetImage(
               qImage().copy(iFirstColumnVisible,
                             iFirstLineVisible,
                             iLastColumnVisible - iFirstColumnVisible + 1,
                             iLastLineVisible - iFirstLineVisible + 1));
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
   qImage().save(m_qFileInfo.absoluteFilePath());

   // Et l'image crée devient la nouvelle image de la fenêtre
   setWindowTitle(m_qFileInfo.fileName());
   m_pqActionSelectImage->setText(m_qFileInfo.fileName());

   emit UpdateWidgetManipColor();
}

void SubWindow::AppelMacro(void)
{
   // Changement de taille
//   int x(206);
//   int y(725);
//   int iWidth(68);
//   int iHeight(52);
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
   for(int i = 0; i < qImage().width(); i++)
   {
      for(int j = 0; j < qImage().height(); j++)
      {
         QColor qColorPixel(qImage().pixelColor(i, j));
         if(qColorPixel.red() != 0)
         {
            qColorPixel.setRed(227);
            qColorPixel.setGreen(90);
            qColorPixel.setBlue(0);
            qImage().setPixelColor(i, j, qColorPixel);
         }
      }
   }
   QString qstrSuffix = m_qFileInfo.suffix();
   QString qstrFileName = m_qFileInfo.fileName();
   qstrFileName.replace("." + qstrSuffix, "")
               .append("EnRouge")
               .append(".")
               .append(qstrSuffix);
   m_qFileInfo.setFile(m_qFileInfo.absolutePath() + "/" + qstrFileName);
   qImage().save(m_qFileInfo.absoluteFilePath());

   setWindowTitle(m_qFileInfo.fileName());
   m_pqActionSelectImage->setText(m_qFileInfo.fileName());

   // Inversion du haut
//   int x(0);
//   int y(0);
//   int iWidth(65);
//   int iHeight(40);
//   QImage qImage = m_qImage.copy(x, y, iWidth, iHeight);
//   for(int i = 0; i < m_qImage.width(); i++)
//   {
//      for(int j = 0; j < 25; j++)
//      {
//         QRgb qPixel(m_qImage.pixel(m_qImage.width() - (1+i), j));
//         qImage.setPixel(i, j, qPixel);
//      }
//   }
//   m_qImage = qImage;
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
}

void SubWindow::CreatePalette(void)
{
   // Si l'image courante à déjà une palette ...
   if(qImage().format() == QImage::Format_Indexed8)
   {
      // ... alors on sort de la fonction sans rien faire.
      return;
   }

   // On crée une palette pour l'image.
   qImage() = qImage().convertToFormat(QImage::Format_Indexed8,
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
   qImage().save(m_qFileInfo.absoluteFilePath());

   setWindowTitle(m_qFileInfo.fileName());
   m_pqWidgetManipImage->viewport()->update();
   m_pqActionSelectImage->setText(m_qFileInfo.fileName());

   emit UpdateWidgetManipColor();
}

void SubWindow::SupprPalette(void)
{
   // Si l'image courante n'a pas de palette ...
   if(qImage().format() != QImage::Format_Indexed8)
   {
      // ... alors on sort de la fonction sans rien faire.
      return;
   }

   // On convertit l'image à un format sans palette.
   qImage() = qImage().convertToFormat(QImage::Format_ARGB32);

   // On sauvegarde notre image
   QString qstrSuffix = m_qFileInfo.suffix();
   QString qstrFileName = m_qFileInfo.fileName();
   qstrFileName.replace("." + qstrSuffix, "")
               .append("_WithoutPalette.")
               .append(qstrSuffix);
   m_qFileInfo.setFile(m_qFileInfo.absolutePath() + "/" + qstrFileName);
   qImage().save(m_qFileInfo.absoluteFilePath());

   setWindowTitle(m_qFileInfo.fileName());
   m_pqWidgetManipImage->viewport()->update();
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
   m_pqWidgetManipImage->viewport()->update();
}

WidgetManipImage& SubWindow::GetWidgetManipImage(void)
{
   return *m_pqWidgetManipImage;
}

bool SubWindow::bIsPalette(void) const
{
   if(qImage().colorCount() == 0)
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
   for(int x = 0; x < qImage().width(); x++)
   {
      for(int y = 0; y < qImage().height(); y++)
      {
         QColor qColorPix = qImage().pixelColor(x, y);
         qmapColor[qColorPix.rgba64()]++;
      }
   }

   return static_cast<unsigned int>(qmapColor.size());
}

QImage& SubWindow::qImage(void) const
{
   return m_pqWidgetManipImage->qImage();
}
