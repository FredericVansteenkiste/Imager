#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QtWidgets>

#include "WidgetManipImage/WidgetManipImage.h"

class SubWindow : public QMdiSubWindow
{
   Q_OBJECT
public:
   SubWindow(const QFileInfo& qFileInfo,
             const QImage& qImage,
             QWidget *parent = 0);
   virtual ~SubWindow();

   QString qstrAbsoluteFilePath(void) const;

   void SetActionSelectImage(QAction* pActionSelectImage);
   QAction* pqActionSelectImage(void);
   void Redraw(void);
   QPixmap qPixmap(void) const;
   WidgetManipImage& GetWidgetManipImage(void);

signals:
   void closeWindow(SubWindow* pSubWindow);
   void RedrawAllImage(void);

public slots:
   void ResizeTransparency(void);
   void SelectSubWindow(void);

protected:
   virtual void moveEvent(QMoveEvent* pqEvent);
   virtual void resizeEvent(QResizeEvent* pqEvent);

private:
   WidgetManipImage m_WidgetManipImage;
   QFileInfo        m_qFileInfo;
   QAction*         m_pqActionSelectImage;

   // J'interdis toute forme de recopie de ma classe:
   SubWindow(const SubWindow&);
   SubWindow& operator=(const SubWindow&);
};

#endif // SUBWINDOW_H
