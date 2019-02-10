#ifndef WIDGETEDITCOMPONENTCOLOR_H
#define WIDGETEDITCOMPONENTCOLOR_H

#include <QtWidgets>

class WidgetEditComponentColor : public QWidget
{
   Q_OBJECT
public:
   WidgetEditComponentColor(const QString& qLabel,
                            const unsigned char& ucValue,
                            QValidator* pqValidator,
                            QWidget* pqParent = nullptr);
   virtual ~WidgetEditComponentColor();

signals:

public slots:

private:
   QLineEdit* m_pqEdit; // Line editor to set the value of color component
};

#endif // WIDGETEDITCOMPONENTCOLOR_H
