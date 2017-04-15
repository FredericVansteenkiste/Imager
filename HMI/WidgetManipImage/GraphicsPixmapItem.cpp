#include "GraphicsPixmapItem.h"

GraphicsPixmapItem::GraphicsPixmapItem(QGraphicsItem* pParent):
                                                   QGraphicsPixmapItem(pParent)
{
}

GraphicsPixmapItem::GraphicsPixmapItem(const QPixmap& qPixmap,
                                       QGraphicsItem* pParent):
                                                   QGraphicsPixmapItem(qPixmap,
                                                                       pParent)
{
}

GraphicsPixmapItem::~GraphicsPixmapItem()
{
}

QRectF GraphicsPixmapItem::boundingRect() const
{
   return QRectF(pos(), scale() * QSizeF(pixmap().size()));
}
