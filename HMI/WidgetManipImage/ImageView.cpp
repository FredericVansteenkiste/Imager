#include "ImageView.h"

ImageView::ImageView(QWidget* pParent,
                     QBrush   qBckgrndBrush):
                                    QGraphicsView(pParent),
                                    m_dZoomFactor(DEFAULT_ZOOM_FACTOR),
                                    m_dZoomCtrlFactor(DEFAULT_ZOOM_CTRL_FACTOR)
{
   // // Allow mouse tracking even if no button is pressed
   // setMouseTracking(true);

   // Update all the view port when needed, otherwise, the drawInViewPort may
   // experience trouble
   setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

   setCacheMode(QGraphicsView::CacheBackground);

   // // Sur windows, je dois activer les scrollbars en permance, sinon si j'ouvre
   // // un grand nombre d'image j'ai des resizeEvent qui sont continuellement
   // // émis. Causes inconnues : à explorer
   // // Ce problème n'apparait pas sous Linux; YES vive linux !!!
// #ifdef Q_OS_WIN
   // // Enable scroll bar to avoid an unwanted resize recursion
   // setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   // setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
// #endif   // Q_OS_WIN

   if(qBckgrndBrush == QBrush())
   {
      setBackgroundBrush(QBrush(QPixmap(ADRESS_CHECKED_BACKGROUND_PICTURE)));
   }
   else
   {
      setBackgroundBrush(qBckgrndBrush);
   }

   // // J'installe le filtre sur les événements pour intercepter les événements
   // // arrivant sur les barres de défilement.
   // horizontalScrollBar()->installEventFilter(this);
   // verticalScrollBar()->installEventFilter(this);
}

ImageView::~ImageView()
{
}

// void ImageView::setContextMenu(void)
// {
   // setContextMenuPolicy(Qt::CustomContextMenu);
   // connect(this, &QWidget::customContextMenuRequested,
           // this, &ImageView::showContextMenu);
// }

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
   if(  (pqEvent->button() == Qt::LeftButton)
      &&(eGetStateMouse() == CSubStateMouse::DEFAULT))
   {
      setDragMode(QGraphicsView::ScrollHandDrag);
   }
   else if(  (pqEvent->button() == Qt::LeftButton)
           &&(eGetStateMouse() == CSubStateMouse::PIPETTE))
   {
      // On récupére les coordonnées de la souris dans la scéne
      QPointF qMousePointScene = mapToScene(QPoint(pqEvent->x(), pqEvent->y()));

      // On détermine la position de la souris sur l'image
      QPointF qMousePointItemF = pqImageScene()->mapToPixmapItem(
                                                            qMousePointScene);
      QRectF qRectImageF(QPoint(0, 0),
                         pqImageScene()->qPixmap().size());
      // Si mon pointeur est sur l'image ...
      if(qRectImageF.contains(qMousePointItemF) == true)
      {
         QPoint qMousePointImage(qFloor(qMousePointItemF.x()),
                                 qFloor(qMousePointItemF.y()));
         QImage qImage = pSubWindow()->qImage();
         if(qImage.colorTable().isEmpty())
         {
            QColor qBckgrndColor = pSubWindow()->backgroundBrush().color();
            if(pSubWindow()->backgroundBrush().style() == Qt::TexturePattern)
            {
               qBckgrndColor = Qt::white;
            }
            pMainWindow()->pWidgetManipColor()
                         ->SetCurrentColor(qImage.pixelColor(qMousePointImage),
                                           qBckgrndColor);
         }
         else
         {
            pSubWindow()->pqWidgetPalette()
                        ->SetIndElementSelectionne(
                                          qImage.pixelIndex(qMousePointImage));
         }
      }
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

   // The event is processed
   pqEvent->accept();
}

#endif

