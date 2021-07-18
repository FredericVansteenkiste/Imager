#include "MainWindow.h"

#define STR_CURRENT_DIRECTORY "currentDirectory"

MainWindow::MainWindow(QWidget* pqParent):QMainWindow(pqParent),
                                          m_pqActionReduceImage(nullptr),
                                          m_pqActionAppelMacro(nullptr),
                                          m_pqActionCreatePalette(nullptr),
                                          m_pqActionSupprPalette(nullptr),
                                          m_pqActionCheckedBckgr(nullptr),
                                          m_pqActionColoredBckgr(nullptr),
                                          m_pqWindowMenu(nullptr),
                                          m_pqActionsWindowMenu(nullptr),
                                          m_pqLabelCoordMouse(nullptr),
                                          m_pqLabelColorPixel(nullptr),
                                          m_pqWidgetManipColor(nullptr),
                                          m_pqMessagerie(nullptr)
{
   SetMenuAndToolbar();
   CreateDockWindow();
   CreateCentralWidget();
   CreateConnection();

   ReadSettings();

   UpdateLabelCoordMouse(QString());
   UpdateLabelColorPixel(QString());
   SubWindowActivated(nullptr);

   QStringList qlstrArguments(qApp->arguments());
   qlstrArguments.removeFirst();
   OpenListFile(qlstrArguments);
}

MainWindow::~MainWindow()
{
   WriteSettings();
}

WidgetManipColor* MainWindow::pWidgetManipColor(void) const
{
   return m_pqWidgetManipColor;
}

void MainWindow::SetMenuAndToolbar(void)
{
#ifdef Q_OS_LINUX
   QAction* pActionOpen = new QAction(QIcon::fromTheme("document-open"),
                                      tr("&Open"),
                                      this);
#else
   QStyle* pqStyle = QApplication::style();
   QAction* pActionOpen = new QAction(pqStyle->standardIcon(
                                                      QStyle::SP_DirOpenIcon),
                                      tr("&Open"),
                                      this);
#endif
   pActionOpen->setShortcut(QKeySequence::Open);
   connect(pActionOpen, &QAction::triggered, this, &MainWindow::OpenFile);


   m_pqActionReduceImage = new QAction(QIcon(":/Icones/resize.png"),
                                      tr("Resize"),
                                      this);
   m_pqActionReduceImage->setDisabled(true);


   m_pqActionAppelMacro = new QAction(QIcon(":/Icones/Engrenages.png"),
                                     tr("Macro"),
                                     this);
   m_pqActionAppelMacro->setDisabled(true);

   m_pqActionCreatePalette = new QAction(
                                    QIcon(":/Icones/CreatePalette.png"),
                                    tr("Creating a palette for the picture(s)"),
                                    this);
   m_pqActionCreatePalette->setDisabled(true);

   m_pqActionSupprPalette = new QAction(
                              QIcon(":/Icones/DeletePalette.png"),
                              tr("Deleting a palette for the picture(s)"),
                              this);
   m_pqActionSupprPalette->setDisabled(true);

   m_pqActionCheckedBckgr = new QAction(QIcon(ADRESS_CHECKED_BACKGROUND_PICTURE),
                                       tr("Checked background"),
                                       this);
   m_pqActionCheckedBckgr->setDisabled(true);

   QPixmap qPixmapColoredIcon(25, 25);
   qPixmapColoredIcon.fill(QColor(0, 0, 0));
   m_pqActionColoredBckgr = new QAction(QIcon(qPixmapColoredIcon),
                                       tr("Colored background"),
                                       this);
   m_pqActionColoredBckgr->setDisabled(true);

#ifdef Q_OS_LINUX
   QAction* pActionAbout = new QAction(QIcon::fromTheme("help-about"),
                                       tr("&About"),
                                       this);
#else
   QAction* pActionAbout = new QAction(tr("&About"),
                                       this);
#endif
   connect(pActionAbout, &QAction::triggered, this, &MainWindow::About);

   QAction* pActionExit = new QAction(tr("E&xit"), this);
   pActionExit->setShortcut(QKeySequence::Close);
   connect(pActionExit, &QAction::triggered, this, &MainWindow::close);

   QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addAction(pActionOpen);
   fileMenu->addSeparator();
   fileMenu->addAction(pActionExit);

   QMenu* macroMenu = menuBar()->addMenu(tr("&Macro"));
   macroMenu->addAction(m_pqActionReduceImage);
   macroMenu->addAction(m_pqActionAppelMacro);
   macroMenu->addAction(m_pqActionCreatePalette);
   macroMenu->addAction(m_pqActionSupprPalette);

   QMenu* bckgrMenu = menuBar()->addMenu(tr("&Background"));
   bckgrMenu->addAction(m_pqActionCheckedBckgr);
   bckgrMenu->addAction(m_pqActionColoredBckgr);

   m_pqWindowMenu = menuBar()->addMenu(tr("&Window"));
   // Je crée un groupe action pour marquer quelles est la fenêtre sélectionnée.
   m_pqActionsWindowMenu = new QActionGroup(this);
   m_pqActionsWindowMenu->setExclusive(true);

   QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
   helpMenu->addAction(pActionAbout);

   QToolBar* fileToolBar = addToolBar(tr("File"));
   fileToolBar->addAction(pActionOpen);

   QToolBar* macroToolBar = addToolBar(tr("Macro"));
   macroToolBar->addAction(m_pqActionReduceImage);
   macroToolBar->addAction(m_pqActionAppelMacro);
   macroToolBar->addAction(m_pqActionCreatePalette);
   macroToolBar->addAction(m_pqActionSupprPalette);

   m_pqLabelCoordMouse = new QLabel("");
   m_pqLabelColorPixel = new QLabel("");
   statusBar()->addPermanentWidget(m_pqLabelCoordMouse);
   statusBar()->addPermanentWidget(m_pqLabelColorPixel);
}

