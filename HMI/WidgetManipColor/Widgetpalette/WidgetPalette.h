#ifndef WIDGETPALETTE_H
#define WIDGETPALETTE_H

#include <QtWidgets>

#include "WidgetPaletteElement.h"
#include "../WidgetManipColor.h"

class WidgetManipColor;

class WidgetPalette : public QScrollArea
{
   Q_OBJECT

public:
   WidgetPalette(const unsigned int& uiNbrColor,
                 QWidget* pParent = nullptr);
   virtual ~WidgetPalette();

protected:
   virtual void resizeEvent(QResizeEvent* pqEvent);

private:
   QList<WidgetPaletteElement*> m_qlstPaletteElement;
   QGridLayout*                 m_pqPaletteLayout;
};

#endif // WIDGETPALETTE_H
