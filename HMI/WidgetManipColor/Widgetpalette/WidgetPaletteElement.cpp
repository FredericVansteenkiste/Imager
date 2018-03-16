#include "WidgetPaletteElement.h"

WidgetPaletteElement::WidgetPaletteElement(const QColor qColor,
                                           QWidget* pParent):QCheckBox("",
                                                                       pParent)
{
   setFixedSize(13, 13);
   setCheckable(false);
   setChecked(false);
}

WidgetPaletteElement::~WidgetPaletteElement()
{
}
