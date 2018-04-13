#include "WidgetPaletteElement.h"

WidgetPaletteElement::WidgetPaletteElement(const QColor qColor,
                                           QWidget* pParent):QCheckBox("",
                                                                       pParent)
{
   setFixedSize(SIZE_PALETTE_ELEMENT, SIZE_PALETTE_ELEMENT);
   setCheckable(false);
   setChecked(false);
}

WidgetPaletteElement::~WidgetPaletteElement()
{
}