void MainWindow::ReadSettings(void)
{
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);

   restoreGeometry(qSettings.value("geometry").toByteArray());
   restoreState(qSettings.value("windowState").toByteArray());
}

void MainWindow::WriteSettings(void) const
{
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);

   qSettings.setValue("geometry", saveGeometry());
   qSettings.setValue("windowState", saveState());
}

void MainWindow::OpenFiles(const QString& qstrFile)
{
   QStringList qlstrListFiles = qstrFile.split("\n");

   OpenListFile(qlstrListFiles);
}

void MainWindow::OpenFile(void)
{
   // On demande à l'utilisateur l'adresse des images à afficher
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);

   QStringList qlstrListFiles = QFileDialog::getOpenFileNames(
                              this,
                              "Select one or more image files to open",
                              qSettings.value(STR_CURRENT_DIRECTORY).toString(),
                              "Images (*.png *.bmp *.jpg *.CR2 *.ppm)");

   OpenListFile(qlstrListFiles);
}

void MainWindow::OpenListFile(const QStringList& qlstrListFiles)
{
   if(qlstrListFiles.isEmpty() == true)
   {
      return;
   }

   QFileInfo qFileInfoTmp(qlstrListFiles.first());

   // On enregistre le répertoire courant
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);
   qSettings.setValue(STR_CURRENT_DIRECTORY, qFileInfoTmp.absolutePath());

   // On ajoute les images sélectionnés sur le widget central
   MdiArea* pqMdiArea = dynamic_cast<MdiArea*>(centralWidget());
   foreach(const QString& qstrFile, qlstrListFiles)
   {
      if(bImageExist(qstrFile) == true)
      {
         QListWidgetItem* pqMsg = new QListWidgetItem(
                              QIcon(":/Icones/IconeErreur.png"),
                              "The file \"" + qstrFile + "\" is already open");
         emit SendMsg(pqMsg);

         continue;
      }

      QFileInfo qFileInfo(qstrFile);

      // On crée l'image pour s'assurer que le fichier est correcte
      QImage qImage;
      if(qFileInfo.suffix() == "CR2")
      {
         qImage = qExtractImageFromRaw(qFileInfo.absoluteFilePath());
      }
      else
      {
         qImage.load(qFileInfo.absoluteFilePath());
      }

      if(qImage.isNull() == true)
      {
         QListWidgetItem* pqMsg = new QListWidgetItem(
                                    QIcon(":/Icones/IconeErreur.png"),
                                    "Impossible de lire l'image \"" + qstrFile
                                    + "\" : format non reconnu");
         emit SendMsg(pqMsg);

         continue;
      }

      // On crée un fenêtre avec notre image
      SubWindow* pSubWindow = new SubWindow(qFileInfo, qImage, this);
      pqMdiArea->addSubWindow(pSubWindow);

      m_pqActionReduceImage->setEnabled(true);
      m_pqActionAppelMacro->setEnabled(true);
      m_pqActionCreatePalette->setEnabled(true);
      m_pqActionSupprPalette->setEnabled(true);
      m_pqActionCheckedBckgr->setEnabled(true);
      m_pqActionColoredBckgr->setEnabled(true);
      connect(m_pqActionReduceImage, &QAction::triggered,
              pSubWindow,           &SubWindow::ResizeTransparency);
      connect(m_pqActionAppelMacro, &QAction::triggered,
              pSubWindow,          &SubWindow::AppelMacro);
      connect(m_pqActionCreatePalette, &QAction::triggered,
              pSubWindow,             &SubWindow::CreatePalette);
      connect(m_pqActionSupprPalette, &QAction::triggered,
              pSubWindow,            &SubWindow::SupprPalette);
      pSubWindow->show();

      // Si les scrollbars sont actives, il faut prendre en compte leurs
      // dimensions.
      QSize qSizeSubWindow = pSubWindow->size();
      QScrollBar* pHorScrollBar = pSubWindow->GetWidgetManipImage()
                                             .horizontalScrollBar();
      if(pHorScrollBar->isHidden() == false)
      {
         qSizeSubWindow.rheight() += pHorScrollBar->height();
      }
      QScrollBar* pVerScrollBar = pSubWindow->GetWidgetManipImage()
                                             .verticalScrollBar();
      if(pVerScrollBar->isHidden() == false)
      {
         qSizeSubWindow.rwidth() += pVerScrollBar->width();
      }
      pSubWindow->resize(qSizeSubWindow);

      QAction* pActionSelectImage = new QAction(qFileInfo.fileName(), this);
      pActionSelectImage->setCheckable(true);
      connect(pActionSelectImage, &QAction::triggered,
              pSubWindow,         &SubWindow::SelectSubWindow);
      pSubWindow->SetActionSelectImage(pActionSelectImage);
      m_pqWindowMenu->addAction(pActionSelectImage);
      m_pqActionsWindowMenu->addAction(pActionSelectImage);
      pActionSelectImage->setChecked(true);

      connect(pSubWindow, &SubWindow::closeWindow,
              this,       &MainWindow::UpdateMenuWindow);
      connect(pSubWindow, &SubWindow::closeWindow,
              this,       &MainWindow::CheckEnabledActionReduceImage,
              Qt::QueuedConnection);
      connect(pSubWindow, &SubWindow::RedrawAllImage,
              this,       &MainWindow::RedrawAllImage,
              Qt::QueuedConnection);
      connect(pSubWindow, &SubWindow::CleanStatusBar,
              this,       &MainWindow::CleanStatusBar);
      connect(pSubWindow, &SubWindow::UpdateWidgetManipColor,
              this,       &MainWindow::UpdateWidgetManipColor);

      WidgetManipImage* pWidgetManipImage = &pSubWindow->GetWidgetManipImage();
      connect(pWidgetManipImage, &WidgetManipImage::CoordMouse,
              this,              &MainWindow::UpdateLabelCoordMouse);
      connect(pWidgetManipImage, &WidgetManipImage::ColorPixel,
              this,              &MainWindow::UpdateLabelColorPixel);
   }
}

