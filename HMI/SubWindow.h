#ifndef SUBWINDOW_H
#define SUBWINDOW_H
#pragma once

#include <QtWidgets>

#include "WidgetManipImage/WidgetManipImage.h"

class WidgetManipImage;
class MainWindow;

class SubWindow : public QMdiSubWindow
{
   Q_OBJECT
public:
   explicit SubWindow(const QImage& qImage,
                      QWidget* pParent = nullptr);
   virtual ~SubWindow();

   void SetActionSelectImage(QAction* pActionSelectImage);
   QAction* pqActionSelectImage(void);
   void Redraw(void);
   QPixmap qPixmap(void) const;
   QImage  qImage(void) const;
   WidgetManipImage& GetWidgetManipImage(void);

public slots:
   // La méthode suivante répertorie les actions à effectuer lorsque l'image
   // courante est sélectionnée
   void SelectSubWindow(void);

protected:
   virtual void moveEvent(QMoveEvent* pqEvent);
   virtual void resizeEvent(QResizeEvent* pqEvent);
   virtual void mouseMoveEvent(QMouseEvent* pqEvent);
   virtual void closeEvent(QCloseEvent *pqEvent);

private:
   MainWindow*       m_pqMainWindow;
   WidgetManipImage* m_pqWidgetManipImage;
   QImage            m_qImage;
   QAction*          m_pqActionSelectImage;

   // J'interdis toute forme de recopie de ma classe:
   SubWindow(const SubWindow&);
   SubWindow& operator=(const SubWindow&);

signals:
   void closeWindow(SubWindow* pSubWindow);
   void RedrawAllImage(void);
};

#endif // SUBWINDOW_H
