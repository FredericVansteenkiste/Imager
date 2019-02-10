#include "WidgetManipImage.h"

WidgetManipImage::WidgetManipImage(QWidget* pParent):QObject(),
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

void WidgetManipImage::setBackgroundBrush(const QBrush& qBckgrndBrush)
{
   // J'indique quel arrière plan l'on désire
   m_pqGraphicsView->setBackgroundBrush(qBckgrndBrush);

   // J'indique comment dessiner le cadre autour de l'image
   if(m_pqGraphicsView->backgroundBrush().style() == Qt::TexturePattern)
   {
      // Si l'arrière plan est une image, je mets un cadre en pointillé noir
      m_pqGraphicsScene->pqCadreItem()->setPen(QPen(QBrush(Qt::black,
                                                           Qt::SolidPattern),
                                                    1,
                                                    Qt::DashLine,
                                                    Qt::SquareCap,
                                                    Qt::BevelJoin));
   }
   else
   {
      // Si l'arrière plan est une couleur, je mets l'inverse de la couleur en
      // pointillé
      QColor qBckGrndColor = qBckgrndBrush.color();
      qBckGrndColor.setRed(iRevertColor(qBckGrndColor.red()));
      qBckGrndColor.setBlue(iRevertColor(qBckGrndColor.blue()));
      qBckGrndColor.setGreen(iRevertColor(qBckGrndColor.green()));
      m_pqGraphicsScene->pqCadreItem()->setPen(QPen(QBrush(qBckGrndColor,
                                                           Qt::SolidPattern),
                                                    1,
                                                    Qt::DashLine,
                                                    Qt::SquareCap,
                                                    Qt::BevelJoin));
   }
}

QBrush WidgetManipImage::backgroundBrush() const
{
   return m_pqGraphicsView->backgroundBrush();
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
