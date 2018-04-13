#include "WidgetPalette.h"

WidgetPalette::WidgetPalette(const unsigned int& uiNbrColor,
                             QWidget* pParent):
                                       QScrollArea(pParent),
                                       m_qlstPaletteElement(),
                                       m_pqPaletteLayout(nullptr)
{
   setAttribute(Qt::WA_DeleteOnClose);

   m_pqPaletteLayout = new QGridLayout();
   m_pqPaletteLayout->setSpacing(0);
   m_pqPaletteLayout->setContentsMargins(0, 0, 0, 0);
   m_pqPaletteLayout->setSizeConstraint(QLayout::SetNoConstraint);
   for(unsigned int i = 0; i < uiNbrColor; i++)
   {
      WidgetPaletteElement* pqColorElement = new WidgetPaletteElement(Qt::black,
                                                                      this);
      m_qlstPaletteElement.append(pqColorElement);
   }
   setLayout(m_pqPaletteLayout);
}

WidgetPalette::~WidgetPalette()
{
}
int i2 = 0;
void WidgetPalette::resizeEvent(QResizeEvent* pqEvent)
{
   qDebug() << "WidgetPalette : " << (i2++);
   qDebug() << "WidgetPalette : " << this << "\n";
   // Je retire tous les éléments de la palette
   for(int i = 0; i < m_qlstPaletteElement.size(); i++)
   {
      m_pqPaletteLayout->removeWidget(m_qlstPaletteElement[i]);
   }

   // Je prends la mesure des nouvelles dimensions de l'objet WidgetPalette
   setFixedSize(pqEvent->size());
   int iWidthPalette(pqEvent->size().width());
   int iHeightPalette(pqEvent->size().height());
   int iWidthPaletteElement(m_qlstPaletteElement[0]->width());
   int iHeightPaletteElement(m_qlstPaletteElement[0]->height());

   // Et je replace correctement les éléments de la palette en fonction des
   // nouvelles dimensions de WidgetPalette
   int x(0);
   int y(0);
   int iMemWidth(iWidthPaletteElement);
   int iMemHeight(iHeightPaletteElement);
   for(int i = 0; i < m_qlstPaletteElement.size(); i++)
   {
      m_pqPaletteLayout->addWidget(m_qlstPaletteElement[i], y, x);
      x++;
      if(((x + 1) * iWidthPaletteElement) > iWidthPalette)
      {
         iMemWidth = x * iWidthPaletteElement;
         x = 0;
         y++;
         iMemHeight = y * iHeightPaletteElement;
      }
   }

   pqEvent->accept();
}
