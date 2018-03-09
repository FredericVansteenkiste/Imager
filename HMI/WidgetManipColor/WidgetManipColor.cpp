#include "WidgetManipColor.h"

WidgetManipColor::WidgetManipColor(QWidget* pParent):
                                                   QWidget(pParent),
                                                   m_StateMachine(),
                                                   m_pqVBoxLayout(nullptr),
                                                   m_pqCurrentColor(nullptr),
                                                   m_pqPen(nullptr),
                                                   m_pqPipette(nullptr),
                                                   m_pEditColor(nullptr),
                                                   m_pqSizePalette(nullptr),
                                                   m_pqColorNumber(nullptr),
                                                   m_pqDepth(nullptr),
                                                   m_pqBitUsedPerPixel(nullptr),
                                                   m_pqSizeImage(nullptr)
{
   // Je dessine un label montrant quelle est la couleur courante
   m_pqCurrentColor = new QLabel();
   m_pqCurrentColor->setFixedSize(1.5 * QSize(SIZE_BUTTON, SIZE_BUTTON));
   m_pqCurrentColor->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   QPixmap qCurrentColor(1.5 * QSize(SIZE_BUTTON, SIZE_BUTTON));
   qCurrentColor.fill(Qt::black);
   m_pqCurrentColor->setPixmap(qCurrentColor);

   // Je dessine un bouton permettant de sélectionner un crayon
   m_pqPen = new QPushButton(QIcon(":/Icones/Pen.png"),
                                   "",
                                   this);
   m_pqPen->setIconSize(QSize(SIZE_BUTTON, SIZE_BUTTON));
   m_pqPen->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   m_pqPen->setCheckable(true);
   m_pqPen->setChecked(false);
   connect(m_pqPen,         &QPushButton::clicked,
           &m_StateMachine, &CStateMouse::eButtonPenClicked);
   connect(&m_StateMachine, &CStateMouse::ButtonPenChecked,
           m_pqPen,         &QPushButton::setChecked);

   // Je dessine une bouton permettant de sélectionner une pipette
   m_pqPipette = new QPushButton(QIcon(":/Icones/Pipette.png"),
                                 "",
                                 this);
   m_pqPipette->setIconSize(QSize(SIZE_BUTTON, SIZE_BUTTON));
   m_pqPipette->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   m_pqPipette->setCheckable(true);
   m_pqPipette->setChecked(false);
   connect(m_pqPipette,     &QPushButton::clicked,
           &m_StateMachine, &CStateMouse::eButtonPipetteClicked);
   connect(&m_StateMachine, &CStateMouse::ButtonPipetteChecked,
           m_pqPipette,     &QPushButton::setChecked);

   // Je dessine le widget permettant de spécifier la couleur
   m_pEditColor = new WidgetEditColor(this);

   // Je dessine les labels donnant les propriétés de l'image courante
   m_pqSizePalette     = new QLabel(this);
   m_pqColorNumber     = new QLabel(this);
   m_pqDepth           = new QLabel(this);
   m_pqBitUsedPerPixel = new QLabel(this);
   m_pqSizeImage       = new QLabel(this);

   // Je range tous ces objets dans un layout
   QHBoxLayout* pqHBoxLayout1 = new QHBoxLayout;
   pqHBoxLayout1->addWidget(m_pqCurrentColor);

   QHBoxLayout* pqHBoxLayout2 = new QHBoxLayout;
   pqHBoxLayout2->addStretch();
   pqHBoxLayout2->addWidget(m_pqPen);
   pqHBoxLayout2->addWidget(m_pqPipette);
   pqHBoxLayout2->addStretch();

   m_pqVBoxLayout = new QVBoxLayout;
   m_pqVBoxLayout->setMargin(4);
   m_pqVBoxLayout->addLayout(pqHBoxLayout1);
   m_pqVBoxLayout->addLayout(pqHBoxLayout2);
   m_pqVBoxLayout->addWidget(m_pEditColor);
   m_pqVBoxLayout->addStretch();
   m_pqVBoxLayout->addWidget(m_pqSizePalette);
   m_pqVBoxLayout->addWidget(m_pqColorNumber);
   m_pqVBoxLayout->addWidget(m_pqDepth);
   m_pqVBoxLayout->addWidget(m_pqBitUsedPerPixel);
   m_pqVBoxLayout->addWidget(m_pqSizeImage);
   setLayout(m_pqVBoxLayout);
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

CSubStateMouse::e_state_machine WidgetManipColor::eCurrentState(void) const
{
   return m_StateMachine.eCurrentState();
}

QVBoxLayout* WidgetManipColor::pVBoxLayout(void)
{
   return m_pqVBoxLayout;
}

void WidgetManipColor::subWindowActivated(QMdiSubWindow* pqMdiSubWindow)
{
   SubWindow* pqActivatedSubWindow = dynamic_cast<SubWindow*>(pqMdiSubWindow);
   MainWindow* pqMainWindow = dynamic_cast<MainWindow*>(parent()->parent());
   QList<QMdiSubWindow*> qlqMdiSubWindow
                        = dynamic_cast<MdiArea*>(pqMainWindow->centralWidget())
                                                             ->subWindowList();

   foreach(QMdiSubWindow* pMdiSubWindow, qlqMdiSubWindow)
   {
      SubWindow* pqSubWindow = dynamic_cast<SubWindow*>(pMdiSubWindow);

      if(pqSubWindow != pqActivatedSubWindow)
      {
         pqSubWindow->pqWidgetPalette()->hide();
      }
      else
      {
         if(  (pqActivatedSubWindow == nullptr)
            ||(pqActivatedSubWindow->bIsPalette() == false))
         {
            pqSubWindow->pqWidgetPalette()->hide();
         }
         else
         {
            pqSubWindow->pqWidgetPalette()->show();
         }
      }
   }
}
