#include "WidgetManipImage.h"

WidgetManipImage::WidgetManipImage(const QImage& qImage,
                                   const QBrush& qBckgrndBrush,
                                   QWidget* pParent):
                                                QAbstractScrollArea(pParent),
                                                m_qImage(qImage),
                                                m_qBckgrndBrush(),
                                                m_qPenCadre(),
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

   update();
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
}

QBrush WidgetManipImage::backgroundBrush() const
{
   return m_qBckgrndBrush;
}

void WidgetManipImage::paintEvent(QPaintEvent *pqEvent)
{
   Q_UNUSED(pqEvent)

   QPainter qPainter(this);
   qPainter.setRenderHint(QPainter::Antialiasing, false);
   qPainter.drawEllipse(80, 80, 400, 240);
   qDebug() << qPainter.window();
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
