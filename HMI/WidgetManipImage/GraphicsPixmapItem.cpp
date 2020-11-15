#include "GraphicsPixmapItem.h"

GraphicsPixmapItem::GraphicsPixmapItem(QGraphicsItem* pParent):
                                                   QGraphicsPixmapItem(pParent)
{
   setCacheMode(QGraphicsItem::ItemCoordinateCache);
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

void GraphicsPixmapItem::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget)
{
   qDebug() << "Call to the event GraphicsPixmapItem::paint()" << endl;
   QGraphicsPixmapItem::paint(painter, option, widget);
}
