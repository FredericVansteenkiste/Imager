#include "MainWindow.h"

#define ORGANISATION     ("FredericVansteenkiste")
#define NAME_APPLICATION ("Imager")

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),
                                        m_pActionReduceImage(nullptr),
                                        m_pWindowMenu(nullptr)
{
   SetMenuAndToolbar();

   ReadSettings();
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
   QAction* pActionOpen = new QAction(pqStyle->standardIcon(QStyle::SP_DirOpenIcon),
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

   if(qlstrListFiles.isEmpty() == true)
   {
      return;
   }

   QFileInfo qFileInfoTmp(qlstrListFiles.first());
   qSettings.setValue("currentDirectory", qFileInfoTmp.absolutePath());

   // On ajoute les images sélectionnés sur le widget central
   QMdiArea* pqMdiArea = dynamic_cast<QMdiArea*>(centralWidget());
   if(pqMdiArea == nullptr)
   {
      pqMdiArea = new QMdiArea(this);
      setCentralWidget(pqMdiArea);
   }

   foreach(const QString& qstrFile, qlstrListFiles)
   {
      if(bImageExist(qstrFile) == true)
      {
         continue;
      }

      QFileInfo qFileInfo(qstrFile);

      // ?? Un peu tordue : on crée l'image pour voir si on pourra la crée dans
      // la sous-fenêtre. Donc on crée deux fois l'image; il y a surement mieux
      // à faire ...
      QImage qImageTemp(qFileInfo.absoluteFilePath());
      if(qImageTemp.isNull() == true)
      {
         continue;
      }

      // On crée un fenêtre avec notre image
      SubWindow* pSubWindow = new SubWindow(qFileInfo, this);
      pqMdiArea->addSubWindow(pSubWindow);
      m_pActionReduceImage->setEnabled(true);
      connect(m_pActionReduceImage, &QAction::triggered,
              pSubWindow, &SubWindow::ResizeTransparency);
      connect(pSubWindow, &SubWindow::closeWindow,
              this, &MainWindow::CheckEnabledActionReduceImage,
              Qt::QueuedConnection);
      pSubWindow->show();

      QAction* pActionSelectImage = new QAction(qFileInfo.fileName(), this);
      connect(pActionSelectImage, &QAction::triggered,
              pSubWindow, &SubWindow::SelectSubWindow);
      connect(pSubWindow, &SubWindow::closeWindow,
              this, &MainWindow::UpdateMenuWindow);
      pSubWindow->SetActionSelectImage(pActionSelectImage);
      m_pWindowMenu->addAction(pActionSelectImage);
   }
}

void MainWindow::About(void)
{
   QMessageBox::about(this,
                      tr("About Application"),
                      tr("<b>AGCO corp.</b> : Imager application. Done by "
                         "Frédéric Vansteenkiste"));
}

void MainWindow::CheckEnabledActionReduceImage(void)
{
   if(centralWidget() == nullptr)
   {
      m_pActionReduceImage->setEnabled(false);

      return;
   }

   QList<QMdiSubWindow*> qlpSubWindow = dynamic_cast<QMdiArea*>(centralWidget())
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

bool MainWindow::bImageExist(const QString& qstrAbsoluteFilePath) const
{
   if(centralWidget() == nullptr)
   {
      return false;
   }

   QList<QMdiSubWindow*> qlpSubWindow = dynamic_cast<QMdiArea*>(centralWidget())
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
