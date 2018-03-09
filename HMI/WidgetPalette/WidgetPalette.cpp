#include "WidgetPalette.h"

WidgetPalette::WidgetPalette(const unsigned int& uiNbrColor,
                             QWidget* pParent):QScrollArea(pParent)
{
   setAttribute(Qt::WA_DeleteOnClose);

   QGridLayout* pqPaletteLayout = new QGridLayout(this);
   for(unsigned int i = 0; i < uiNbrColor; i++)
   {
      WidgetPaletteElement* pqColorElement = new WidgetPaletteElement(
                                                               Qt::black,
                                                               this);
      pqPaletteLayout->addWidget(pqColorElement, i, 0);
   }
   setLayout(pqPaletteLayout);
}

WidgetPalette::~WidgetPalette()
{
}
