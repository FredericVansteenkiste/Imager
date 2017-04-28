#include <qtsingleapplication.h>

#include "HMI/MainWindow.h"

int main(int argc, char *argv[])
{
   QtSingleApplication qApplication(argc, argv);

   // On s'assure que nous sommes la seule application Imager en cours, dans le
   // cas contraire on envoie la liste des arguments à l'application principale
   // et on ferme l'application courante.
   QStringList qlstrArguments(qApplication.arguments());
   QString qstrArguments(qlstrArguments.join("\n"));
   if(qApplication.sendMessage(qstrArguments) == true)
   {
      return 0;
   }

   qApplication.setWindowIcon(QIcon(":HMI/Icones/application.ico"));
   MainWindow qMainWindow;
   qMainWindow.show();

   qApplication.setActivationWindow(&qMainWindow);

/*   QObject::connect(&qApplication, SIGNAL(messageReceived(const QString&)),
                    &qMainWindow, SLOT(OpenFiles(const QString&)));*/
   QObject::connect(&qApplication, &QtSingleApplication::messageReceived,
                    &qMainWindow, &MainWindow::OpenFiles);

   return qApplication.exec();
}
