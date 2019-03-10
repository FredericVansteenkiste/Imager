#include "WidgetPaletteElement.h"

WidgetPaletteElement::WidgetPaletteElement(const QColor& qColor,
                                           QWidget* pParent):QWidget(pParent),
                                                             m_qColor(qColor)
{
   setAttribute(Qt::WA_StaticContents);
   setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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

void WidgetPaletteElement::mousePressEvent(QMouseEvent* pqEvent)
{
   Q_UNUSED(pqEvent)
}

void WidgetPaletteElement::paintEvent(QPaintEvent* pqEvent)
{
   Q_UNUSED(pqEvent)

   QPainter qPainter(this);
   QRect qSquare(QPoint(0, 0),
                 QSize(WIDGET_PALETTE_ELEM_SIZE_PIXEL - 1,
                       WIDGET_PALETTE_ELEM_SIZE_PIXEL - 1));
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
