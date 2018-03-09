#ifndef WIDGETPALETTE_H
#define WIDGETPALETTE_H

#include <QtWidgets>

#include "WidgetPaletteElement.h"

class WidgetPalette : public QScrollArea
{
   Q_OBJECT

public:
   WidgetPalette(const unsigned int& uiNbrColor, QWidget* pParent = nullptr);
   virtual ~WidgetPalette();
};

#endif // WIDGETPALETTE_H
