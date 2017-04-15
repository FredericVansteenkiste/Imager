#include "ImageScene.h"

ImageScene::ImageScene(QWidget* pParent):QGraphicsScene(pParent),
                                         m_pqGraphicsPixmapItem(nullptr)
{
   // Add the default pixmap at startup
   m_pqGraphicsPixmapItem = addPixmap(QPixmap());
}

ImageScene::~ImageScene()
{
}

void ImageScene::setPixmap(const QPixmap& qPixmap)
{
   m_pqGraphicsPixmapItem->setPixmap(qPixmap);
}

QPixmap ImageScene::qPixmap(void) const
{
   return m_pqGraphicsPixmapItem->pixmap();
}

