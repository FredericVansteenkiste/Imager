#include "WidgetManipImage.h"

WidgetManipImage::WidgetManipImage(const QImage& qImage,
                                   const QBrush& qBckgrndBrush,
                                   QWidget* pParent):
                                                QAbstractScrollArea(pParent),
                                                m_qImage(qImage),
                                                m_qBckgrndBrush(),
                                                m_qPenCadre(),
                                                m_qTopLeftCorner(),
                                                m_dScale(1)
{
   // Allow mouse tracking even if no button is pressed
   setMouseTracking(true);

   // J'appel setBackgroundBrush() au lieu d'initialiser directement dans le
   // constructeur pour qu'il y ait une mise à jour de m_qPenCadre en fonction
   // de m_qBckgrndBrush.
   setBackgroundBrush(qBckgrndBrush);

   // Initialize contextual menu
   setContextMenu();

   // Sur windows, je dois activer les scrollbars en permance, sinon si j'ouvre
   // un grand nombre d'image j'ai des resizeEvent qui sont continuellement
   // émis. Causes inconnues : à explorer
   // Ce problème n'apparait pas sous Linux; YES vive linux !!!
#ifdef Q_OS_WIN
   // Enable scroll bar to avoid an unwanted resize recursion
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
#endif   // Q_OS_WIN

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

void WidgetManipImage::resizeEvent(QResizeEvent *pqEvent)
{
   CheckCoordTopLeftImage();

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
   contextMenu.exec(qPos);    // ?? vérifier la valeur de qPos pour que le menu contextuel se pose correctement ...
}

void WidgetManipImage::ResetZoom(void)
{
   m_dScale = 1;
}

// La fonction suivante permet de retrouver l'état de la souris.
CSubStateMouse::e_state_machine WidgetManipImage::eGetStateMouse(void)
{
   return pMainWindow()->pWidgetManipColor()->eCurrentState();
}

MainWindow* WidgetManipImage::pMainWindow(void) const
{
   return dynamic_cast<MainWindow*>(parentWidget()->parentWidget()
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
      int iMin_x(-1 * qRound(  static_cast<qreal>(m_qImage.width()) * m_dScale
                             - static_cast<qreal>(qSizeViewport.width())
                             + 0.5));

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
      int iMin_y(-1 * qRound(  static_cast<qreal>(m_qImage.height()) * m_dScale
                             - static_cast<qreal>(qSizeViewport.height())
                             + 0.5));

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
