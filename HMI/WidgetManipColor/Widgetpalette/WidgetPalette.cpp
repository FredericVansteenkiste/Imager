#include "WidgetPalette.h"

WidgetPalette::WidgetPalette(const unsigned int& uiNbrColor,
                             QWidget* pParent):QScrollArea(pParent),
                                               m_qlstPaletteElement(),
                                               m_pqPaletteLayout(nullptr)
{
   setAttribute(Qt::WA_DeleteOnClose);

   m_pqPaletteLayout = new QGridLayout(this);
   m_pqPaletteLayout->setSpacing(0);
   for(unsigned int i = 0; i < uiNbrColor; i++)
   {
      WidgetPaletteElement* pqColorElement = new WidgetPaletteElement(
                                                                     Qt::black,
                                                                     this);
      pqColorElement->resize(13, 13);
      m_qlstPaletteElement.append(pqColorElement);
   }
   setLayout(m_pqPaletteLayout);
}

WidgetPalette::~WidgetPalette()
{
}

void WidgetPalette::resizeEvent(QResizeEvent* pqEvent)
{
   // Je retire tous les éléments de la palette
   for(int i = 0; i < m_qlstPaletteElement.size(); i++)
   {
      m_pqPaletteLayout->removeWidget(m_qlstPaletteElement[i]);
   }

   // Je prends la mesure des nouvelles dimensions de l'objet WidgetPalette
   int iWidthPalette(frameSize().width());
   int iWidthPaletteElement(m_qlstPaletteElement[0]->width());
//   int iHeightPaletteElement(m_qlstPaletteElement[0]->height());

   // Et je replace correctement les éléments de la palette en fonction des
   // nouvelles dimensions de WidgetPalette
   int x(0);
   int y(0);
   for(int i = 0; i < m_qlstPaletteElement.size(); i++)
   {
      qDebug() << x << "\t" << y;
      m_pqPaletteLayout->addWidget(m_qlstPaletteElement[i], y, x);
      x++;
      if(((x + 1) * iWidthPaletteElement) > iWidthPalette)
      {
        x = 0;
        y++;
      }
   }
   qDebug() << iWidthPalette;
   qDebug() << iWidthPaletteElement;
   qDebug() << "";
   setMaximumWidth(m_qlstPaletteElement.size() * iWidthPaletteElement);
//   setMaximumHeight(30 + (y + 1) * iHeightPaletteElement);

   pqEvent->accept();
}
