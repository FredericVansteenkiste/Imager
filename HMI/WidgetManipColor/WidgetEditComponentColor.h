#ifndef WIDGETEDITCOMPONENTCOLOR_H
#define WIDGETEDITCOMPONENTCOLOR_H

#include <QtWidgets>

#include "ComponentColorValidator.h"

class WidgetEditComponentColor : public QWidget
{
   Q_OBJECT
public:
   explicit WidgetEditComponentColor(const QString& qLabel,
                                     const int& iValue,
                                     QWidget* pqParent = nullptr);
   virtual ~WidgetEditComponentColor();

   void SetValue(const int& iValue);

signals:

public slots:

private:
   QLineEdit* m_pqEdit; // Line editor to set the value of color component
};

#endif // WIDGETEDITCOMPONENTCOLOR_H
