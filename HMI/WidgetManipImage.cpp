#include "WidgetManipImage.h"

WidgetManipImage::WidgetManipImage(const QImage& qImage,
                                   const QBrush& qBckgrndBrush,
                                   QWidget* pParent):
                                                QAbstractScrollArea(pParent),
                                                m_qImage(qImage),
                                                m_qBckgrndBrush(),
                                                m_qPenCadre(),
                                                m_qTopLeftCorner(),
                                                m_dScale(1),
                                                m_qCoordMouseClicked()
{
   // Allow mouse tracking even if no button is pressed
   setMouseTracking(true);

   // J'appel setBackgroundBrush() au lieu d'initialiser directement dans le
   // constructeur pour qu'il y ait une mise à jour de m_qPenCadre en fonction
   // de m_qBckgrndBrush.
   setBackgroundBrush(qBckgrndBrush);

   // Initialize contextual menu
   setContextMenu();

   // J'installe le filtre sur les événements pour intercepter les événements
   // arrivant sur les barres de défilement.
   horizontalScrollBar()->installEventFilter(this);
   verticalScrollBar()->installEventFilter(this);
}

WidgetManipImage::~WidgetManipImage()
{
}

void WidgetManipImage::SetImage(const QImage& qImage)
{
   m_qImage = qImage;

   viewport()->update();
}

QImage& WidgetManipImage::qImage(void)
{
   return m_qImage;
}


void WidgetManipImage::setBackgroundBrush(const QBrush& qBckgrndBrush)
{
   // J'indique quel arrière plan l'on désire
   m_qBckgrndBrush = qBckgrndBrush;

   // J'indique comment dessiner le cadre autour de l'image
   if(m_qBckgrndBrush.style() == Qt::TexturePattern)
   {
      // Si l'arrière plan est une image, je mets un cadre en pointillé noir
      m_qPenCadre = QPen(QBrush(Qt::black,
                                Qt::SolidPattern),
                         1,
                         Qt::DashLine,
                         Qt::SquareCap,
                         Qt::BevelJoin);
   }
   else
   {
      // Si l'arrière plan est une couleur, je mets l'inverse de la couleur en
      // pointillé
      QColor qBckGrndColor = m_qBckgrndBrush.color();
      qBckGrndColor.setRed(iRevertColor(qBckGrndColor.red()));
      qBckGrndColor.setBlue(iRevertColor(qBckGrndColor.blue()));
      qBckGrndColor.setGreen(iRevertColor(qBckGrndColor.green()));
      m_qPenCadre = QPen(QBrush(qBckGrndColor,
                                Qt::SolidPattern),
                         1,
                         Qt::DashLine,
                         Qt::SquareCap,
                         Qt::BevelJoin);
   }

   viewport()->update();
}

QBrush WidgetManipImage::backgroundBrush() const
{
   return m_qBckgrndBrush;
}

void WidgetManipImage::mousePressEvent(QMouseEvent* pqEvent)
{
   // Drag mode : change the cursor's shape
   if(  (pqEvent->button() == Qt::LeftButton)
      &&(eGetStateMouse() == CSubStateMouse::DEFAULT)
      &&(IsPointWidgetInImage(pqEvent->pos())))
   {
      m_qCoordMouseClicked = pqEvent->pos();
      setCursor(Qt::DragMoveCursor);
   }
   else if(  (pqEvent->button() == Qt::LeftButton)
           &&(eGetStateMouse() == CSubStateMouse::PIPETTE))
   {
      // Si mon pointeur est sur l'image ...
      if(IsPointWidgetInImage(pqEvent->pos()))
      {
         QPointF qMousePointImageF = qMapWidgetToImage(pqEvent->pos());
         QPoint  qMousePointImage(qFloor(qMousePointImageF.rx()),
                                  qFloor(qMousePointImageF.ry()));
         if(m_qImage.colorTable().isEmpty())
         {
            QColor qBckgrndColor = m_qBckgrndBrush.color();
            if(m_qBckgrndBrush.style() == Qt::TexturePattern)
            {
               qBckgrndColor = Qt::white;
            }
            pMainWindow()->pWidgetManipColor()
                         ->SetCurrentColor(
                                          m_qImage.pixelColor(qMousePointImage),
                                          qBckgrndColor);
         }
         else
         {
            pSubWindow()->pqWidgetPalette()
                        ->SetIndElementSelectionne(
                                       m_qImage.pixelIndex(qMousePointImage));
         }
      }
   }

   QAbstractScrollArea::mousePressEvent(pqEvent);
}

