#include "WidgetPalette.h"

WidgetPalette::WidgetPalette(const QVector<QRgb>& aqColorPalette,
                             QWidget* pParent):
                              QWidget(pParent),
                              m_apPaletteElement(),
                              m_pLayoutPalette(new QGridLayout(this)),
                              m_iNbrColumn(0),
                              m_iNbrLine(0),
                              m_pqSubWindow(dynamic_cast<SubWindow*>(pParent)),
                              m_iIndElementSelectionne()
{
   setAttribute(Qt::WA_DeleteOnClose);

   m_pLayoutPalette->setHorizontalSpacing(0);
   m_pLayoutPalette->setVerticalSpacing(0);
   m_pLayoutPalette->setContentsMargins(0, 0, 0, 0);
   setLayout(m_pLayoutPalette);

   SetPalette(aqColorPalette);
   SetIndElementSelectionne(0);

   RearrangePalette(width());

   WidgetManipColor* pWidgetManipColor =
            dynamic_cast<MainWindow*>(parent()->parent())->pWidgetManipColor();
   connect(this,              &WidgetPalette::IndElementSelectionnedChanged,
           pWidgetManipColor, &WidgetManipColor::SetCurrentColor);
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
                                              i,
                                              this));
   }

   int iTemp(aqColorPalette.size() * WIDGET_PALETTE_ELEM_SIZE_PIXEL + 1);
   setMaximumSize(iTemp, iTemp);
}

SubWindow* WidgetPalette::pqSubWindow(void) const
{
   return m_pqSubWindow;
}

void WidgetPalette::resizeEvent(QResizeEvent* pqEvent)
{
   RearrangePalette(width());

   QWidget::resizeEvent(pqEvent);
}

void WidgetPalette::RearrangePalette(const int& iWidth)
{
   m_iNbrColumn = (iWidth - 1) / WIDGET_PALETTE_ELEM_SIZE_PIXEL;
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

int WidgetPalette::iIndElementSelectionne(void) const
{
   return m_iIndElementSelectionne;
}

void WidgetPalette::SetIndElementSelectionne(const int& iIndElement)
{
   m_iIndElementSelectionne = iIndElement;
   if(m_apPaletteElement.isEmpty() == false)
   {
      if(m_pqSubWindow->backgroundBrush().style() == Qt::TexturePattern)
      {
         emit IndElementSelectionnedChanged(
                                    m_apPaletteElement[iIndElement]->qColor(),
                                    Qt::white);
      }
      else
      {
         emit IndElementSelectionnedChanged(
                                    m_apPaletteElement[iIndElement]->qColor(),
                                    m_pqSubWindow->backgroundBrush().color());
      }
   }
}
