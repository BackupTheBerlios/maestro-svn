#include<qpoint.h>
#include<qfiledialog.h>
#include<qstring.h>

#include"fenetre.h"


Fenetre::Fenetre(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  OpenBut = new QPushButton(this, "OpenBut");
  QuitBut = new QPushButton(this, "QuitBut");
  PreviewCadre = new ImageBox(this, "PreviewCadre");
  fab = new Fabien(this, "fab");
  rom = new Romain(this, "rom");
  sam = new Sami(this, "sam");
  m = new Mat(this, "m");

  resize(450, 420);
  setCaption("Maestro");

  OpenBut->setText("Open");
  QuitBut->setText("Quit");
  PreviewCadre->setTitle("Preview");

  fab->show();
  sam->show();
  rom->show();
  m->show();

  OpenBut->move(10, 30);
  QuitBut->move(10, 80);
  PreviewCadre->move(140, 10);
  
  PreviewCadre->resize(290, 400);

  connect(OpenBut, SIGNAL(clicked()), this, SLOT(OuvrirImage()));
  connect(QuitBut, SIGNAL(clicked()), this, SLOT(close()));
}

Fenetre::~Fenetre()
{

}

void Fenetre::OuvrirImage()
{
  bool succesI, succesA;
  QString FilePath;
  QImage temp;

  FilePath = QFileDialog::getOpenFileName("~/",
					  "Images (*.png *.jpg *.bmp)",
					  this,
					  "openfiledialog",
					  "Choose an image to load");
  succesI = Partition.load(FilePath);
  OpenBut->setText("OK 1");

  temp = Partition.smoothScale(290, 400);

  succesA = PreviewCadre->Apercu.convertFromImage(temp);
  OpenBut->setText("OK 2");

  PreviewCadre->setPaletteBackgroundPixmap(PreviewCadre->Apercu);
}
