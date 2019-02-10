#ifndef WIDGETEDITCOLOR_H
#define WIDGETEDITCOLOR_H

#include <QtWidgets>

#include "WidgetEditComponentColor.h"

class WidgetEditColor : public QWidget
{
   Q_OBJECT
public:
   WidgetEditColor(QWidget* pqParent = nullptr);
   virtual ~WidgetEditColor();

private:
   WidgetEditComponentColor* m_pqEditRed;
   WidgetEditComponentColor* m_pqEditGreen;
   WidgetEditComponentColor* m_pqEditBlue;
   WidgetEditComponentColor* m_pqEditAlpha;
};

#endif // WIDGETEDITCOLOR_H
