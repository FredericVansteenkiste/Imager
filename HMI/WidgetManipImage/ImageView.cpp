#include "ImageView.h"

ImageView::ImageView(QWidget* pParent):
                                    QGraphicsView(pParent),
                                    m_dZoomFactor(DEFAULT_ZOOM_FACTOR),
                                    m_dZoomCtrlFactor(DEFAULT_ZOOM_CTRL_FACTOR)
{
   // Allow mouse tracking even if no button is pressed
   setMouseTracking(true);

   // Update all the view port when needed, otherwise, the drawInViewPort may
   // experience trouble
   setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
   setOptimizationFlags(DontAdjustForAntialiasing);

   setCacheMode(QGraphicsView::CacheBackground);

   // Sur windows, je dois activer les scrollbars en permance, sinon si j'ouvre
   // un grand nombre d'image j'ai des resizeEvent qui sont continuellement
   // émis. Causes inconnues : à explorer
   // Ce problème n'apparait pas sous Linux; YES vive linux !!!
#ifdef Q_OS_WIN
   // Enable scroll bar to avoid an unwanted resize recursion
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
#endif   // Q_OS_WIN

   setBackgroundBrush(QBrush(QPixmap(ADRESS_CHECKED_BACKGROUND_PICTURE)));
}

ImageView::~ImageView()
{
}

void ImageView::setContextMenu(void)
{
   setContextMenuPolicy(Qt::CustomContextMenu);
   connect(this, &QWidget::customContextMenuRequested,
           this, &ImageView::showContextMenu);
}

void ImageView::setZoomFactor(const double dFactor)
{
   m_dZoomFactor = dFactor;
}

void ImageView::setZoomCtrlFactor(const double dFactor)
{
   m_dZoomCtrlFactor = dFactor;
}

ImageScene* ImageView::pqImageScene(void) const
{
   return dynamic_cast<ImageScene*>(scene());
}

QPointF ImageView::mapToPixmapItem(const QPoint& qCoordView)
{
   return pqImageScene()->mapToPixmapItem(mapToScene(qCoordView));
}

QPoint ImageView::mapFromPixmapItem(const QPointF& qCoordPixmap)
{
   return mapFromScene(pqImageScene()->mapFromPixmapItem(qCoordPixmap));
}

void ImageView::mousePressEvent(QMouseEvent* pqEvent)
{
   // Drag mode : change the cursor's shape
   if(pqEvent->button() == Qt::LeftButton)
   {
      setDragMode(QGraphicsView::ScrollHandDrag);
   }

   QGraphicsView::mousePressEvent(pqEvent);
}

void ImageView::mouseReleaseEvent(QMouseEvent* pqEvent)
{
   // Exit drag mode : change the cursor's shape
   if(pqEvent->button() == Qt::LeftButton)
   {
      this->setDragMode(QGraphicsView::NoDrag);
   }

   QGraphicsView::mouseReleaseEvent(pqEvent);
}


#ifndef QT_NO_WHEELEVENT

void ImageView::wheelEvent(QWheelEvent* pqEvent)
{
   // On vérifie s'il s'agit d'un zoom rapide ou non
   qreal dFactor(0);
   if(pqEvent->modifiers() & Qt::ControlModifier)
   {
      dFactor = m_dZoomCtrlFactor;
   }
   else
   {
      dFactor = m_dZoomFactor;
   }

   // On détermine quelle est la nouvelle valeur du zoom
   qreal dScale(pqImageScene()->dScale());
   qreal dNewScale(0.0);
   if(pqEvent->delta() > 0)
   {
      if(dScale > SCALE_MAX)
      {
         return;
      }

      dNewScale = dScale * dFactor;
      // Je m'assure qu'on repasse par l'unité
      if(  (dNewScale > 1)
         &&(dScale < 1))
      {
         dNewScale = 1;
      }
   }
   else
   {
      if(dScale < (1.0 / SCALE_MAX))
      {
         return;
      }

      dNewScale = dScale / dFactor;
      // Je m'assure qu'on repasse par l'unité
      if(  (dNewScale < 1)
         &&(dScale > 1))
      {
         dNewScale = 1;
      }
   }

   // Je regarde où était la souris sur l'image par rapport au centre de la vue
   QPointF qCoordPixelUnderMouseF = mapToPixmapItem(pqEvent->pos());
   int iWidthView(size().width());
   int iHeightView(size().height());
   // Je prends en compte l'espace qu'occupe les scrollbars
   if(verticalScrollBar()->isVisible() == true)
   {
      iWidthView -= verticalScrollBar()->size().width();
   }
   if(horizontalScrollBar()->isVisible() == true)
   {
      iHeightView -= horizontalScrollBar()->size().height();
   }
   // J'en déduis de combien est décalé la souris par rapport au centre de la
   // vue
   QPointF qDecalageCentre = pqEvent->pos() - QPoint(iWidthView / 2,
                                                     iHeightView / 2);

   // J'applique le zoom que l'on a déterminé
   pqImageScene()->ScaleImage(dNewScale);

   // Je repositionne le centre de la vue afin que la souris reste sur le même
   // pixel.
   QPointF qNewCoordPixelUnderMouseF = pqImageScene()->mapFromPixmapItem(
                                                      qCoordPixelUnderMouseF);
   centerOn(qNewCoordPixelUnderMouseF - qDecalageCentre);

   // J'indique que l'événement est terminé
   // Ici, je n'appelle pas QGraphicsView::wheelEvent(pqEvent) car si je vais
   // dans QGraphicsView::wheelEvent(pqEvent) cela déplacerait la position de
   // l'image sous la souris (comme si les scrollbar avaient bougé).
   pqEvent->accept();
}

#endif

void ImageView::mouseMoveEvent(QMouseEvent* pqEvent)
{
   unsetCursor();

   // On appelle la fonction parente pour les déplacements de l'image
   QGraphicsView::mouseMoveEvent(pqEvent);
}

void ImageView::paintEvent(QPaintEvent* pqEvent)
{
   qDebug() << "Call to the event QGraphicsView::paintEvent()";

   QGraphicsView::paintEvent(pqEvent);
}

QString ImageView::setToolTipText(QPoint qImageCoordinates)
{
   Q_UNUSED(qImageCoordinates);

   return QString("");
}

void ImageView::showContextMenu(const QPoint& qPos)
{
   // Get the mouse position in the scene
   QPoint qGlobalPos = mapToGlobal(qPos);

   // Create the menu and add action
   QMenu contextMenu;
   contextMenu.addAction("Reset zoom", this, &ImageView::ResetZoom);

   // Display the menu
   contextMenu.exec(qGlobalPos);
}

void ImageView::ResetZoom(void)
{
   pqImageScene()->ScaleImage(1);
}

MainWindow* ImageView::pMainWindow(void) const
{
   return dynamic_cast<MainWindow*>(parentWidget()->parentWidget()
                                                  ->parentWidget()
                                                  ->parentWidget());
}

SubWindow* ImageView::pSubWindow(void) const
{
   return dynamic_cast<SubWindow*>(parentWidget());
}
