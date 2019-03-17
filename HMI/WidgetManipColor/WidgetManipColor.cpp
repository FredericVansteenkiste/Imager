#include "WidgetManipColor.h"

WidgetManipColor::WidgetManipColor(QWidget* pParent):
                                                   QWidget(pParent),
                                                   m_StateMachine(),
                                                   m_pqCurrentColor(nullptr),
                                                   m_pqPen(nullptr),
                                                   m_pqPipette(nullptr),
                                                   m_pEditColor(nullptr),
                                                   m_pqPaletteLayout(nullptr),
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

   // Je crée le layout qui contiendra les palettes des images
   m_pqPaletteLayout = new QHBoxLayout;

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

   QVBoxLayout* pqVBoxLayout = new QVBoxLayout;
   pqVBoxLayout->setMargin(4);
   pqVBoxLayout->addLayout(pqHBoxLayout1);
   pqVBoxLayout->addLayout(pqHBoxLayout2);
   pqVBoxLayout->addWidget(m_pEditColor);
   pqVBoxLayout->addLayout(m_pqPaletteLayout);
   pqVBoxLayout->addStretch();
   pqVBoxLayout->addWidget(m_pqSizePalette);
   pqVBoxLayout->addWidget(m_pqColorNumber);
   pqVBoxLayout->addWidget(m_pqDepth);
   pqVBoxLayout->addWidget(m_pqBitUsedPerPixel);
   pqVBoxLayout->addWidget(m_pqSizeImage);
   setLayout(pqVBoxLayout);

   // J'indique qu'elle est la couleur courante
   SetCurrentColor(Qt::black, Qt::black);
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

QHBoxLayout* WidgetManipColor::pqPaletteLayout(void)
{
   return m_pqPaletteLayout;
}

void WidgetManipColor::SubWindowActivated(QMdiSubWindow* pqMdiSubWindow)
{
   SubWindow* pqActivatedSubWindow = dynamic_cast<SubWindow*>(pqMdiSubWindow);
   MainWindow* pqMainWindow = dynamic_cast<MainWindow*>(parent()->parent());
   QList<QMdiSubWindow*> qlpqMdiSubWindow
                        = dynamic_cast<MdiArea*>(pqMainWindow->centralWidget())
                                                             ->subWindowList();

   hide();
   foreach(QMdiSubWindow* pMdiSubWindow, qlpqMdiSubWindow)
   {
      SubWindow* pqSubWindow = dynamic_cast<SubWindow*>(pMdiSubWindow);

      if(pqSubWindow == nullptr)
      {
         continue;
      }
      else if(pqSubWindow->pqWidgetPalette() == nullptr)
      {
         continue;
      }
      else if(pqSubWindow != pqActivatedSubWindow)
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
            pqSubWindow->pqWidgetPalette()->RearrangePalette(size().width());
            pqSubWindow->pqWidgetPalette()->show();
         }
      }
   }
   show();

   if(  (pqActivatedSubWindow != nullptr)
      &&(pqActivatedSubWindow->qImage().colorTable().isEmpty() == false))
   {
      QColor qBckgrndColor = pqActivatedSubWindow->backgroundBrush().color();
      if(pqActivatedSubWindow->backgroundBrush().style() == Qt::TexturePattern)
      {
         qBckgrndColor = Qt::white;
      }
      QVector<QRgb> aqColorPalette = pqActivatedSubWindow->qImage()
                                                          .colorTable();
      int iIndColor = pqActivatedSubWindow->pqWidgetPalette()
                                          ->iIndElementSelectionne();
      QColor qCurrentColor = QColor(qRed(aqColorPalette[iIndColor]),
                                    qGreen(aqColorPalette[iIndColor]),
                                    qBlue(aqColorPalette[iIndColor]),
                                    qAlpha(aqColorPalette[iIndColor]));
      pqMainWindow->pWidgetManipColor()->SetCurrentColor(qCurrentColor,
                                                         qBckgrndColor);
   }
}

void WidgetManipColor::SetCurrentColor(const QColor& qColor,
                                       const QColor& qBckGrndColor)
{
   QPixmap qCurrentColor(m_pqCurrentColor->size());
   qCurrentColor.fill(qBckGrndColor);
   QPainter qPainter(&qCurrentColor);
   QRect qRect(QPoint(0, 0), m_pqCurrentColor->size());
   qPainter.fillRect(qRect, qColor);
   m_pqCurrentColor->setPixmap(qCurrentColor);

   m_pEditColor->SetColor(qColor);
}
