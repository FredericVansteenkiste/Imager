#include "MainWindow.h"

MainWindow::MainWindow(QWidget* pqParent):QMainWindow(pqParent),
                                          m_pActionReduceImage(nullptr),
                                          m_pActionAppelMacro(nullptr),
                                          m_pActionCreatePalette(nullptr),
                                          m_pActionSupprPalette(nullptr),
                                          m_pActionCheckedBckgr(nullptr),
                                          m_pActionColoredBckgr(nullptr),
                                          m_pWindowMenu(nullptr),
                                          m_pLabelCoordMouse(nullptr),
                                          m_pLabelColorPixel(nullptr),
                                          m_pWidgetManipColor(nullptr)
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
   return m_pWidgetManipColor;
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


   m_pActionReduceImage = new QAction(QIcon(":/Icones/resize.png"),
                                      tr("Resize"),
                                      this);
   m_pActionReduceImage->setDisabled(true);


   m_pActionAppelMacro = new QAction(QIcon(":/Icones/Engrenages.png"),
                                     tr("Macro"),
                                     this);
   m_pActionAppelMacro->setDisabled(true);

   m_pActionCreatePalette = new QAction(
                                    QIcon(":/Icones/CreatePalette.png"),
                                    tr("Creating a palette for the picture(s)"),
                                    this);
   m_pActionCreatePalette->setDisabled(true);

   m_pActionSupprPalette = new QAction(
                              QIcon(":/Icones/DeletePalette.png"),
                              tr("Deleting a palette for the picture(s)"),
                              this);
   m_pActionSupprPalette->setDisabled(true);

   m_pActionCheckedBckgr = new QAction(QIcon(ADRESS_CHECKED_BACKGROUND_PICTURE),
                                       tr("Checked background"),
                                       this);
   m_pActionCheckedBckgr->setDisabled(true);

   QPixmap qPixmapColoredIcon(25, 25);
   qPixmapColoredIcon.fill(QColor(0, 0, 0));
   m_pActionColoredBckgr = new QAction(QIcon(qPixmapColoredIcon),
                                       tr("Colored background"),
                                       this);
   m_pActionColoredBckgr->setDisabled(true);

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
   macroMenu->addAction(m_pActionReduceImage);
   macroMenu->addAction(m_pActionAppelMacro);
   macroMenu->addAction(m_pActionCreatePalette);
   macroMenu->addAction(m_pActionSupprPalette);

   QMenu* bckgrMenu = menuBar()->addMenu(tr("&Background"));
   bckgrMenu->addAction(m_pActionCheckedBckgr);
   bckgrMenu->addAction(m_pActionColoredBckgr);

   m_pWindowMenu = menuBar()->addMenu(tr("&Window"));

   QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
   helpMenu->addAction(pActionAbout);

   QToolBar* fileToolBar = addToolBar(tr("File"));
   fileToolBar->addAction(pActionOpen);

   QToolBar* macroToolBar = addToolBar(tr("Macro"));
   macroToolBar->addAction(m_pActionReduceImage);
   macroToolBar->addAction(m_pActionAppelMacro);
   macroToolBar->addAction(m_pActionCreatePalette);
   macroToolBar->addAction(m_pActionSupprPalette);

   m_pLabelCoordMouse = new QLabel("");
   m_pLabelColorPixel = new QLabel("");
   statusBar()->addPermanentWidget(m_pLabelCoordMouse);
   statusBar()->addPermanentWidget(m_pLabelColorPixel);
}

void MainWindow::ReadSettings(void)
{
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);

   restoreGeometry(qSettings.value("geometry").toByteArray());
}

