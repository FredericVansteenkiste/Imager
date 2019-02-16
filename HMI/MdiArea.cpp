#include "MdiArea.h"

MdiArea::MdiArea(QWidget* pParent):QMdiArea(pParent)
{
   setMouseTracking(true);
   setAcceptDrops(true);

   connect(this, &MdiArea::subWindowActivated,
           this, &MdiArea::UpdateMenuWindow);
}

MdiArea::~MdiArea()
{
}

void MdiArea::setCheckedBackground(void)
{
   SubWindow* pCurrentSubWindow = dynamic_cast<SubWindow*>(currentSubWindow());

   if(pCurrentSubWindow != nullptr)
   {
      pCurrentSubWindow->setCheckedBackground();
   }
}

void MdiArea::askBackgroundColor(void)
{
   SubWindow* pCurrentSubWindow = dynamic_cast<SubWindow*>(currentSubWindow());

   if(pCurrentSubWindow != nullptr)
   {
      pCurrentSubWindow->askBackgroundColor();
   }
}

void MdiArea::mouseMoveEvent(QMouseEvent* pqEvent)
{
   emit CleanStatusBar();

   QMdiArea::mouseMoveEvent(pqEvent);
}

void MdiArea::dragEnterEvent(QDragEnterEvent* pqEvent)
{
   // On vérifie que c'est bien un ou des fichiers utilisés pour le
   // glisser-déposer
   if(pqEvent->mimeData()->hasUrls() == true)
   {
      // On accepte le glisser-déposer
      pqEvent->acceptProposedAction();
   }
}

void MdiArea::dropEvent(QDropEvent* pqEvent)
{
   // On récupére toutes les adresses de fichiers sélectionnées par
   // l'utilisateur pour le glisser-déposer.
   QStringList qlstrListFiles;
   foreach(QUrl qUrl, pqEvent->mimeData()->urls())
   {
      qlstrListFiles.append(qUrl.toLocalFile());
   }

   emit NewFileReceived(qlstrListFiles);
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
