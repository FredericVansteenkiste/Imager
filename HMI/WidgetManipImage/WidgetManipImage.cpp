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
   // J'appel setBackgroundBrush() au lieu d'initialiser directement dans le
   // constructeur pour qu'il y ait une mise à jour de m_qPenCadre en fonction
   // de m_qBckgrndBrush.
   setBackgroundBrush(qBckgrndBrush);

   // Initialize contextual menu
   setContextMenu();
}

WidgetManipImage::~WidgetManipImage()
{
}

void WidgetManipImage::SetImage(const QImage& qImage)
{
   m_qImage = qImage;

   update();
//   // Update the pixmap in the scene
//   QPixmap qPixmap = QPixmap(qImage.size());
//   qPixmap.fill(QColor(0x0, 0x0, 0x0, 0x0));
//   QPainter qPainter(&qPixmap);
//   qPainter.drawPixmap(QPoint(), QPixmap::fromImage(qImage));

//   m_pqGraphicsScene->setPixmap(qPixmap);
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
   contextMenu.exec(qPos);
}

void WidgetManipImage::ResetZoom(void)
{
   m_dScale = 1;
}
