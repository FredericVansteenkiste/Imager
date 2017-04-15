#include "WidgetManipColor.h"

WidgetManipColor::WidgetManipColor(QWidget* pParent):
                                                   QWidget(pParent),
                                                   m_pqSizePalette(nullptr),
                                                   m_pqColorNumber(nullptr),
                                                   m_pqDepth(nullptr),
                                                   m_pqBitUsedPerPixel(nullptr),
                                                   m_pqSizeImage(nullptr)
{
   m_pqSizePalette     = new QLabel(this);
   m_pqColorNumber     = new QLabel(this);
   m_pqDepth           = new QLabel(this);
   m_pqBitUsedPerPixel = new QLabel(this);
   m_pqSizeImage       = new QLabel(this);

   QVBoxLayout* pqVBoxLayout = new QVBoxLayout;
   pqVBoxLayout->addStretch();
   pqVBoxLayout->addWidget(m_pqSizePalette);
   pqVBoxLayout->addWidget(m_pqColorNumber);
   pqVBoxLayout->addWidget(m_pqDepth);
   pqVBoxLayout->addWidget(m_pqBitUsedPerPixel);
   pqVBoxLayout->addWidget(m_pqSizeImage);
   setLayout(pqVBoxLayout);
}

WidgetManipColor::~WidgetManipColor()
{
}

void WidgetManipColor::SetSizePalette(const unsigned int& uiSizePalette)
{
   if(uiSizePalette == 0)
   {
      m_pqSizePalette->hide();
   }
   else
   {
      QString qString(tr("Size palette : %1"));
      qString = qString.arg(uiSizePalette);
      m_pqSizePalette->setText(qString);
      m_pqSizePalette->show();
   }
}

void WidgetManipColor::SetColorNumber(const unsigned int& uiNbreColor)
{
   QString qString(tr("Color number : %1"));
   qString = qString.arg(uiNbreColor);
   m_pqColorNumber->setText(qString);
}

void WidgetManipColor::SetDepth(const unsigned int& uiDepth)
{
   QString qString(tr("Bits per pixel : %1"));
   qString = qString.arg(uiDepth);
   m_pqDepth->setText(qString);
}

void WidgetManipColor::SetBitsUsedPerPixel(
                                       const unsigned int& uiBitsUsedPerPixel)
{
   QString qString(tr("Bits used per pixel : %1"));
   qString = qString.arg(uiBitsUsedPerPixel);
   m_pqBitUsedPerPixel->setText(qString);
}

void WidgetManipColor::SetSizeImage(const QSize& qSize)
{
   QString qString(tr("Size image : %1x%2"));
   qString = qString.arg(qSize.width()).arg(qSize.height());
   m_pqSizeImage->setText(qString);
}
