#include<qpoint.h>
#include<qfiledialog.h>

#include"sami.h"


Sami::Sami(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  But_filtre_gs = new QPushButton(this, "Filtrer gray scale");  


  resize(200, 200);
  setCaption("Sami svn marche");
  
  But_filtre_gs->setText("Filter gray scale");
  But_filtre_gs->move(10, 30);
  connect(But_filtre_gs, SIGNAL(clicked()), this, SLOT(~Sami()));
}

Sami::~Sami()
{

}