void MainWindow::WriteSettings(void) const
{
   QSettings qSettings(ORGANISATION, NAME_APPLICATION);

   qSettings.setValue("geometry", saveGeometry());
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
                                 qSettings.value("currentDirectory").toString(),
                                 "Images (*.png *.bmp *.jpg)");

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
   qSettings.setValue("currentDirectory", qFileInfoTmp.absolutePath());

   // On ajoute les images sélectionnés sur le widget central
   MdiArea* pqMdiArea = dynamic_cast<MdiArea*>(centralWidget());
   foreach(const QString& qstrFile, qlstrListFiles)
   {
      if(bImageExist(qstrFile) == true)
      {
         continue;
      }

      QFileInfo qFileInfo(qstrFile);

      // On crée l'image pour s'assurer que le fichier est correcte
      QImage qImage(qFileInfo.absoluteFilePath());
      if(qImage.isNull() == true)
      {
         continue;
      }

      // On crée un fenêtre avec notre image
      SubWindow* pSubWindow = new SubWindow(qFileInfo, qImage, this);
      pqMdiArea->addSubWindow(pSubWindow);

      m_pActionReduceImage->setEnabled(true);
      m_pActionAppelMacro->setEnabled(true);
      m_pActionCreatePalette->setEnabled(true);
      m_pActionSupprPalette->setEnabled(true);
      m_pActionCheckedBckgr->setEnabled(true);
      m_pActionColoredBckgr->setEnabled(true);
      connect(m_pActionReduceImage, &QAction::triggered,
              pSubWindow, &SubWindow::ResizeTransparency);
      connect(m_pActionAppelMacro, &QAction::triggered,
              pSubWindow, &SubWindow::AppelMacro);
      connect(m_pActionCreatePalette, &QAction::triggered,
              pSubWindow, &SubWindow::CreatePalette);
      connect(m_pActionSupprPalette, &QAction::triggered,
              pSubWindow, &SubWindow::SupprPalette);
      pSubWindow->show();

      // Si les scrollbars sont actives, il faut prendre en compte leurs
      // dimensions.
      QSize qSizeSubWindow = pSubWindow->size();
      QScrollBar* pHorScrollBar = pSubWindow->GetWidgetManipImage()
                                             .pImageView()
                                            ->horizontalScrollBar();
      if(pHorScrollBar->isHidden() == false)
      {
         qSizeSubWindow.rheight() += pHorScrollBar->height();
      }
      QScrollBar* pVerScrollBar = pSubWindow->GetWidgetManipImage()
                                             .pImageView()
                                            ->verticalScrollBar();
      if(pVerScrollBar->isHidden() == false)
      {
         qSizeSubWindow.rwidth() += pVerScrollBar->width();
      }
      pSubWindow->resize(qSizeSubWindow);

      QAction* pActionSelectImage = new QAction(qFileInfo.fileName(), this);
      connect(pActionSelectImage, &QAction::triggered,
              pSubWindow, &SubWindow::SelectSubWindow);
      pSubWindow->SetActionSelectImage(pActionSelectImage);
      m_pWindowMenu->addAction(pActionSelectImage);

      connect(pSubWindow, &SubWindow::closeWindow,
              this, &MainWindow::UpdateMenuWindow);
      connect(pSubWindow, &SubWindow::closeWindow,
              this, &MainWindow::CheckEnabledActionReduceImage,
              Qt::QueuedConnection);
      connect(pSubWindow, &SubWindow::RedrawAllImage,
              this, &MainWindow::RedrawAllImage,
              Qt::QueuedConnection);
      connect(pSubWindow, &SubWindow::CleanStatusBar,
              this, &MainWindow::CleanStatusBar);
      connect(pSubWindow, &SubWindow::UpdateWidgetManipColor,
              this, &MainWindow::UpdateWidgetManipColor);

      ImageView* pImageView = pSubWindow->GetWidgetManipImage().pImageView();
      connect(pImageView, &ImageView::CoordMouse,
              this, &MainWindow::UpdateLabelCoordMouse);
      connect(pImageView, &ImageView::ColorPixel,
              this, &MainWindow::UpdateLabelColorPixel);
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
      m_pActionReduceImage->setEnabled(false);
      m_pActionAppelMacro->setEnabled(false);
      m_pActionCreatePalette->setEnabled(false);
      m_pActionSupprPalette->setEnabled(false);
      m_pActionCheckedBckgr->setEnabled(false);
      m_pActionColoredBckgr->setEnabled(false);

      return;
   }

   QList<QMdiSubWindow*> qlpSubWindow = dynamic_cast<MdiArea*>(centralWidget())
                                                             ->subWindowList();
   if(qlpSubWindow.isEmpty() == true)
   {
      m_pActionReduceImage->setEnabled(false);
      m_pActionAppelMacro->setEnabled(false);
      m_pActionCreatePalette->setEnabled(false);
      m_pActionSupprPalette->setEnabled(false);
      m_pActionCheckedBckgr->setEnabled(false);
      m_pActionColoredBckgr->setEnabled(false);
   }
   else
   {
      m_pActionReduceImage->setEnabled(true);
      m_pActionAppelMacro->setEnabled(true);
      m_pActionCreatePalette->setEnabled(true);
      m_pActionSupprPalette->setEnabled(true);
      m_pActionCheckedBckgr->setEnabled(true);
      m_pActionColoredBckgr->setEnabled(true);
   }
}

