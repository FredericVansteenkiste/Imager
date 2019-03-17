#include "WidgetEditColor.h"

WidgetEditColor::WidgetEditColor(QWidget* pqParent):QWidget(pqParent),
                                                    m_pqEditRed(nullptr),
                                                    m_pqEditGreen(nullptr),
                                                    m_pqEditBlue(nullptr),
                                                    m_pqEditAlpha(nullptr)
{
   m_pqEditRed = new WidgetEditComponentColor(tr("r="),
                                              255,
                                              this);
   m_pqEditGreen = new WidgetEditComponentColor(tr("g="),
                                                255,
                                                this);
   QHBoxLayout* pqHBoxLayout1 = new QHBoxLayout;
   pqHBoxLayout1->setMargin(0);
   pqHBoxLayout1->addStretch(1);
   pqHBoxLayout1->addWidget(m_pqEditRed);
   pqHBoxLayout1->addWidget(m_pqEditGreen);
   pqHBoxLayout1->addStretch(1);

   m_pqEditBlue = new WidgetEditComponentColor(tr("b="),
                                               255,
                                               this);
   m_pqEditAlpha = new WidgetEditComponentColor(tr("a="),
                                                255,
                                                this);
   QHBoxLayout* pqHBoxLayout2 = new QHBoxLayout;
   pqHBoxLayout2->setMargin(0);
   pqHBoxLayout2->addStretch(1);
   pqHBoxLayout2->addWidget(m_pqEditBlue);
   pqHBoxLayout2->addWidget(m_pqEditAlpha);
   pqHBoxLayout2->addStretch(1);

   QVBoxLayout* pqVBoxLayout = new QVBoxLayout;
   pqVBoxLayout->setMargin(0);
   pqVBoxLayout->addLayout(pqHBoxLayout1);
   pqVBoxLayout->addLayout(pqHBoxLayout2);

   setLayout(pqVBoxLayout);
}

WidgetEditColor::~WidgetEditColor()
{
}

void WidgetEditColor::SetColor(const QColor& qColor)
{
   m_pqEditRed->SetValue(qColor.red());
   m_pqEditGreen->SetValue(qColor.green());
   m_pqEditBlue->SetValue(qColor.blue());
   m_pqEditAlpha->SetValue(qColor.alpha());
}
