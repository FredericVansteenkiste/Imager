#include "WidgetEditColor.h"

WidgetEditColor::WidgetEditColor(QWidget* pqParent):QWidget(pqParent),
                                                    m_pqEditRed(nullptr),
                                                    m_pqEditGreen(nullptr),
                                                    m_pqEditBlue(nullptr),
                                                    m_pqEditAlpha(nullptr)
{
   QValidator* pqValidator = new QIntValidator(0, 255, this);

   m_pqEditRed = new WidgetEditComponentColor(tr("r="),
                                              255,
                                              pqValidator,
                                              this);
   m_pqEditGreen = new WidgetEditComponentColor(tr("g="),
                                                255,
                                                pqValidator,
                                                this);
   QHBoxLayout* pqHBoxLayout1 = new QHBoxLayout;
   pqHBoxLayout1->addWidget(m_pqEditRed);
   pqHBoxLayout1->addWidget(m_pqEditGreen);

   m_pqEditBlue = new WidgetEditComponentColor(tr("b="),
                                               255,
                                               pqValidator,
                                               this);
   m_pqEditAlpha = new WidgetEditComponentColor(tr("a="),
                                                255,
                                                pqValidator,
                                                this);
   QHBoxLayout* pqHBoxLayout2 = new QHBoxLayout;
   pqHBoxLayout2->addWidget(m_pqEditBlue);
   pqHBoxLayout2->addWidget(m_pqEditAlpha);

   QVBoxLayout* pqVBoxLayout = new QVBoxLayout;
   pqVBoxLayout->addLayout(pqHBoxLayout1);
   pqVBoxLayout->addLayout(pqHBoxLayout2);

   setLayout(pqVBoxLayout);
}

WidgetEditColor::~WidgetEditColor()
{
}