void MainWindow::About(void)
{
   QMessageBox::about(this,
                      tr("About Application"),
                      tr("<b>VTK Industries</b> : Imager application. Done by "
                         "Frédéric Vansteenkiste"));
}

void MainWindow::CheckEnabledActionReduceImage(void)
{
   if(centralWidget() == nullptr)
   {
      m_pqActionReduceImage->setEnabled(false);
      m_pqActionAppelMacro->setEnabled(false);
      m_pqActionCreatePalette->setEnabled(false);
      m_pqActionSupprPalette->setEnabled(false);
      m_pqActionCheckedBckgr->setEnabled(false);
      m_pqActionColoredBckgr->setEnabled(false);

      return;
   }

   QList<QMdiSubWindow*> qlpSubWindow = dynamic_cast<MdiArea*>(centralWidget())
                                                             ->subWindowList();
   if(qlpSubWindow.isEmpty() == true)
   {
      m_pqActionReduceImage->setEnabled(false);
      m_pqActionAppelMacro->setEnabled(false);
      m_pqActionCreatePalette->setEnabled(false);
      m_pqActionSupprPalette->setEnabled(false);
      m_pqActionCheckedBckgr->setEnabled(false);
      m_pqActionColoredBckgr->setEnabled(false);
   }
   else
   {
      m_pqActionReduceImage->setEnabled(true);
      m_pqActionAppelMacro->setEnabled(true);
      m_pqActionCreatePalette->setEnabled(true);
      m_pqActionSupprPalette->setEnabled(true);
      m_pqActionCheckedBckgr->setEnabled(true);
      m_pqActionColoredBckgr->setEnabled(true);
   }
}

void MainWindow::UpdateMenuWindow(SubWindow* pSubWindow)
{
   m_pqWindowMenu->removeAction(pSubWindow->pqActionSelectImage());
   m_pqActionsWindowMenu->removeAction(pSubWindow->pqActionSelectImage());
}

