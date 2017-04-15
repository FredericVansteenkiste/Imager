#include "WidgetManipImage.h"

WidgetManipImage::WidgetManipImage(QWidget* pParent):
                                    m_pqGraphicsScene(nullptr),
                                    m_pqGraphicsView(nullptr)
{
   // Create the scene
   m_pqGraphicsScene = new ImageScene(pParent);

   // Create the view and add it to this widget
   m_pqGraphicsView = new ImageView(pParent);

   // Add the scene to the QGraphicsView
   m_pqGraphicsView->setScene(m_pqGraphicsScene);

   // Initialize contextual menu
   m_pqGraphicsView->setContextMenu();
}

WidgetManipImage::~WidgetManipImage()
{
}

void WidgetManipImage::setImage(const QImage& qImage)
{
   // Update the pixmap in the scene
   QPixmap qPixmap = QPixmap(qImage.size());
   qPixmap.fill(QColor(0x0, 0x0, 0x0, 0x0));
   QPainter qPainter(&qPixmap);
   qPainter.drawPixmap(QPoint(), QPixmap::fromImage(qImage));

   m_pqGraphicsScene->setPixmap(qPixmap);
}

QPixmap WidgetManipImage::qPixmap(void) const
{
   return m_pqGraphicsScene->qPixmap();
}

WidgetManipImage::operator QWidget*()
{
   return m_pqGraphicsView;
}

ImageView* WidgetManipImage::pImageView(void)
{
   return m_pqGraphicsView;
}
