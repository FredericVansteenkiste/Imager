#include "HMI/MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication qApplication(argc, argv);
   qApplication.setWindowIcon(QIcon(":HMI/Icones/application.ico"));
   MainWindow qMainWindow;
   qMainWindow.show();

   return qApplication.exec();
}