void MainWindow::UpdateLabelCoordMouse(const QString& qstrLabel)
{
   if(qstrLabel.isEmpty() == true)
   {
      m_pqLabelCoordMouse->hide();
   }
   else
   {
      m_pqLabelCoordMouse->setText(qstrLabel);
      m_pqLabelCoordMouse->show();
   }
}

void MainWindow::UpdateLabelColorPixel(const QString& qstrLabel)
{
   if(qstrLabel.isEmpty() == true)
   {
      m_pqLabelColorPixel->hide();
   }
   else
   {
      m_pqLabelColorPixel->setText(qstrLabel);
      m_pqLabelColorPixel->show();
   }
}

void MainWindow::AddToMessagerie(QListWidgetItem* pqMessage)
{
   m_pqMessagerie->addItem(pqMessage);
}

void MainWindow::CleanStatusBar(void)
{
   m_pqLabelCoordMouse->hide();
   m_pqLabelColorPixel->hide();
}

void MainWindow::closeEvent(QCloseEvent* pqEvent)
{
   if(centralWidget() != nullptr)
   {
      QList<QMdiSubWindow*> qlpSubWindow
                  = dynamic_cast<MdiArea*>(centralWidget())->subWindowList();

      foreach(QMdiSubWindow* pMdiSubWindow, qlpSubWindow)
      {
         SubWindow* pSubWindow = dynamic_cast<SubWindow*>(pMdiSubWindow);
         disconnect(pSubWindow, nullptr, nullptr, nullptr);
      }
   }

   QMainWindow::closeEvent(pqEvent);
}

void MainWindow::SubWindowActivated(QMdiSubWindow* pMdiSubWindow)
{
   if(pMdiSubWindow == nullptr)
   {
      m_pqWidgetManipColor->hide();
   }
   else
   {
      SubWindow* pSubWindow = dynamic_cast<SubWindow*>(pMdiSubWindow);
      m_pqWidgetManipColor->SetSizePalette(static_cast<unsigned int>(
                                            pSubWindow->qImage().colorCount()));
      m_pqWidgetManipColor->SetColorNumber(pSubWindow->uiNbColorDefined());
      m_pqWidgetManipColor->SetDepth(static_cast<unsigned int>(
                                                pSubWindow->qImage().depth()));
      m_pqWidgetManipColor->SetBitsUsedPerPixel(static_cast<unsigned int>(
                                        pSubWindow->qImage().bitPlaneCount()));
      m_pqWidgetManipColor->SetSizeImage(pSubWindow->qImage().size());
      m_pqWidgetManipColor->show();

      QColor qColorBckGrnd = pSubWindow->GetWidgetManipImage()
                                        .backgroundBrush()
                                        .color();
      QPixmap qPixmapColoredIcon(25, 25);
      qPixmapColoredIcon.fill(qColorBckGrnd);
      m_pqActionColoredBckgr->setIcon(QIcon(qPixmapColoredIcon));
   }
}

void MainWindow::UpdateWidgetManipColor(void)
{
   if (centralWidget() == nullptr)
   {
      return;
   }

   SubWindowActivated(dynamic_cast<MdiArea*>(centralWidget())
                                                         ->activeSubWindow());
}

bool MainWindow::bImageExist(const QString& qstrAbsoluteFilePath) const
{
   if(centralWidget() == nullptr)
   {
      return false;
   }

   QList<QMdiSubWindow*> qlpSubWindow = dynamic_cast<MdiArea*>(centralWidget())
                                                             ->subWindowList();

   foreach(QMdiSubWindow* pMdiSubWindow, qlpSubWindow)
   {
      SubWindow* pSubWindow = dynamic_cast<SubWindow*>(pMdiSubWindow);
      if(pSubWindow->qstrAbsoluteFilePath() == qstrAbsoluteFilePath)
      {
         return true;
      }
   }

   return false;
}

void MainWindow::RedrawAllImage(void)
{
   if(centralWidget() == nullptr)
   {
      return;
   }

   QList<QMdiSubWindow*> qlpSubWindow = dynamic_cast<MdiArea*>(centralWidget())
                                                             ->subWindowList();

   foreach(QMdiSubWindow* pMdiSubWindow, qlpSubWindow)
   {
      dynamic_cast<SubWindow*>(pMdiSubWindow)->Redraw();
   }
}