void WidgetManipImage::mouseMoveEvent(QMouseEvent* pqEvent)
{
   QString qstrLabel;

   // On récupére les coordonnées de la souris dans l'image
   QPointF qMousePointInWidgetF(pqEvent->pos());
   QPointF qMousePointInImageF = qMapWidgetToImage(qMousePointInWidgetF);

   // On indique quelle est la position de la souris et le code couleur du pixel
   // correspondant
   // Si mon pointeur est sur l'image ...
   if(IsPointWidgetInImage(pqEvent->pos()))
   {
      // ... j'indique quelles sont les coordonnées de la souris (dans le repère
      // de l'image)
      qstrLabel = "Coord = (%1, %2)";
      QPoint qMousePointInImage(qFloor(qMousePointInImageF.x()),
                                qFloor(qMousePointInImageF.y()));
      qstrLabel = qstrLabel.arg(qMousePointInImage.x())
                           .arg(qMousePointInImage.y());
      emit CoordMouse(qstrLabel);

      // J'indique quelles sont les composantes de la couleur du pixel pointé
      // par la souris
      // Si mon image est palettisé ...
      if(m_qImage.colorCount() != 0)
      {
         // ... je précise l'index dans la palette et je donne les composants de
         // la couleur ...
         QRgb qPixel = m_qImage.pixel(qMousePointInImage);
         qstrLabel = "\t[%1] => (A = %2 R = %3 G = %4 B = %5)";
         qstrLabel = qstrLabel.arg(m_qImage.pixelIndex(qMousePointInImage))
                              .arg(qAlpha(qPixel))
                              .arg(qRed(qPixel))
                              .arg(qGreen(qPixel))
                              .arg(qBlue(qPixel));
      }
      else
      {
         // ... sinon je précise simplement les composants du pixel
         QRgb qPixel = m_qImage.pixel(qMousePointInImage);
         qstrLabel = "A = %1 R = %2 G = %3 B = %4";
         qstrLabel = qstrLabel.arg(qAlpha(qPixel))
                              .arg(qRed(qPixel))
                              .arg(qGreen(qPixel))
                              .arg(qBlue(qPixel));
      }
      emit ColorPixel(qstrLabel);

      // Je sélectionne le pointeur de souris correspondant à l'état de la
      // machine d'état de WidgetManipColor et je déplace l'image si nécessaire
      CSubStateMouse::e_state_machine eCurrentState = eGetStateMouse();
      if(eCurrentState == CSubStateMouse::PEN)
      {
         setCursor(QCursor(QPixmap(":/Icones/Pen.png"), 0, 40));
      }
      else if(eCurrentState == CSubStateMouse::PIPETTE)
      {
         setCursor(QCursor(QPixmap(":/Icones/Pipette.png"), 0, 40));
      }
      else if(  (eCurrentState == CSubStateMouse::DEFAULT)
              &&(cursor() == Qt::DragMoveCursor))
      {
         m_qTopLeftCorner += (pqEvent->pos() - m_qCoordMouseClicked);
         m_qCoordMouseClicked = pqEvent->pos();
         CheckCoordTopLeftImage();
         viewport()->update();
         CheckScroolBar();
      }
   }
   else
   {
      qstrLabel = "";
      emit CoordMouse(qstrLabel);
      emit ColorPixel(qstrLabel);

      unsetCursor();
   }

   pqEvent->accept();
}

void WidgetManipImage::mouseReleaseEvent(QMouseEvent* pqEvent)
{
   // Exit drag mode : change the cursor's shape
   if(  (pqEvent->button() == Qt::LeftButton)
      &&(eGetStateMouse() == CSubStateMouse::DEFAULT))
   {
      setCursor(Qt::ArrowCursor);
   }

   QAbstractScrollArea::mouseReleaseEvent(pqEvent);
}

