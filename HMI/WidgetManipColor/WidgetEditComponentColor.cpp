#include "WidgetEditComponentColor.h"

WidgetEditComponentColor::WidgetEditComponentColor(const QString& qLabel,
                                                   const int& iValue,
                                                   QWidget* pqParent):
                                                         QWidget(pqParent),
                                                         m_pqEdit(nullptr)
{
   QIntValidator* pqValidator = new QIntValidator(0, 255, this);

   QLabel* pqLabel = new QLabel(qLabel, this);
   pqLabel->setMaximumWidth(20);

   m_pqEdit = new QLineEdit(QString("%1").arg(iValue), this);
   m_pqEdit->setValidator(pqValidator);
   m_pqEdit->setAlignment(Qt::AlignHCenter);
   m_pqEdit->setMaximumWidth(40);

   QHBoxLayout* pqHBoxLayout = new QHBoxLayout;
   pqHBoxLayout->setMargin(0);
   pqHBoxLayout->addWidget(pqLabel);
   pqHBoxLayout->addWidget(m_pqEdit);

   setLayout(pqHBoxLayout);
}

WidgetEditComponentColor::~WidgetEditComponentColor()
{
}

void WidgetEditComponentColor::SetValue(const int& iValue)
{
   m_pqEdit->setText(QString("%1").arg(iValue));
}

