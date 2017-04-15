#include "DisplayImage.h"

DisplayImage::DisplayImage(bool bIsContextualMenu,
                           QWidget* pParent):
                                    QGraphicsView(pParent),
                                    m_pqGraphicsScene(nullptr),
                                    m_pqGraphicsPixmapItem(nullptr),
                                    m_qImageSize(),
                                    m_dZoomFactor(DEFAULT_ZOOM_FACTOR),
                                    m_dZoomCtrlFactor(DEFAULT_ZOOM_CTRL_FACTOR),
                                    m_qPixmap()
{
   // Create the scene
   m_pqGraphicsScene = new QGraphicsScene();

   // Allow mouse tracking even if no button is pressed
   this->setMouseTracking(true);

   // Add the scene to the QGraphicsView
   this->setScene(m_pqGraphicsScene);

   // Update all the view port when needed, otherwise, the drawInViewPort may
   // experience trouble
   this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

   // When zooming, the view stay centered over the mouse
   this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

   this->setResizeAnchor(QGraphicsView::AnchorViewCenter);

   // Initialize contextual menu if requested
   if(bIsContextualMenu == true)
   {
      setContextMenuPolicy(Qt::CustomContextMenu);
      connect(this, &QWidget::customContextMenuRequested,
              this, &DisplayImage::showContextMenu);
   }

   // Sur windows, je dois désactiver les scrollbars dans les coins de l'image,
   // sinon si j'ouvre un grand nombre d'image j'ai des resizeEvent qui sont
   // continuellement émis. Causes inconnues : à explorer
   // Ce problème n'apparait pas sous Linux; YES vive linux !!!
#ifdef Q_OS_WIN
   // Disable scroll bar to avoid a unwanted resize recursion
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
#endif

   // Add the default pixmap at startup
   m_pqGraphicsPixmapItem = m_pqGraphicsScene->addPixmap(m_qPixmap);
}

DisplayImage::~DisplayImage()
{
   delete m_pqGraphicsPixmapItem;
   delete m_pqGraphicsScene;
}

void DisplayImage::showContextMenu(const QPoint& qPos)
{
   // Get the mouse position in the scene
   QPoint qGlobalPos = mapToGlobal(qPos);

   // Create the menu and add action
   QMenu contextMenu;
   contextMenu.addAction("Reset view", this, SLOT(FitImage()));

   // Display the menu
   contextMenu.exec(qGlobalPos);
}

void DisplayImage::setImage(const QImage& qImage)
{
   // Update the pixmap in the scene
   m_qPixmap = QPixmap(qImage.size());
   m_qPixmap.fill(QColor(0x7F, 0x7F, 0x7F));
   QPainter qPainter(&m_qPixmap);
   qPainter.drawPixmap(QPoint(), QPixmap::fromImage(qImage));

   m_pqGraphicsPixmapItem->setPixmap(m_qPixmap);

   // Resize the scene (needed is the new image is smaller)
   m_pqGraphicsScene->setSceneRect(QRect(QPoint(0, 0), qImage.size()));

   // Store the image size
   m_qImageSize = qImage.size();
}

void DisplayImage::setImageFromRawData(const uchar* pucData,
                                       int          iWidth,
                                       int          iHeight,
                                       bool         bMirrorHorizontally,
                                       bool         bMirrorVertically)
{
   // Convert data into QImage
   QImage qImage(pucData, iWidth, iHeight, iWidth*3, QImage::Format_RGB888);

   // Update the pixmap in the scene
   m_qPixmap = QPixmap::fromImage(qImage.mirrored(bMirrorHorizontally,
                                                  bMirrorVertically));
   m_pqGraphicsPixmapItem->setPixmap(m_qPixmap);

   // Resize the scene (needed if the new image is smaller)
   m_pqGraphicsScene->setSceneRect(QRect(QPoint(0, 0), qImage.size()));

   // Store the image size
   m_qImageSize = qImage.size();
}

void DisplayImage::setZoomFactor(const double dFactor)
{
   m_dZoomFactor = dFactor;
}

void DisplayImage::setZoomCtrlFactor(const double dFactor)
{
   m_dZoomCtrlFactor = dFactor;
}

