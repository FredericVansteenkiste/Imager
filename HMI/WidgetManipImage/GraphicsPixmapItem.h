#ifndef GRAPHICSPIXMAPITEM_H
#define GRAPHICSPIXMAPITEM_H

#include <QtWidgets>

class GraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
   explicit GraphicsPixmapItem(QGraphicsItem* pParent = nullptr);
   explicit GraphicsPixmapItem(const QPixmap& qPixmap,
                               QGraphicsItem* pParent = nullptr);
   virtual ~GraphicsPixmapItem();

   virtual QRectF boundingRect() const override;

   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;   // ??

private:
   // J'interdis toute forme de recopie de ma classe:
   GraphicsPixmapItem(const GraphicsPixmapItem&);
   GraphicsPixmapItem& operator=(const GraphicsPixmapItem&);
};

#endif // GRAPHICSPIXMAPITEM_H
