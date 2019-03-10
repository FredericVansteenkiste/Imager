#include "WidgetPalette.h"

WidgetPalette::WidgetPalette(const QVector<QRgb>& aqColorPalette,
                             QWidget* pParent):
                              QWidget(pParent),
                              m_apPaletteElement(),
                              m_pLayoutPalette(new QGridLayout(this)),
                              m_iNbrColumn(0),
                              m_iNbrLine(0),
                              m_pqSubWindow(dynamic_cast<SubWindow*>(pParent))
{
   setAttribute(Qt::WA_DeleteOnClose);

   m_pLayoutPalette->setHorizontalSpacing(0);
   m_pLayoutPalette->setVerticalSpacing(0);
   m_pLayoutPalette->setContentsMargins(0, 0, 0, 0);
   setLayout(m_pLayoutPalette);

   SetPalette(aqColorPalette);

   RearrangePalette();
}

WidgetPalette::~WidgetPalette()
{
}

void WidgetPalette::SetPalette(const QVector<QRgb>& aqColorPalette)
{
   // On efface l'ancienne palette
   for(int i = 0; i < m_apPaletteElement.size(); i++)
   {
      m_pLayoutPalette->removeWidget(m_apPaletteElement[i]);
      delete m_apPaletteElement[i];
      m_apPaletteElement[i] = nullptr;
   }
   m_apPaletteElement.clear();

   for(int i = 0; i < aqColorPalette.size(); i++)
   {
      m_apPaletteElement.append(
                     new WidgetPaletteElement(QColor(qRed(aqColorPalette[i]),
                                                     qGreen(aqColorPalette[i]),
                                                     qBlue(aqColorPalette[i]),
                                                     qAlpha(aqColorPalette[i])),
                                              this));
   }

   int iTemp(aqColorPalette.size() * WIDGET_PALETTE_ELEM_SIZE_PIXEL + 1);
   setMaximumSize(iTemp, iTemp);
}

SubWindow* WidgetPalette::pqSubWindow(void) const
{
   return m_pqSubWindow;
}

void WidgetPalette::resizeEvent(QResizeEvent* event)
{
   RearrangePalette();

   QWidget::resizeEvent(event);
}

void WidgetPalette::paintEvent(QPaintEvent* pqEvent)
{
   QWidget::paintEvent(pqEvent);
}

void WidgetPalette::RearrangePalette(void)
{
   m_iNbrColumn = (width() - 1) / WIDGET_PALETTE_ELEM_SIZE_PIXEL;
   int iNbrColor = m_apPaletteElement.size();
   if(m_iNbrColumn > iNbrColor)
   {
      m_iNbrColumn = iNbrColor;
      m_iNbrLine   = 1;
   }
   else
   {
      if(m_iNbrColumn == 0)
      {
         return;
      }
      m_iNbrLine = iNbrColor / m_iNbrColumn;
      if(iNbrColor % m_iNbrColumn != 0)
      {
         m_iNbrLine++;
      }
   }

   int iIndColumn(0);
   int iIndLine(0);
   for(int i = 0; i < m_apPaletteElement.size(); i++)
   {
      m_pLayoutPalette->addWidget(m_apPaletteElement[i], iIndLine, iIndColumn);
      iIndColumn++;
      if(iIndColumn >= m_iNbrColumn)
      {
         iIndColumn = 0;
         iIndLine++;
      }
   }
}