void MainWindow::UpdateMenuWindow(SubWindow* pSubWindow)
{
   m_pWindowMenu->removeAction(pSubWindow->pqActionSelectImage());
}

void MainWindow::UpdateLabelCoordMouse(const QString& qstrLabel)
{
   if(qstrLabel.isEmpty() == true)
   {
      m_pLabelCoordMouse->hide();
   }
   else
   {
      m_pLabelCoordMouse->setText(qstrLabel);
      m_pLabelCoordMouse->show();
   }
}

void MainWindow::UpdateLabelColorPixel(const QString& qstrLabel)
{
   if(qstrLabel.isEmpty() == true)
   {
      m_pLabelColorPixel->hide();
   }
   else
   {
      m_pLabelColorPixel->setText(qstrLabel);
      m_pLabelColorPixel->show();
   }
}

void MainWindow::CleanStatusBar(void)
{
   m_pLabelCoordMouse->hide();
   m_pLabelColorPixel->hide();
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
         disconnect(pSubWindow, 0, 0, 0);
      }
   }

   QMainWindow::closeEvent(pqEvent);
}

void MainWindow::SubWindowActivated(QMdiSubWindow* pMdiSubWindow)
{
   if(pMdiSubWindow == nullptr)
   {
      m_pWidgetManipColor->hide();
   }
   else
   {
      SubWindow* pSubWindow = dynamic_cast<SubWindow*>(pMdiSubWindow);
      m_pWidgetManipColor->SetSizePalette(pSubWindow->qImage().colorCount());
      m_pWidgetManipColor->SetColorNumber(pSubWindow->uiNbColorDefined());
      m_pWidgetManipColor->SetDepth(pSubWindow->qImage().depth());
      m_pWidgetManipColor->SetBitsUsedPerPixel(
                                       pSubWindow->qImage().bitPlaneCount());
      m_pWidgetManipColor->SetSizeImage(pSubWindow->qImage().size());
      m_pWidgetManipColor->show();

      QColor qColorBckGrnd = pSubWindow->GetWidgetManipImage()
                                        .backgroundBrush()
                                        .color();
      QPixmap qPixmapColoredIcon(25, 25);
      qPixmapColoredIcon.fill(qColorBckGrnd);
      m_pActionColoredBckgr->setIcon(QIcon(qPixmapColoredIcon));
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
   QDockWidget* pqDock = new QDockWidget(tr("Color"), this);
   pqDock->setFeatures(QDockWidget::NoDockWidgetFeatures);

   m_pWidgetManipColor = new WidgetManipColor(this);
   pqDock->setWidget(m_pWidgetManipColor);

   addDockWidget(Qt::RightDockWidgetArea, pqDock);
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
      CExceptionMessagerie Msg(QIcon(":/Icones/IconeErreur.png"),
                               "The central widget has not been created, "
                               "impossible to do the connection",
                               __FILE__,
                               __LINE__);
      throw Msg;
   }
   else
   {
      connect(pqMdiArea, &MdiArea::CleanStatusBar,
              this, &MainWindow::CleanStatusBar);
      connect(pqMdiArea, &QMdiArea::subWindowActivated,
              this, &MainWindow::SubWindowActivated);
      connect(pqMdiArea, &QMdiArea::subWindowActivated,
              m_pWidgetManipColor, &WidgetManipColor::subWindowActivated);
      connect(pqMdiArea, &MdiArea::NewFileReceived,
              this, &MainWindow::OpenListFile);
   }

   if(  (m_pActionCheckedBckgr == nullptr)
      ||(m_pActionColoredBckgr == nullptr))
   {
      CExceptionMessagerie Msg(QIcon(":/Icones/IconeErreur.png"),
                               "The action to colorized the background has not "
                               "yet been defined, impossible to do the "
                               "connection",
                               __FILE__,
                               __LINE__);
      throw Msg;
   }
   else
   {
      connect(m_pActionCheckedBckgr, &QAction::triggered,
              pqMdiArea, &MdiArea::setCheckedBackground);
      connect(m_pActionColoredBckgr, &QAction::triggered,
              pqMdiArea, &MdiArea::askBackgroundColor);
   }
}
