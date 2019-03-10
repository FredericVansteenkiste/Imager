#include "WidgetEditComponentColor.h"

WidgetEditComponentColor::WidgetEditComponentColor(const QString& qLabel,
                                                   const unsigned char& ucValue,
                                                   QValidator* pqValidator,
                                                   QWidget* pqParent):
                                                         QWidget(pqParent),
                                                         m_pqEdit(nullptr)
{
   QLabel* pqLabel = new QLabel(qLabel, this);
   pqLabel->setMaximumWidth(20);

   m_pqEdit = new QLineEdit(QString("%1").arg(ucValue), this);
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
