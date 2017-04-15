#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QtWidgets>

#include "DisplayImage.h"

class SubWindow : public QMdiSubWindow
{
   Q_OBJECT
public:
   SubWindow(const QFileInfo& qFileInfo, QWidget *parent = 0);
   virtual ~SubWindow();

   QString qstrAbsoluteFilePath(void) const;

   void SetActionSelectImage(QAction* pActionSelectImage);
   QAction* pqActionSelectImage(void);

signals:
   void closeWindow(SubWindow* pSubWindow);

public slots:
   void ResizeTransparency(void);
   void SelectSubWindow(void);

private:
   DisplayImage* m_pqDisplayImage;
   QFileInfo     m_qFileInfo;
   QAction*      m_pActionSelectImage;
};

#endif // SUBWINDOW_H
