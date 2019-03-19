#ifndef COMPONENTCOLORVALIDATOR_H
#define COMPONENTCOLORVALIDATOR_H

#include <QIntValidator>

class ComponentColorValidator : public QIntValidator
{
public:
   explicit ComponentColorValidator(QObject* pParent = nullptr);
   explicit ComponentColorValidator(const int& iMinimum,
                                    const int& iMaximum,
                                    QObject* pParent = nullptr);
   virtual ~ComponentColorValidator();

   virtual QValidator::State validate(QString &qstrInput, int &iPos)
                                                                  const final;
};

#endif // COMPONENTCOLORVALIDATOR_H
