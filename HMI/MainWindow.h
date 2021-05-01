#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QtWidgets>
#include <QMainWindow>

#include "global.h"
#include "MdiArea.h"
#include "SubWindow.h"
#include "WidgetManipColor/WidgetManipColor.h"
#include "../CException/CException.h"

class WidgetManipColor;
class SubWindow;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget* pqParent = nullptr);
   virtual ~MainWindow();

   WidgetManipColor* pWidgetManipColor(void) const;

public slots:
   void OpenFiles(const QString& qstrFile);
   void UpdateLabelColorPixel(const QString& qstrLabel);
   void AddToMessagerie(QListWidgetItem* pqMessage);

protected:
   virtual void closeEvent(QCloseEvent* pqEvent);

private:
   QAction*          m_pqActionReduceImage;
   QAction*          m_pqActionAppelMacro;
   QAction*          m_pqActionCreatePalette;
   QAction*          m_pqActionSupprPalette;
   QAction*          m_pqActionCheckedBckgr;
   QAction*          m_pqActionColoredBckgr;
   QMenu*            m_pqWindowMenu;
   QActionGroup*     m_pqActionsWindowMenu;
   QLabel*           m_pqLabelCoordMouse;
   QLabel*           m_pqLabelColorPixel;
   WidgetManipColor* m_pqWidgetManipColor;
   QListWidget*      m_pqMessagerie;

   void SetMenuAndToolbar(void);
   void ReadSettings(void);
   void WriteSettings(void) const;
   void OpenListFile(const QStringList& qlstrListFiles);
   void RedrawAllImage(void);
   void CreateDockWindow(void);
   void CreateCentralWidget(void);
   void CreateConnection(void);

   bool bImageExist(const QString& qstrAbsoluteFilePath) const;

   // J'interdis toute forme de recopie de ma classe:
   MainWindow(const MainWindow&);
   MainWindow& operator=(const MainWindow&);

private slots:
   void OpenFile(void);
   void About(void);
   void CheckEnabledActionReduceImage(void);
   void UpdateMenuWindow(SubWindow* pSubWindow);
   void UpdateLabelCoordMouse(const QString& qstrLabel);
   void CleanStatusBar(void);
   void SubWindowActivated(QMdiSubWindow* pMdiSubWindow);
   void UpdateWidgetManipColor(void);

signals:
   void SendMsg(QListWidgetItem* pqMessage);
};

#endif // MAINWINDOW_H
