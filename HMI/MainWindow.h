#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>

#include "SubWindow.h"

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = 0);
   ~MainWindow();

private slots:
   void OpenFile(void);
   void About(void);
   void CheckEnabledActionReduceImage(void);
   void UpdateMenuWindow(SubWindow* pSubWindow);

private:
   QAction* m_pActionReduceImage;
   QMenu*   m_pWindowMenu;

   void SetMenuAndToolbar(void);
   void ReadSettings(void);
   void WriteSettings(void) const;

   bool bImageExist(const QString& qstrAbsoluteFilePath) const;
};

#endif // MAINWINDOW_H
