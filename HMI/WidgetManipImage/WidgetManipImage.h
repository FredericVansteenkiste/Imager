#ifndef WidgetManipImage_H
#define WidgetManipImage_H

#include <QtWidgets>

#include "ImageScene.h"
#include "ImageView.h"

class WidgetManipImage : public QObject
{
   Q_OBJECT

public:
   // Constructor, create the scene and set parameters
   // When set to true, the contextual menu is initialize
   // If you don't want contextual menu or need to create a
   // custom one, set to false.
   WidgetManipImage(bool bIsContextualMenu = true, QWidget* pParent = nullptr);
   virtual ~WidgetManipImage();


   // Set the image in the widget
   // QImage to display
   void setImage(const QImage& qImage);

   // Set the image from raw data
   // Pointer to the raw data (data format is RGBRGBRGBRGB ...)
   // Size of the image to display
   // The raw data MUST be compliant with the size
   void setImageFromRawData(const uchar* pucData,
                            int iWidth,
                            int iHeight,
                            bool bMirrorHorizontally = false,
                            bool bMirrorVertically = false);

   operator QWidget*();

private:
   // Scene where the image is drawn
   ImageScene*          m_pqGraphicsScene;
   // View to display the image
   ImageView*           m_pqGraphicsView;
};

#endif // WidgetManipImage_H