void MainWindow::CreateDockWindow(void)
{
   /* On crée d'abord un dock widget qui contiendra la description de la */
   /* palette                                                            */
   QDockWidget* pqDockPalette = new QDockWidget(tr("Color"), this);
   pqDockPalette->setFeatures(QDockWidget::NoDockWidgetFeatures);

   m_pqWidgetManipColor = new WidgetManipColor(this);
   pqDockPalette->setWidget(m_pqWidgetManipColor);

   addDockWidget(Qt::RightDockWidgetArea, pqDockPalette);

   /* On ajoute un dock widget pour la messagerie */
   QDockWidget* pqDockMessagerie = new QDockWidget(tr("Messagerie"), this);
   pqDockMessagerie->setFeatures(QDockWidget::NoDockWidgetFeatures);

   m_pqMessagerie = new QListWidget();
   m_pqMessagerie->setSelectionMode(QAbstractItemView::NoSelection);
   pqDockMessagerie->setWidget(m_pqMessagerie);

   addDockWidget(Qt::BottomDockWidgetArea, pqDockMessagerie);

   /* La palette occupe tout le coté droit de l'objet central */
   setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

void MainWindow::CreateCentralWidget(void)
{
   MdiArea* pqMdiArea = new MdiArea(this);
   setCentralWidget(pqMdiArea);
}

void MainWindow::CreateConnection(void)
{
   MdiArea* pqMdiArea = dynamic_cast<MdiArea*>(centralWidget());

   if(pqMdiArea == nullptr)
   {
      CException qException("The central widget has not been created, "
                            "impossible to do the connection",
                            __FILE__,
                            __LINE__);
      throw qException;
   }
   else
   {
      connect(pqMdiArea, &MdiArea::CleanStatusBar,
              this,      &MainWindow::CleanStatusBar);
      connect(pqMdiArea, &QMdiArea::subWindowActivated,
              this,      &MainWindow::SubWindowActivated);
      connect(pqMdiArea,           &QMdiArea::subWindowActivated,
              m_pqWidgetManipColor, &WidgetManipColor::SubWindowActivated);
      connect(pqMdiArea, &MdiArea::NewFileReceived,
              this,      &MainWindow::OpenListFile);
   }

   if(  (m_pqActionCheckedBckgr == nullptr)
      ||(m_pqActionColoredBckgr == nullptr))
   {
      CException qException("The action to colorized the background has not "
                            "yet been defined, impossible to do the "
                            "connection",
                            __FILE__,
                            __LINE__);
      throw qException;
   }
   else
   {
      connect(m_pqActionCheckedBckgr, &QAction::triggered,
              pqMdiArea, &MdiArea::setCheckedBackground);
      connect(m_pqActionColoredBckgr, &QAction::triggered,
              pqMdiArea, &MdiArea::askBackgroundColor);
   }

   if(m_pqMessagerie == nullptr)
   {
      CException qException("The messagerie has not yet been defined, "
                            "impossible to do the connection",
                            __FILE__,
                            __LINE__);
      throw qException;
   }
   else
   {
      connect(this, &MainWindow::SendMsg,
              this, &MainWindow::AddToMessagerie);
   }
}

QImage MainWindow::qExtractImageFromRaw(const QFileInfo& qFileInfo)
{
   // We use the program dcraw to convert the image from CR2 to ppm
   QString qConvertFile(qFileInfo.absolutePath() + "/"
                        + qFileInfo.completeBaseName() + ".ppm");
   QString qInstruction("dcraw " + qFileInfo.absoluteFilePath());

   // On convertie l'image de CR2 à ppm
   int iResult = QProcess::execute(qInstruction);

   if(iResult == -2)
   {
      QListWidgetItem* pqMsg = new QListWidgetItem(
                                 QIcon(":/Icones/IconeErreur.png"),
                                 "L'instruction \"" + qInstruction
                                 + "\" n'a pas pu démarrer");
      emit SendMsg(pqMsg);

      return QImage();
   }
   else if (iResult == -1)
   {
      QListWidgetItem* pqMsg = new QListWidgetItem(
                                 QIcon(":/Icones/IconeErreur.png"),
                                 "L'instruction \"" + qInstruction
                                 + "\" a crasher");
      emit SendMsg(pqMsg);

      return QImage();
   }
   else if (iResult != 0)
   {
      QListWidgetItem* pqMsg = new QListWidgetItem(
                                 QIcon(":/Icones/IconeErreur.png"),
                                 "L'instruction \"" + qInstruction
                                 + "\" a renvoyé le code erreur : "
                                 + QString::number(iResult));
      emit SendMsg(pqMsg);

      return QImage();
   }

   // On créé l'image à partir du fichier convertie
   QImage qImage(qConvertFile);

   // Et on supprime l'image intermédiaire devenue inutile
   QProcess::execute("rm " + qConvertFile);

   return qImage;
}
