#include "WidgetManipImage.h"

WidgetManipImage::WidgetManipImage(bool bIsContextualMenu,
                                   QWidget* pParent):
                                    m_pqGraphicsScene(nullptr),
                                    m_pqGraphicsView(nullptr)
{
   // Create the scene
   m_pqGraphicsScene = new ImageScene(pParent);

   // Create the view and add it to this widget
   m_pqGraphicsView = new ImageView(pParent);

   // Add the scene to the QGraphicsView
   m_pqGraphicsView->setScene(m_pqGraphicsScene);

   // Initialize contextual menu if requested
   if(bIsContextualMenu == true)
   {
      m_pqGraphicsView->setContextMenu();
   }
}

WidgetManipImage::~WidgetManipImage()
{
}

void WidgetManipImage::setImage(const QImage& qImage)
{
   // Update the pixmap in the scene
   QPixmap qPixmap = QPixmap(qImage.size());
   qPixmap.fill(QColor(0x7F, 0x7F, 0x7F));
//   qPixmap.fill(QColor(0x0, 0x0, 0x0, 0x0));
   QPainter qPainter(&qPixmap);
   qPainter.drawPixmap(QPoint(), QPixmap::fromImage(qImage));

   m_pqGraphicsScene->setPixmap(qPixmap);

   // Resize the scene (needed is the new image is smaller)
   m_pqGraphicsScene->setSceneRect(QRect(QPoint(0, 0), qImage.size()));
}

void WidgetManipImage::setImageFromRawData(const uchar* pucData,
                                           int          iWidth,
                                           int          iHeight,
                                           bool         bMirrorHorizontally,
                                           bool         bMirrorVertically)
{
   // Convert data into QImage
   QImage qImage(pucData, iWidth, iHeight, iWidth*3, QImage::Format_RGB888);

   // Update the pixmap in the scene
   QPixmap qPixmap = QPixmap::fromImage(qImage.mirrored(bMirrorHorizontally,
                                                        bMirrorVertically));
   m_pqGraphicsScene->setPixmap(qPixmap);

   // Resize the scene (needed if the new image is smaller)
   m_pqGraphicsScene->setSceneRect(QRect(QPoint(0, 0), qImage.size()));
}

WidgetManipImage::operator QWidget*()
{
   return m_pqGraphicsView;
}
