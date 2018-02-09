#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QtWidgets>

#include "WidgetManipImage/WidgetManipImage.h"

class WidgetManipImage;

class SubWindow : public QMdiSubWindow
{
   Q_OBJECT
public:
   SubWindow(const QFileInfo& qFileInfo,
             const QImage& qImage,
             QWidget* pParent = nullptr);
   virtual ~SubWindow();

   QString qstrAbsoluteFilePath(void) const;

   void SetActionSelectImage(QAction* pActionSelectImage);
   QAction* pqActionSelectImage(void);
   void Redraw(void);
   QPixmap qPixmap(void) const;
   QImage  qImage(void) const;
   WidgetManipImage& GetWidgetManipImage(void);
   bool bIsPalette(void) const;
   unsigned int uiNbColorDefined(void) const;

signals:
   void closeWindow(SubWindow* pSubWindow);
   void RedrawAllImage(void);
   void CleanStatusBar(void);
   void UpdateWidgetManipColor(void);

public slots:
   void ResizeTransparency(void);
   void AppelMacro(void);
   void CreatePalette(void);
   void SupprPalette(void);
   void SelectSubWindow(void);
   void setCheckedBackground(void);
   void setBackgroundColor(void);

protected:
   virtual void moveEvent(QMoveEvent* pqEvent);
   virtual void resizeEvent(QResizeEvent* pqEvent);
   virtual void mouseMoveEvent(QMouseEvent* pqEvent);

private:
   WidgetManipImage* m_pWidgetManipImage;
   QFileInfo         m_qFileInfo;
   QImage            m_qImage;
   QAction*          m_pqActionSelectImage;
   QColor            m_qCurrentColor;

   // J'interdis toute forme de recopie de ma classe:
   SubWindow(const SubWindow&);
   SubWindow& operator=(const SubWindow&);
};

#endif // SUBWINDOW_H
