#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>

#include "MdiArea.h"
#include "SubWindow.h"
#include "WidgetManipColor.h"

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QWidget* pqParent = nullptr);
   ~MainWindow();

public slots:
   void OpenFiles(const QString& qstrFile);

private slots:
   void OpenFile(void);
   void About(void);
   void CheckEnabledActionReduceImage(void);
   void UpdateMenuWindow(SubWindow* pSubWindow);
   void UpdateLabelCoordMouse(const QString& qstrLabel);
   void UpdateLabelColorPixel(const QString& qstrLabel);
   void UpdateLabelSizePicture(const QString& qstrLabel);
   void CleanStatusBar(void);
   virtual void closeEvent(QCloseEvent* pqEvent);
   void SubWindowActivated(QMdiSubWindow* pMdiSubWindow);

private:
   QAction*          m_pActionReduceImage;
   QAction*          m_pActionAppelMacro;
   QMenu*            m_pWindowMenu;
   QLabel*           m_pLabelCoordMouse;
   QLabel*           m_pLabelColorPixel;
   QLabel*           m_pLabelSizePicture;
   WidgetManipColor* m_pWidgetManipColor;

   void SetMenuAndToolbar(void);
   void ReadSettings(void);
   void WriteSettings(void) const;
   void OpenListFile(const QStringList& qlstrListFiles);
   void RedrawAllImage(void);
   void CreateDockWindow(void);
   void CreateCentralWidget(void);

   bool bImageExist(const QString& qstrAbsoluteFilePath) const;

   // J'interdis toute forme de recopie de ma classe:
   MainWindow(const MainWindow&);
   MainWindow& operator=(const MainWindow&);
};

#endif // MAINWINDOW_H
