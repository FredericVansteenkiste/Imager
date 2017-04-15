#ifndef IMAGESCENE_H
#define IMAGESCENE_H

#include <QtWidgets>

class ImageScene : public QGraphicsScene
{
public:
   ImageScene(QWidget* pParent = nullptr);
   virtual ~ImageScene();

   void setPixmap(const QPixmap& qPixmap);
   QPixmap qPixmap(void) const;

private:
   // Pixmap item containing the image
   QGraphicsPixmapItem* m_pqGraphicsPixmapItem;
};

#endif // IMAGESCENE_H
