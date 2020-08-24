#include "ImageScene.h"

ImageScene::ImageScene(QWidget* pParent):QGraphicsScene(pParent),
                                         m_pqGraphicsPixmapItem(nullptr)
{
   // Add the default pixmap at startup
   m_pqGraphicsPixmapItem = new GraphicsPixmapItem(QPixmap());
   addItem(m_pqGraphicsPixmapItem);
}

ImageScene::~ImageScene()
{
}

void ImageScene::setPixmap(const QPixmap& qPixmap)
{
   m_pqGraphicsPixmapItem->setPixmap(qPixmap);
   ScaleImage(dScale());
}

QPixmap ImageScene::qPixmap(void) const
{
   return m_pqGraphicsPixmapItem->pixmap();
}

void ImageScene::ScaleImage(const qreal& dScale)
{
   m_pqGraphicsPixmapItem->setScale(dScale);
   QSizeF qSizeItem =   dScale
                      * QSizeF(m_pqGraphicsPixmapItem->pixmap().size());
   m_pqGraphicsPixmapItem->setPos(-0.5 * qSizeItem.width(),
                                  -0.5 * qSizeItem.height());
   setSceneRect(m_pqGraphicsPixmapItem->boundingRect());
}

qreal ImageScene::dScale(void) const
{
   return m_pqGraphicsPixmapItem->scale();
}

GraphicsPixmapItem* ImageScene::pqPixmapItem(void) const
{
   return m_pqGraphicsPixmapItem;
}

QPointF ImageScene::mapToPixmapItem(const QPointF& qCoordScene)
{
   return m_pqGraphicsPixmapItem->mapFromScene(qCoordScene);
}

QPointF ImageScene::mapFromPixmapItem(const QPointF& qCoordPixmap)
{
   return m_pqGraphicsPixmapItem->mapToScene(qCoordPixmap);
}
