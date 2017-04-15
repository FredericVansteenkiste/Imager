#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>

#include "SubWindow.h"

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QWidget* pqParent = nullptr);
   ~MainWindow();

private slots:
   void OpenFile(void);
   void About(void);
   void CheckEnabledActionReduceImage(void);
   void UpdateMenuWindow(SubWindow* pSubWindow);
   void UpdateLabelCoordMouse(const QString& qstrLabel);
   void UpdateLabelColorPixel(const QString& qstrLabel);
   void UpdateLabelSizePicture(const QString& qstrLabel);
   virtual void closeEvent(QCloseEvent* pqEvent);

private:
   QAction* m_pActionReduceImage;
   QMenu*   m_pWindowMenu;
   QLabel*  m_pLabelCoordMouse;
   QLabel*  m_pLabelColorPixel;
   QLabel*  m_pLabelSizePicture;

   void SetMenuAndToolbar(void);
   void ReadSettings(void);
   void WriteSettings(void) const;
   void OpenListFile(const QStringList& qlstrListFiles);
   void RedrawAllImage(void);

   bool bImageExist(const QString& qstrAbsoluteFilePath) const;

   // J'interdis toute forme de recopie de ma classe:
   MainWindow(const MainWindow&);
   MainWindow& operator=(const MainWindow&);
};

#endif // MAINWINDOW_H
