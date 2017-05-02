#include "MdiArea.h"

MdiArea::MdiArea(QWidget* pParent):QMdiArea(pParent)
{
   setMouseTracking(true);
   setAcceptDrops(true);
}

MdiArea::~MdiArea()
{
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
   // l'utilisateur pour le gisser-déposer.
   QStringList qlstrListFiles;
   foreach(QUrl qUrl, pqEvent->mimeData()->urls())
   {
      qlstrListFiles.append(qUrl.toLocalFile());
   }

   emit NewFileReceived(qlstrListFiles);
}
