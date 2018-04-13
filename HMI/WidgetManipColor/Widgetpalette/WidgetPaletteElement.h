#ifndef WIDGETPALETTEELEMENT_H
#define WIDGETPALETTEELEMENT_H

#include <QtWidgets>

#define SIZE_PALETTE_ELEMENT (13)

class WidgetPaletteElement : public QCheckBox
{
   Q_OBJECT

public:
   WidgetPaletteElement(const QColor qColor, QWidget* pParent = nullptr);
   virtual ~WidgetPaletteElement();
};

#endif // WIDGETPALETTEELEMENT_H
