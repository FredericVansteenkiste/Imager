#include "WidgetPaletteElement.h"

WidgetPaletteElement::WidgetPaletteElement(const QColor& qColor,
                                           const int& iIndPalette,
                                           QWidget* pParent):
                                                      QWidget(pParent),
                                                      m_qColor(qColor),
                                                      m_iIndPalette(iIndPalette)
{
   setAttribute(Qt::WA_StaticContents);
   // Ce widget a une taille fixe définie par WIDGET_PALETTE_ELEM_SIZE_PIXEL
   setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

   MainWindow* pqMainWindow =
                        dynamic_cast<MainWindow*>(parent()->parent()->parent());
   connect(this,         &WidgetPaletteElement::LabelColorPixel,
           pqMainWindow, &MainWindow::UpdateLabelColorPixel);
}

WidgetPaletteElement::~WidgetPaletteElement()
{
}

QColor WidgetPaletteElement::qColor(void) const
{
   return m_qColor;
}

void WidgetPaletteElement::SetColor(const QColor& qColor)
{
   if(m_qColor != qColor)
   {
      m_qColor = qColor;
      emit ColorChanged();
   }
}

QSize WidgetPaletteElement::sizeHint(void) const
{
   return QSize(WIDGET_PALETTE_ELEM_SIZE_PIXEL, WIDGET_PALETTE_ELEM_SIZE_PIXEL);
}

void WidgetPaletteElement::enterEvent(QEvent* pqEvent)
{
   QString qstrLabel("[%1] => (A = %2 R = %3 G = %4 B = %5)");
   qstrLabel = qstrLabel.arg(m_iIndPalette)
                        .arg(m_qColor.alpha())
                        .arg(m_qColor.red())
                        .arg(m_qColor.green())
                        .arg(m_qColor.blue());
   emit LabelColorPixel(qstrLabel);

   QWidget::enterEvent(pqEvent);
}

void WidgetPaletteElement::leaveEvent(QEvent* pqEvent)
{
   emit LabelColorPixel("");

   QWidget::leaveEvent(pqEvent);
}
void WidgetPaletteElement::paintEvent(QPaintEvent* pqEvent)
{
   Q_UNUSED(pqEvent)

   QPainter qPainter(this);
   QRect qSquare(QPoint(0, 0),
                 QSize(WIDGET_PALETTE_ELEM_SIZE_PIXEL - 1,
                       WIDGET_PALETTE_ELEM_SIZE_PIXEL - 1));

   SubWindow* pSubWindow = dynamic_cast<WidgetPalette*>(
                                                      parent())->pqSubWindow();
   if(pSubWindow->backgroundBrush().style() == Qt::TexturePattern)
   {
      qPainter.fillRect(qSquare, Qt::white);
   }
   else
   {
      qPainter.fillRect(qSquare, pSubWindow->backgroundBrush().color());
   }
   qPainter.fillRect(qSquare, m_qColor);
   qPainter.setPen(Qt::black);
   QLine qHorizontalBas(0,
                        WIDGET_PALETTE_ELEM_SIZE_PIXEL - 1,
                        WIDGET_PALETTE_ELEM_SIZE_PIXEL - 1,
                        WIDGET_PALETTE_ELEM_SIZE_PIXEL - 1);
   QLine qVerticalDroite(WIDGET_PALETTE_ELEM_SIZE_PIXEL - 1,
                         0,
                         WIDGET_PALETTE_ELEM_SIZE_PIXEL - 1,
                         WIDGET_PALETTE_ELEM_SIZE_PIXEL - 1);
   qPainter.drawLine(qHorizontalBas);
   qPainter.drawLine(qVerticalDroite);
}