#if QT_CONFIG(wheelevent)
void WidgetManipImage::wheelEvent(QWheelEvent* pqEvent)
{
   // On vérifie s'il s'agit d'un zoom rapide ou non
   qreal dFactor(0);
   if(pqEvent->modifiers() & Qt::ControlModifier)
   {
      dFactor = DEFAULT_ZOOM_CTRL_FACTOR;
   }
   else
   {
      dFactor = DEFAULT_ZOOM_FACTOR;
   }

   // On détermine quelle est la nouvelle valeur du zoom
   qreal dNewScale(0.0);
   if(pqEvent->angleDelta().y() > 0)
   {
      if(m_dScale > SCALE_MAX)
      {
         return;
      }

      dNewScale = m_dScale * dFactor;
      // Je m'assure qu'on repasse par l'unité
      if(  (dNewScale > 1)
         &&(m_dScale < 1))
      {
         dNewScale = 1;
      }
   }
   else
   {
      if(m_dScale < (1.0 / SCALE_MAX))
      {
         return;
      }

      dNewScale = m_dScale / dFactor;
      // Je m'assure qu'on repasse par l'unité
      if(  (dNewScale < 1)
         &&(m_dScale > 1))
      {
         dNewScale = 1;
      }
   }

   // Je regarde où était la souris sur l'image par rapport au centre de la vue
   QPointF qCoordMouseInImage(qMapWidgetToImage(pqEvent->position()));

   // J'applique la nouvelle valeur du zoom ...
   m_dScale = dNewScale;
   // ... et je repositionne mon image pour que le pixel de l'image sous la
   // souris reste le même
   QPointF qCoordNewPoint(qMapImageToWidget(qCoordMouseInImage));
   m_qTopLeftCorner -= (   QPoint(qCoordNewPoint.rx(),
                                  qCoordNewPoint.ry())
                         - QPoint(pqEvent->position().rx(),
                                  pqEvent->position().ry()));

   // Je vérifie que l'image est toujours correctement placée dans le widget
   CheckCoordTopLeftImage();

   // Je contrôle la position des scrools bars
   CheckScroolBar();

   // Et je redessine le widget
   viewport()->update();

   // The event is processed
   pqEvent->accept();
}
#endif

void WidgetManipImage::resizeEvent(QResizeEvent *pqEvent)
{
   CheckCoordTopLeftImage();

   CheckScroolBar();

   QAbstractScrollArea::resizeEvent(pqEvent);
}

void WidgetManipImage::paintEvent(QPaintEvent* pqEvent)
{
   Q_UNUSED(pqEvent)

   // On définit le painter sur le widget que l'on veut peindre et je désactive
   // l'antialiasing car je veux voir les "pixels" de mon image quand je zoome à
   // l'intérieur.
   QPainter qPainter(viewport());
   qPainter.setRenderHint(QPainter::Antialiasing, false);

   // On dessine l'arrière plan
   qPainter.fillRect(qPainter.window(), m_qBckgrndBrush);

   // On dessine l'image
   qPainter.drawImage(QRectF(m_qTopLeftCorner, m_qImage.size() * m_dScale),
                      m_qImage,
                      QRectF(QPointF(),
                             m_qImage.size()));

   // On dessine le cadre
   qPainter.setPen(m_qPenCadre);
   qPainter.setBrush(Qt::NoBrush);
   qPainter.drawRect(QRectF(m_qTopLeftCorner - QPointF(1, 1),
                            m_qImage.size() * m_dScale + QSize(2, 2)));
}

bool WidgetManipImage::eventFilter(QObject* pqObj, QEvent* pqEvent)
{
   if(  (pqObj == verticalScrollBar())
      ||(pqObj == horizontalScrollBar())
      ||(pqObj == cornerWidget()))
   {
      if(pqEvent->type() == QEvent::Enter)
      {
         unsetCursor();
      }

      // Si les scrollbars ont du être redessinées, c'est que leur valeur a
      // changé
      if(pqEvent->type() == QEvent::Paint)
      {
         if(horizontalScrollBar()->isVisible())
         {
            m_qTopLeftCorner.rx() = -1 * horizontalScrollBar()->value();
            viewport()->update();
         }
         if(verticalScrollBar()->isVisible())
         {
            m_qTopLeftCorner.ry() = -1 * verticalScrollBar()->value();
            viewport()->update();
         }
      }

      return false;
   }
   else
   {
      // pass the event to the parent class
      return QAbstractScrollArea::eventFilter(pqObj, pqEvent);
   }
}

void WidgetManipImage::setContextMenu(void)
{
   setContextMenuPolicy(Qt::CustomContextMenu);
   connect(this, &QWidget::customContextMenuRequested,
           this, &WidgetManipImage::showContextMenu);
}

void WidgetManipImage::showContextMenu(const QPoint& qPos)
{
   // Create the menu and add action
   QMenu contextMenu;
   contextMenu.addAction("Reset zoom", this, &WidgetManipImage::ResetZoom);

   // Display the menu
   contextMenu.exec(this->mapToGlobal(qPos));
}

void WidgetManipImage::ResetZoom(void)
{
   m_dScale = 1;
   CheckCoordTopLeftImage();
   viewport()->update();
}

// La fonction suivante permet de retrouver l'état de la souris.
CSubStateMouse::e_state_machine WidgetManipImage::eGetStateMouse(void)
{
   return pMainWindow()->pWidgetManipColor()->eCurrentState();
}

MainWindow* WidgetManipImage::pMainWindow(void) const
{
   return dynamic_cast<MainWindow*>(parentWidget()->parentWidget()
                                                  ->parentWidget()
                                                  ->parentWidget());
}