void ImageView::mouseMoveEvent(QMouseEvent* pqEvent)
{
   // On indique dans la barre d'état la taille de l'image courante.
   QString qstrLabel("Size = (%1x%2)");
   ImageScene* pScene = pqImageScene();
   qstrLabel = qstrLabel.arg(pScene->qPixmap().size().width())
                        .arg(pScene->qPixmap().size().height());
   emit SizeImage(qstrLabel);

   // On récupére les coordonnées de la souris dans la scéne
   QPointF qMousePointScene = mapToScene(QPoint(pqEvent->x(), pqEvent->y()));

   // On appelle la fonction qui met à jour le tooltip
   setToolTip(setToolTipText(QPoint(static_cast<int>(qMousePointScene.x()),
                                    static_cast<int>(qMousePointScene.y()))));

   // On indique quelle est la position de la souris et le code couleur du pixel
   // correspondant
   QPointF qMousePointItemF = pqImageScene()->mapToPixmapItem(qMousePointScene);
   QRectF qRectImageF(QPoint(0, 0),
                      pqImageScene()->qPixmap().size());
   // Si mon pointeur est sur l'image ...
   if(qRectImageF.contains(qMousePointItemF) == true)
   {
      // ... j'indique quelles sont les coordonnées de la souris (dans le repère
      // de l'image)
      qstrLabel = "Coord = (%1, %2)";
      QPoint qMousePointItem(qFloor(qMousePointItemF.x()),
                             qFloor(qMousePointItemF.y()));
      qstrLabel = qstrLabel.arg(qMousePointItem.x())
                           .arg(qMousePointItem.y());
      emit CoordMouse(qstrLabel);

      // J'indique quelles sont les composantes de la couleur du pixel pointé
      // par la souris
      // Je récupére l'image source courante :
      QImage qImage = dynamic_cast<SubWindow*>(parent())->qImage();
      // Si mon image est palettisé ...
      if(qImage.colorCount() != 0)
      {
         // ... je précise l'index dans la palette et je donne les composants de
         // la couleur ...
         QRgb qPixel = qImage.pixel(qMousePointItem);
         qstrLabel = "\t[%1] => (A = %2 R = %3 G = %4 B = %5)";
         qstrLabel = qstrLabel.arg(qImage.pixelIndex(qMousePointItem))
                              .arg(qAlpha(qPixel))
                              .arg(qRed(qPixel))
                              .arg(qGreen(qPixel))
                              .arg(qBlue(qPixel));
      }
      else
      {
         // ... sinon je précise simplement les composants du pixel
         QRgb qPixel = qImage.pixel(qMousePointItem);
         qstrLabel = "A = %1 R = %2 G = %3 B = %4";
         qstrLabel = qstrLabel.arg(qAlpha(qPixel))
                              .arg(qRed(qPixel))
                              .arg(qGreen(qPixel))
                              .arg(qBlue(qPixel));
      }
      emit ColorPixel(qstrLabel);

      // Je sélectionne le pointeur de souris correspondant à l'état de la
      // machine d'état de WidgetManipColor
      CSubStateMouse::e_state_machine eCurrentState = eGetStateMouse();
      if(eCurrentState == CSubStateMouse::PEN)
      {
         setCursor(QCursor(QPixmap(":/Icones/Pen.png"), 0, 40));
      }
      else if(eCurrentState == CSubStateMouse::PIPETTE)
      {
         setCursor(QCursor(QPixmap(":/Icones/Pipette.png"), 0, 40));
      }
      else
      {
         unsetCursor();
      }
   }
   else
   {
      qstrLabel = "";
      emit CoordMouse(qstrLabel);
      emit ColorPixel(qstrLabel);

      unsetCursor();
   }

   // On appelle la fonction parente pour les déplacements de l'image
   QGraphicsView::mouseMoveEvent(pqEvent);
}

// bool ImageView::eventFilter(QObject* pqObj, QEvent* pqEvent)
// {
   // if(  (pqObj == verticalScrollBar())
      // ||(pqObj == horizontalScrollBar())
      // ||(pqObj == cornerWidget()))
   // {
      // if(pqEvent->type() == QEvent::Enter)
      // {
         // unsetCursor();
      // }

      // return false;
   // }
   // else
   // {
      // // pass the event to the parent class
      // return QGraphicsView::eventFilter(pqObj, pqEvent);
   // }
// }

QString ImageView::setToolTipText(QPoint qImageCoordinates)
{
   Q_UNUSED(qImageCoordinates);

   return QString("");
}

// void ImageView::showContextMenu(const QPoint& qPos)
// {
   // // Get the mouse position in the scene
   // QPoint qGlobalPos = mapToGlobal(qPos);

   // // Create the menu and add action
   // QMenu contextMenu;
   // contextMenu.addAction("Reset zoom", this, &ImageView::ResetZoom);

   // // Display the menu
   // contextMenu.exec(qGlobalPos);
// }

// void ImageView::ResetZoom(void)
// {
   // pqImageScene()->ScaleImage(1);
// }

// La fonction suivante permet de retrouver l'état de la souris.
CSubStateMouse::e_state_machine ImageView::eGetStateMouse(void)
{
   return pMainWindow()->pWidgetManipColor()->eCurrentState();
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
