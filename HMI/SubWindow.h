#ifndef SUBWINDOW_H
#define SUBWINDOW_H
#pragma once

#include <QtWidgets>

#include "WidgetManipImage/WidgetManipImage.h"
#include "WidgetPalette/WidgetPalette.h"

class WidgetManipImage;
class WidgetPalette;
class MainWindow;

class SubWindow : public QMdiSubWindow
{
   Q_OBJECT
public:
   explicit SubWindow(const QFileInfo& qFileInfo,
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
   QBrush backgroundBrush(void) const;

public slots:
   // La méthode suivante permet de retirer les parties superflues d'une image
   // transparente en ressérant les bords de l'image
   void ResizeTransparency(void);
   // Macro
   void AppelMacro(void);
   // La méthode suivante crée une palette pour l'image courante
   void CreatePalette(void);
   // La méthode suivante détruit la palette de l'image courante
   void SupprPalette(void);
   // La méthode suivante répertorie les actions à effectuer lorsque l'image
   // courante est sélectionnée
   void SelectSubWindow(void);

protected:
   virtual void moveEvent(QMoveEvent* pqEvent);
   virtual void resizeEvent(QResizeEvent* pqEvent);
   virtual void mouseMoveEvent(QMouseEvent* pqEvent);
   virtual void closeEvent(QCloseEvent *event);

private:
   MainWindow*       m_pqMainWindow;
   WidgetManipImage* m_pqWidgetManipImage;
   WidgetPalette*    m_pqWidgetPalette;
   QFileInfo         m_qFileInfo;
   QImage            m_qImage;
   QAction*          m_pqActionSelectImage;

   // J'interdis toute forme de recopie de ma classe:
   SubWindow(const SubWindow&);
   SubWindow& operator=(const SubWindow&);

signals:
   void closeWindow(SubWindow* pSubWindow);
   void RedrawAllImage(void);
   void CleanStatusBar(void);
   void UpdateWidgetManipColor(void);
};

#endif // SUBWINDOW_H
