#ifndef WIDGETMANIPCOLOR_H
#define WIDGETMANIPCOLOR_H

#include <QtWidgets>

#include "CStateMouse.h"

#define SIZE_BUTTON (25)

class WidgetManipColor : public QWidget
{
public:
   WidgetManipColor(QWidget* pParent = nullptr);
   virtual ~WidgetManipColor();

   void SetSizePalette(const unsigned int& uiSizePalette);
   void SetColorNumber(const unsigned int& uiNbreColor);
   void SetDepth(const unsigned int& uiDepth);
   void SetBitsUsedPerPixel(const unsigned int& uiBitsUsedPerPixel);
   void SetSizeImage(const QSize& qSize);

private:
<<<<<<< HEAD:HMI/WidgetManipColor.h
=======
   CStateMouse  m_StateMachine;

>>>>>>> 79e9d42059e5657067b4a2d31fb2aaeac0daba2f:HMI/WidgetManipColor/WidgetManipColor.h
   QLabel*      m_pqCurrentColor;
   QPushButton* m_pqPen;
   QPushButton* m_pqPipette;

   QLabel*      m_pqSizePalette;       // Size of the used palette if any.
   QLabel*      m_pqColorNumber;       // Number of color in the image.
   QLabel*      m_pqDepth;             // bits per pixel (bpp) (may contain
                                       // unused bits).
   QLabel*      m_pqBitUsedPerPixel;   // bits used to define a pixel.
   QLabel*      m_pqSizeImage;         // Size of the picture.
};

#endif // WIDGETMANIPCOLOR_H