void DisplayImage::FitImage(void)
{
   // Get current scroll bar policy
   Qt::ScrollBarPolicy eCurrentHorizontalPolicy = horizontalScrollBarPolicy();
   Qt::ScrollBarPolicy eCurrentverticalPolicy = verticalScrollBarPolicy();

   // Disable scroll bar to avoid a margin around the image
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   // Fit the scene in the QGraphicsView
   this->fitInView(m_pqGraphicsScene->sceneRect(), Qt::KeepAspectRatio);

   // Restaure scroll bar policy
   setHorizontalScrollBarPolicy(eCurrentHorizontalPolicy);
   setVerticalScrollBarPolicy(eCurrentverticalPolicy);
}

void DisplayImage::mousePressEvent(QMouseEvent* pqEvent)
{
   // Drag mode : change the cursor's shape
   if(pqEvent->button() == Qt::LeftButton)
   {
      this->setDragMode(QGraphicsView::ScrollHandDrag);
   }

   QGraphicsView::mousePressEvent(pqEvent);
}

void DisplayImage::mouseReleaseEvent(QMouseEvent* pqEvent)
{
   // Exit drag mode : change the cursor's shape
   if(pqEvent->button() == Qt::LeftButton)
   {
      this->setDragMode(QGraphicsView::NoDrag);
   }

   QGraphicsView::mouseReleaseEvent(pqEvent);
}


#ifndef QT_NO_WHEELEVENT

void DisplayImage::wheelEvent(QWheelEvent* pqEvent)
{
   // When zooming, the view stay centered over the mouse
   this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

   double dFactor(0);
   if(pqEvent->modifiers() & Qt::ControlModifier)
   {
      dFactor = m_dZoomCtrlFactor;
   }
   else
   {
      dFactor = m_dZoomFactor;
   }

   if(pqEvent->delta() > 0)
   {
      // Zoom in
      scale(dFactor, dFactor);
   }
   else
   {
      // Zooming out
      scale(1.0 / dFactor, 1.0 / dFactor);
   }

   // The event is processed
   pqEvent->accept();
}

#endif

void DisplayImage::mouseMoveEvent(QMouseEvent* pqEvent)
{
   // Get the coordinates of the mouse in the scene
   QPointF qImagePoint = mapToScene(QPoint(pqEvent->x(), pqEvent->y()));

   // Call the function that create the tool tip
   setToolTip(setToolTipText(QPoint(static_cast<int>(qImagePoint.x()),
                                    static_cast<int>(qImagePoint.y()))));

   // Call the parent's function (for dragging)
   QGraphicsView::mouseMoveEvent(pqEvent);
}

void DisplayImage::drawForeground(QPainter* pqPainter, const QRectF& qRrect)
{
   Q_UNUSED(qRrect)

   // Call the function to draw over the image
   this->drawOnImage(pqPainter,m_qImageSize);

   // Reset transformation and call the function draw in the view port
   pqPainter->resetTransform();

   // Call the function to draw in the view port
   this->drawInViewPort(pqPainter, this->viewport()->size());
}

void DisplayImage::resizeEvent(QResizeEvent* pqEvent)
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
   if(P2.x() > m_pqGraphicsScene->width())
   {
      P2.setX(m_pqGraphicsScene->width());
   }
   if(P2.y() > m_pqGraphicsScene->height())
   {
      P2.setY(m_pqGraphicsScene->height());
   }

   // Fit the previous area in the scene
   this->fitInView(QRect(P1.toPoint(), P2.toPoint()), Qt::KeepAspectRatio);
}

QString DisplayImage::setToolTipText(QPoint qImageCoordinates)
{
   Q_UNUSED(qImageCoordinates);

   return QString("");
}

void DisplayImage::drawOnImage(QPainter* pqPainter, QSize qImageSize)
{
   Q_UNUSED(pqPainter)
   Q_UNUSED(qImageSize)
}

void DisplayImage::drawInViewPort(QPainter* pqPainter, QSize qPortSize)
{
   Q_UNUSED(pqPainter)
   Q_UNUSED(qPortSize)
}
