#include "MainWindow.h"

#define STR_CURRENT_DIRECTORY "currentDirectory"

MainWindow::MainWindow(QWidget* pqParent):QMainWindow(pqParent),
                                          m_pWindowMenu(nullptr),
                                          m_pActionsWindowMenu(nullptr)
{
   SetMenuAndToolbar();
   CreateCentralWidget();
   CreateConnection();
}

MainWindow::~MainWindow()
{
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

   QAction* pActionExit = new QAction(tr("E&xit"), this);
   pActionExit->setShortcut(QKeySequence::Close);
   connect(pActionExit, &QAction::triggered, this, &MainWindow::close);

   QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addAction(pActionOpen);
   fileMenu->addSeparator();
   fileMenu->addAction(pActionExit);

   m_pWindowMenu = menuBar()->addMenu(tr("&Window"));
   // Je crée un groupe action pour marquer quelles est la fenêtre sélectionnée.
   m_pActionsWindowMenu = new QActionGroup(this);
   m_pActionsWindowMenu->setExclusive(true);

   QToolBar* fileToolBar = addToolBar(tr("File"));
   fileToolBar->addAction(pActionOpen);
}

void MainWindow::OpenFiles(const QString& qstrFile)
{
   QStringList qlstrListFiles = qstrFile.split("\n");

   OpenListFile(qlstrListFiles);
}

void MainWindow::OpenFile(void)
{
   QStringList qlstrListFiles = QFileDialog::getOpenFileNames(
                              this,
                              "Select one or more image files to open",
                              QString(),
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

   // On ajoute les images sélectionnés sur le widget central
   MdiArea* pqMdiArea = dynamic_cast<MdiArea*>(centralWidget());
   foreach(const QString& qstrFile, qlstrListFiles)
   {
      QFileInfo qFileInfo(qstrFile);

      // On crée l'image pour s'assurer que le fichier est correcte
      QImage qImage(qFileInfo.absoluteFilePath());
      if(qImage.isNull() == true)
      {
         continue;
      }

      // On crée un fenêtre avec notre image
      SubWindow* pSubWindow = new SubWindow(qImage, this);
      pqMdiArea->addSubWindow(pSubWindow);

      pSubWindow->show();

      QAction* pActionSelectImage = new QAction(qFileInfo.fileName(), this);
      pActionSelectImage->setCheckable(true);
      connect(pActionSelectImage, &QAction::triggered,
              pSubWindow,         &SubWindow::SelectSubWindow);
      pSubWindow->SetActionSelectImage(pActionSelectImage);
      m_pWindowMenu->addAction(pActionSelectImage);
      m_pActionsWindowMenu->addAction(pActionSelectImage);
      pActionSelectImage->setChecked(true);

      connect(pSubWindow, &SubWindow::closeWindow,
              this,       &MainWindow::UpdateMenuWindow);
      connect(pSubWindow, &SubWindow::RedrawAllImage,
              this,       &MainWindow::RedrawAllImage,
              Qt::QueuedConnection);
   }
}

void MainWindow::About(void)
{
   QMessageBox::about(this,
                      tr("About Application"),
                      tr("<b>VTK Industries</b> : Imager application. Done by "
                         "Frédéric Vansteenkiste"));
}

void MainWindow::UpdateMenuWindow(SubWindow* pSubWindow)
{
   m_pWindowMenu->removeAction(pSubWindow->pqActionSelectImage());
   m_pActionsWindowMenu->removeAction(pSubWindow->pqActionSelectImage());
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

void MainWindow::CreateCentralWidget(void)
{
   MdiArea* pqMdiArea = new MdiArea(this);
   setCentralWidget(pqMdiArea);
}

void MainWindow::CreateConnection(void)
{
   MdiArea* pqMdiArea = dynamic_cast<MdiArea*>(centralWidget());

   connect(pqMdiArea, &MdiArea::NewFileReceived,
           this,      &MainWindow::OpenListFile);
}
