#ifndef GRAPHICSPIXMAPITEM_H
#define GRAPHICSPIXMAPITEM_H

#include <QtWidgets>

class GraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
   GraphicsPixmapItem(QGraphicsItem* pParent = nullptr);
   GraphicsPixmapItem(const QPixmap& qPixmap,
                      QGraphicsItem* pParent = nullptr);
   virtual ~GraphicsPixmapItem();

   virtual QRectF boundingRect() const;

private:
   // J'interdis toute forme de recopie de ma classe:
   GraphicsPixmapItem(const GraphicsPixmapItem&);
   GraphicsPixmapItem& operator=(const GraphicsPixmapItem&);
};

#endif // GRAPHICSPIXMAPITEM_H
