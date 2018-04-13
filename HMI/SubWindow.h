#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QtWidgets>

#include "WidgetManipImage/WidgetManipImage.h"
#include "WidgetManipColor/WidgetPalette/WidgetPalette.h"

class WidgetManipImage;
class WidgetPalette;

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
   WidgetPalette* pqWidgetPalette(void) const;
   unsigned int uiNbColorDefined(void) const;
   void askBackgroundColor(void);
   void setBackgroundColor(const QColor& qColor);
   void setCheckedBackground(void);

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

protected:
   virtual void moveEvent(QMoveEvent* pqEvent);
   virtual void resizeEvent(QResizeEvent* pqEvent);
   virtual void mouseMoveEvent(QMouseEvent* pqEvent);
   virtual void closeEvent(QCloseEvent *event);

private:
   WidgetManipImage* m_pqWidgetManipImage;
   WidgetPalette*    m_pqWidgetPalette;
   QHBoxLayout*      m_pqPaletteLayout;
   QFileInfo         m_qFileInfo;
   QImage            m_qImage;
   QAction*          m_pqActionSelectImage;
   QColor            m_qCurrentColor;

   // J'interdis toute forme de recopie de ma classe:
   SubWindow(const SubWindow&);
   SubWindow& operator=(const SubWindow&);
};

#endif // SUBWINDOW_H
