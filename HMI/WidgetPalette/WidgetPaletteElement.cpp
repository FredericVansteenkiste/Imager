#include "WidgetPaletteElement.h"

WidgetPaletteElement::WidgetPaletteElement(const QColor qColor,
                                           QWidget* pParent):QCheckBox("",
                                                                       pParent)
{
   setCheckable(false);
   setChecked(false);
}

WidgetPaletteElement::~WidgetPaletteElement()
{
}
