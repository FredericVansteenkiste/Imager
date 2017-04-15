#include "MainWindow.h"

#define ORGANISATION     ("FredericVansteenkiste")
#define NAME_APPLICATION ("Imager")

MainWindow::MainWindow(QWidget* pqParent):QMainWindow(pqParent),
                                          m_pActionReduceImage(nullptr),
                                          m_pWindowMenu(nullptr),
                                          m_pLabelCoordMouse(nullptr),
                                          m_pLabelColorPixel(nullptr),
                                          m_pLabelSizePicture(nullptr)
{
   SetMenuAndToolbar();

   ReadSettings();

   UpdateLabelCoordMouse(QString());
   UpdateLabelColorPixel(QString());
   UpdateLabelSizePicture(QString());

   QStringList qlstrArguments(qApp->arguments());
   qlstrArguments.removeFirst();
   OpenListFile(qlstrArguments);
}

MainWindow::~MainWindow()
{
   WriteSettings();
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


   m_pActionReduceImage = new QAction(QIcon(":/HMI/Icones/resize.png"),
                                      tr("Resize"),
                                      this);
   m_pActionReduceImage->setDisabled(true);


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

   m_pWindowMenu = menuBar()->addMenu(tr("&Window"));

   QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
   helpMenu->addAction(pActionAbout);

   QToolBar* fileToolBar = addToolBar(tr("File"));
   fileToolBar->addAction(pActionOpen);

   QToolBar* macroToolBar = addToolBar(tr("Macro"));
   macroToolBar->addAction(m_pActionReduceImage);

   m_pLabelCoordMouse = new QLabel("");
   m_pLabelColorPixel = new QLabel("");
   m_pLabelSizePicture = new QLabel("");
   statusBar()->addPermanentWidget(m_pLabelCoordMouse);
   statusBar()->addPermanentWidget(m_pLabelColorPixel);
   statusBar()->addPermanentWidget(m_pLabelSizePicture);
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
   if(pqMdiArea == nullptr)
   {
      pqMdiArea = new MdiArea(this);
      setCentralWidget(pqMdiArea);

      connect(pqMdiArea, &MdiArea::CleanStatusBar,
              this, &MainWindow::CleanStatusBar);
   }

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
      connect(m_pActionReduceImage, &QAction::triggered,
              pSubWindow, &SubWindow::ResizeTransparency);
      pSubWindow->show();

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

      ImageView* pImageView = pSubWindow->GetWidgetManipImage().pImageView();
      connect(pImageView, &ImageView::SizeImage,
              this, &MainWindow::UpdateLabelSizePicture);
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

      return;
   }

   QList<QMdiSubWindow*> qlpSubWindow = dynamic_cast<MdiArea*>(centralWidget())
                                                             ->subWindowList();
   if(qlpSubWindow.isEmpty() == true)
   {
      m_pActionReduceImage->setEnabled(false);
   }
   else
   {
      m_pActionReduceImage->setEnabled(true);
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

void MainWindow::UpdateLabelSizePicture(const QString& qstrLabel)
{
   if(qstrLabel.isEmpty() == true)
   {
      m_pLabelSizePicture->hide();
   }
   else
   {
      m_pLabelSizePicture->setText(qstrLabel);
      m_pLabelSizePicture->show();
   }
}

void MainWindow::CleanStatusBar(void)
{
   m_pLabelCoordMouse->hide();
   m_pLabelColorPixel->hide();
   m_pLabelSizePicture->hide();
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
