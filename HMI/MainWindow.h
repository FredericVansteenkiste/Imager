#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QtWidgets>
#include <QMainWindow>

#include "MdiArea.h"
#include "SubWindow.h"

class SubWindow;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget* pqParent = nullptr);
   virtual ~MainWindow();

public slots:
   void OpenFiles(const QString& qstrFile);

protected:
   virtual void closeEvent(QCloseEvent* pqEvent);

private:
   QMenu*            m_pWindowMenu;
   QActionGroup*     m_pActionsWindowMenu;

   void SetMenuAndToolbar(void);
   void OpenListFile(const QStringList& qlstrListFiles);
   void RedrawAllImage(void);
   void CreateCentralWidget(void);
   void CreateConnection(void);

   // J'interdis toute forme de recopie de ma classe:
   MainWindow(const MainWindow&);
   MainWindow& operator=(const MainWindow&);

private slots:
   void OpenFile(void);
   void About(void);
   void UpdateMenuWindow(SubWindow* pSubWindow);
};

#endif // MAINWINDOW_H