MdiArea* WidgetManipImage::pMdiArea(void) const
{
   return dynamic_cast<MdiArea*>(parentWidget()->parentWidget()
                                               ->parentWidget());
}

SubWindow* WidgetManipImage::pSubWindow(void) const
{
   return dynamic_cast<SubWindow*>(parentWidget());
}

void WidgetManipImage::CheckCoordTopLeftImage(void)
{
   // On lit la taille du viewport
   QSize qSizeViewport(viewport()->size());

   // On s'assure que l'image reste bien dans le viewport en largeur
   if(static_cast<qreal>(qSizeViewport.width())
                           >= (static_cast<qreal>(m_qImage.width()) * m_dScale))
   {
      m_qTopLeftCorner.rx() = (qSizeViewport.width()
                                             - m_qImage.width() * m_dScale) / 2;
   }
   else
   {
      int iMin_x(-1 * qCeil(   static_cast<qreal>(m_qImage.width()) * m_dScale
                             - static_cast<qreal>(qSizeViewport.width())));

      if(m_qTopLeftCorner.rx() > 0)
      {
         m_qTopLeftCorner.rx() = 0;
      }
      else if(m_qTopLeftCorner.rx() < iMin_x)
      {
         m_qTopLeftCorner.rx() = iMin_x;
      }
   }

   // On s'assure que l'image reste bien dans le viewport en hauteur
   if(static_cast<qreal>(qSizeViewport.height())
                        >= (static_cast<qreal>(m_qImage.height()) * m_dScale))
   {
      m_qTopLeftCorner.ry() = (qSizeViewport.height()
                                          - m_qImage.height() * m_dScale) / 2;
   }
   else
   {
      int iMin_y(-1 * qCeil(   static_cast<qreal>(m_qImage.height()) * m_dScale
                             - static_cast<qreal>(qSizeViewport.height())));

      if(m_qTopLeftCorner.ry() > 0)
      {
         m_qTopLeftCorner.ry() = 0;
      }
      else if(m_qTopLeftCorner.ry() < iMin_y)
      {
         m_qTopLeftCorner.ry() = iMin_y;
      }
   }
}

void WidgetManipImage::CheckScroolBar(void)
{
   // On lit la taille du viewport
   QSize qSizeViewport(viewport()->size());

   // On lit la taille de l'image
   QSize qSizeImage(qCeil(qreal(m_qImage.size().width())  * m_dScale),
                    qCeil(qreal(m_qImage.size().height()) * m_dScale));

   // On gére d'abord le scroolbar horizontal
   if(qSizeViewport.width() >= qSizeImage.width())
   {
      // Alors le scrollbar est inutile
      horizontalScrollBar()->hide();
      horizontalScrollBar()->setRange(0, 0);
   }
   else
   {
      // Alors le scrollbar est utile
      horizontalScrollBar()->show();

      horizontalScrollBar()->setPageStep(qSizeViewport.width());
      horizontalScrollBar()->setRange(0,
                                        qSizeImage.width()
                                      - qSizeViewport.width());
      horizontalScrollBar()->setValue(-1 * m_qTopLeftCorner.rx());
   }

   // Puis on gére le scrollbar vertical
   if(qSizeViewport.height() >= qSizeImage.height())
   {
      // Alors le scrollbar est inutile
      verticalScrollBar()->hide();
      verticalScrollBar()->setRange(0, 0);
   }
   else
   {
      // Alors le scrollbar est utile
      verticalScrollBar()->show();

      verticalScrollBar()->setPageStep(qSizeViewport.height());
      verticalScrollBar()->setRange(0,
                                        qSizeImage.height()
                                      - qSizeViewport.height());
      verticalScrollBar()->setValue(-1 * m_qTopLeftCorner.ry());
   }
}

QPointF WidgetManipImage::qMapWidgetToImage(const QPointF qPointInWidgetF) const
{
   return ((qPointInWidgetF - m_qTopLeftCorner) / m_dScale);
}

QPointF WidgetManipImage::qMapImageToWidget(const QPointF qPointInImageF) const
{
   return (qPointInImageF * m_dScale + m_qTopLeftCorner);
}

bool WidgetManipImage::IsPointWidgetInImage(const QPoint& qPointInWidget) const
{
   // On récupére les coordonnées de la souris dans l'image
   QPointF qMousePointInImageF = qMapWidgetToImage(qPointInWidget);

   QRectF qRectImageF(QPoint(0, 0),
                      m_qImage.size());

   return qRectImageF.contains(qMousePointInImageF);
}
