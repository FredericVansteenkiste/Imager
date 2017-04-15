#ifndef WIDGETMANIPCOLOR_H
#define WIDGETMANIPCOLOR_H

#include <QtWidgets>

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
   QLabel* m_pqSizePalette;      // Size of the used palette if any
   QLabel* m_pqColorNumber;      // Number of color in the image
   QLabel* m_pqDepth;            // bits per pixel (bpp) (may contain unused
                                 // bits)
   QLabel* m_pqBitUsedPerPixel;  // bits used to define a pixel
   QLabel* m_pqSizeImage;
};

#endif // WIDGETMANIPCOLOR_H
