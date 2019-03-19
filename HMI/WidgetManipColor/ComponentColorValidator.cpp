#include "ComponentColorValidator.h"

ComponentColorValidator::ComponentColorValidator(QObject* pParent):
                                                         QIntValidator(pParent)
{
}

ComponentColorValidator::ComponentColorValidator(const int& iMinimum,
                                                 const int& iMaximum,
                                                 QObject* pParent):
                                                         QIntValidator(iMinimum,
                                                                       iMaximum,
                                                                       pParent)
{
}

ComponentColorValidator::~ComponentColorValidator()
{
}

QValidator::State ComponentColorValidator::validate(QString &qstrInput,
                                                    int &iPos) const
{
   QValidator::State qState = QIntValidator::validate(qstrInput, iPos);

   if(qstrInput.toInt() > top())
   {
      qState = QValidator::Invalid;
   }

   return qState;
}
