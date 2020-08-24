#ifndef WidgetManipImage_H
#define WidgetManipImage_H
#pragma once

#include <QtWidgets>

#include "ImageScene.h"
#include "ImageView.h"

class ImageView;
class ImageScene;

class WidgetManipImage : public QObject
{
   Q_OBJECT

public:
   // Constructor, create the scene and set parameters
   explicit WidgetManipImage(QWidget* pParent = nullptr);
   virtual ~WidgetManipImage();

   // Set the image in the widget
   // QImage to display
   void setImage(const QImage& qImage);
   QPixmap qPixmap(void) const;

   // J'indique quelle pinceau utiliser pour le background
   void setBackgroundBrush(const QBrush& qBckgrndBrush);
   QBrush backgroundBrush() const;

   operator QWidget*();

   ImageView* pImageView(void);

private:
   // Scene where the image is drawn
   ImageScene*   m_pqGraphicsScene;
   // View to display the image
   ImageView*    m_pqGraphicsView;

   // J'interdis toute forme de recopie de ma classe:
   WidgetManipImage(const WidgetManipImage&);
   WidgetManipImage& operator=(const WidgetManipImage&);
};

#endif // WidgetManipImage_H
