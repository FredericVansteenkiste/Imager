#ifndef IMAGESCENE_H
#define IMAGESCENE_H

#include <QtWidgets>
#include "GraphicsPixmapItem.h"

class ImageScene : public QGraphicsScene
{
public:
   ImageScene(QWidget* pParent = nullptr);
   virtual ~ImageScene();

   void setPixmap(const QPixmap& qPixmap);
   QPixmap qPixmap(void) const;

   void ScaleImage(const qreal& dScale);
   qreal dScale(void) const;

   GraphicsPixmapItem* pqPixmapItem(void) const;
   QGraphicsRectItem*  pqCadreItem(void) const;

   // La méthode suivante permet de convertir les coordonnées de la scéne en
   // coordonnées de l'image
   QPointF mapToPixmapItem(const QPointF& qCoordScene);
   // La méthode suivante permet de convertir les coordonnées de l'image en
   // coordonnées de la scéne
   QPointF mapFromPixmapItem(const QPointF& qCoordPixmap);

private:
   // Pixmap item containing the image
   GraphicsPixmapItem* m_pqGraphicsPixmapItem;
   QGraphicsRectItem*  m_pqCadreItem;

   // J'interdis toute forme de recopie de ma classe:
   ImageScene(const ImageScene&);
   ImageScene& operator=(const ImageScene&);
};

#endif // IMAGESCENE_H
