#include "WidgetEditComponentColor.h"

WidgetEditComponentColor::WidgetEditComponentColor(const QString& qLabel,
                                                   const unsigned char& ucValue,
                                                   QValidator* pqValidator,
                                                   QWidget* pqParent):
                                                         QWidget(pqParent),
                                                         m_pqEdit(nullptr)
{
   QLabel* pqLabel = new QLabel(qLabel, this);
   pqLabel->setMaximumWidth(15);
   pqLabel->setMinimumWidth(15);

   m_pqEdit = new QLineEdit(QString("%1").arg(ucValue), this);
   m_pqEdit->setValidator(pqValidator);
   m_pqEdit->setAlignment(Qt::AlignHCenter);
   m_pqEdit->setMaximumWidth(30);
   m_pqEdit->setMinimumWidth(30);

   QHBoxLayout* pqHBoxLayout = new QHBoxLayout;
   pqHBoxLayout->setContentsMargins(0, 0, 0, 0);
   pqHBoxLayout->addWidget(pqLabel);
   pqHBoxLayout->addWidget(m_pqEdit);
   pqHBoxLayout->setSizeConstraint(QLayout::SetFixedSize);

   setLayout(pqHBoxLayout);
}

WidgetEditComponentColor::~WidgetEditComponentColor()
{
}
