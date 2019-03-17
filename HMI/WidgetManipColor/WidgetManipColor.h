#ifndef WIDGETMANIPCOLOR_H
#define WIDGETMANIPCOLOR_H
#pragma once

#include <QtWidgets>

#include "CStateMouse.h"
#include "WidgetEditColor.h"
#include "../WidgetPalette/WidgetPalette.h"
#include "../SubWindow.h"

#define SIZE_BUTTON (25)

class SubWindow;
class WidgetPalette;

class WidgetManipColor : public QWidget
{
public:
   explicit WidgetManipColor(QWidget* pParent = nullptr);
   virtual ~WidgetManipColor();

   void SetSizePalette(const unsigned int& uiSizePalette);
   void SetColorNumber(const unsigned int& uiNbreColor);
   void SetDepth(const unsigned int& uiDepth);
   void SetBitsUsedPerPixel(const unsigned int& uiBitsUsedPerPixel);
   void SetSizeImage(const QSize& qSize);
   CSubStateMouse::e_state_machine eCurrentState(void) const;

   QHBoxLayout* pqPaletteLayout(void);

public slots:
   void SubWindowActivated(QMdiSubWindow* pqMdiSubWindow);
   void SetCurrentColor(const QColor& qColor,
                        const QColor& qBckGrndColor);

private:
   CStateMouse      m_StateMachine;

   QLabel*          m_pqCurrentColor;
   QPushButton*     m_pqPen;
   QPushButton*     m_pqPipette;

   WidgetEditColor* m_pEditColor;

   QHBoxLayout*     m_pqPaletteLayout;

   QLabel*          m_pqSizePalette;       // Size of the used palette if any.
   QLabel*          m_pqColorNumber;       // Number of color in the image.
   QLabel*          m_pqDepth;             // bits per pixel (bpp) (may contain
                                           // unused bits).
   QLabel*          m_pqBitUsedPerPixel;   // bits used to define a pixel.
   QLabel*          m_pqSizeImage;         // Size of the picture.
};

#endif // WIDGETMANIPCOLOR_H
