#include "MdiArea.h"

MdiArea::MdiArea(QWidget* pParent):QMdiArea(pParent)
{
   connect(this, &MdiArea::subWindowActivated,
           this, &MdiArea::UpdateMenuWindow);
}

MdiArea::~MdiArea()
{
}

void MdiArea::UpdateMenuWindow(QMdiSubWindow* pqWindow) const
{
   // On met à jour dans les actions de sélections de fenêtre, laquelle est
   // couramment sélectionné
   SubWindow* pSubWindow = dynamic_cast<SubWindow*>(pqWindow);
   if(pSubWindow == nullptr)
   {
      return;
   }
   else if(pSubWindow->pqActionSelectImage() == nullptr)
   {
      return;
   }
   else
   {
      pSubWindow->pqActionSelectImage()->setChecked(true);
   }
}
