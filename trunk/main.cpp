#include<qapplication.h>

#include"fenetre.h"
#include"global.h"


int main(int argc, char **argv)
{
  QApplication maestro(argc, argv);

  Fenetre MainWin;
  maestro.setMainWidget(&MainWin);
  MainWin.connect(&maestro, SIGNAL(lastWindowClosed()), &maestro, SLOT(quit()));

  MainWin.show();
  return maestro.exec();
}
