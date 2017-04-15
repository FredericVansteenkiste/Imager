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

   // When zooming, the view stay centered over the mouse
   setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

   setResizeAnchor(QGraphicsView::AnchorViewCenter);

   // Sur windows, je dois désactiver les scrollbars dans les coins de l'image,
   // sinon si j'ouvre un grand nombre d'image j'ai des resizeEvent qui sont
   // continuellement émis. Causes inconnues : à explorer
   // Ce problème n'apparait pas sous Linux; YES vive linux !!!
#ifdef Q_OS_WIN
   // Disable scroll bar to avoid an unwanted resize recursion
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
#endif

   setBackgroundBrush(QBrush(QPixmap(ADRESS_BACKGROUND_PICTURE)));
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
   // When zooming, the view stay centered over the mouse
   setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

   qreal dFactor(0);
   if(pqEvent->modifiers() & Qt::ControlModifier)
   {
      dFactor = m_dZoomCtrlFactor;
   }
   else
   {
      dFactor = m_dZoomFactor;
   }

   QTransform qTransform = transform();
   qreal dScale(qTransform.m11());
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

   qTransform.setMatrix(     dNewScale, qTransform.m12(), qTransform.m13(),
                      qTransform.m21(),        dNewScale, qTransform.m23(),
                      qTransform.m31(), qTransform.m32(), qTransform.m33());

   // Zoom in
   setTransform(qTransform);

   // On redessine le fond de l'écran
   QPixmap qPixmapBackground(ADRESS_BACKGROUND_PICTURE);
   qPixmapBackground = qPixmapBackground.scaled(
                                          qPixmapBackground.size() / dNewScale);
   setBackgroundBrush(QBrush(qPixmapBackground));

   // The event is processed
   pqEvent->accept();
}

#endif

void ImageView::mouseMoveEvent(QMouseEvent* pqEvent)
{
   // Get the coordinates of the mouse in the scene
   QPointF qImagePoint = mapToScene(QPoint(pqEvent->x(), pqEvent->y()));

   // Call the function that create the tool tip
   setToolTip(setToolTipText(QPoint(static_cast<int>(qImagePoint.x()),
                                    static_cast<int>(qImagePoint.y()))));

   // Call the parent's function (for dragging)
   QGraphicsView::mouseMoveEvent(pqEvent);
}

void ImageView::drawForeground(QPainter* pqPainter, const QRectF& qRrect)
{
   Q_UNUSED(qRrect)

   ImageScene* pScene = dynamic_cast<ImageScene*>(scene());

   if(pScene == nullptr)
   {
      return;
   }

   // Call the function to draw over the image
   drawOnImage(pqPainter, pScene->qPixmap().size());

   // Reset transformation and call the function draw in the view port
   pqPainter->resetTransform();

   // Call the function to draw in the view port
   drawInViewPort(pqPainter, viewport()->size());
}

void ImageView::resizeEvent(QResizeEvent* pqEvent)
{
   // First call, the scene is created
   if(  (pqEvent->oldSize().width()  == -1)
      ||(pqEvent->oldSize().height() == -1))
   {
      return;
   }

   // Get the previous rectangle of the scene in the viewport
   QPointF P1 = mapToScene(QPoint(0,0));
   QPointF P2 = mapToScene(QPoint(pqEvent->oldSize().width(),
                                  pqEvent->oldSize().height()));

   // Stretch the rectangle around the scene
   if(P1.x() < 0)
   {
      P1.setX(0);
   }
   if(P1.y() < 0)
   {
      P1.setY(0);
   }
   if(P2.x() > scene()->width())
   {
      P2.setX(scene()->width());
   }
   if(P2.y() > scene()->height())
   {
      P2.setY(scene()->height());
   }

   // Fit the previous area in the scene
   this->fitInView(QRect(P1.toPoint(), P2.toPoint()), Qt::KeepAspectRatio);
}

QString ImageView::setToolTipText(QPoint qImageCoordinates)
{
   Q_UNUSED(qImageCoordinates);

   return QString("");
}

void ImageView::drawOnImage(QPainter* pqPainter, QSize qImageSize)
{
   Q_UNUSED(pqPainter)
   Q_UNUSED(qImageSize)
}

void ImageView::drawInViewPort(QPainter* pqPainter, QSize qPortSize)
{
   Q_UNUSED(pqPainter)
   Q_UNUSED(qPortSize)
}

void ImageView::showContextMenu(const QPoint& qPos)
{
   // Get the mouse position in the scene
   QPoint qGlobalPos = mapToGlobal(qPos);

   // Create the menu and add action
   QMenu contextMenu;
   contextMenu.addAction("Reset view", this, SLOT(FitImage()));

   // Display the menu
   contextMenu.exec(qGlobalPos);
}

void ImageView::FitImage(void)
{
   // Get current scroll bar policy
   Qt::ScrollBarPolicy eCurrentHorizontalPolicy = horizontalScrollBarPolicy();
   Qt::ScrollBarPolicy eCurrentverticalPolicy = verticalScrollBarPolicy();

   // Disable scroll bar to avoid a margin around the image
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   // Fit the scene in the QGraphicsView
   fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);

   // Restaure scroll bar policy
   setHorizontalScrollBarPolicy(eCurrentHorizontalPolicy);
   setVerticalScrollBarPolicy(eCurrentverticalPolicy);
}
