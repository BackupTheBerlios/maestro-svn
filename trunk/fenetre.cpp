#include<qpoint.h>
#include<qfiledialog.h>
#include<qstring.h>

#include"fenetre.h"


Fenetre::Fenetre(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  /* on definit l'aspect de la fenetre*/
  resize(450, 420);  //taille
  setCaption("Maestro");  //nom

  /* on definit nos boutons et autres composantes de la fenetre*/
  OpenBut = new QPushButton(this, "OpenBut");  //allocation
  QuitBut = new QPushButton(this, "QuitBut");
  PreviewCadre = new ImageBox(this, "PreviewCadre");
  FabBut = new QPushButton(this, "FabBut");
  MatBut = new QPushButton(this, "MatBut");
  SamBut = new QPushButton(this, "SamBut");
  RomBut = new QPushButton(this, "RomBut");
  fab = new Fabien(this, "fab");
  rom = new Romain(this, "rom");
  sam = new Sami(this, "sam");
  m = new Mat(this, "m");

  OpenBut->setText("Open");  //nom affiche
  QuitBut->setText("Quit");
  PreviewCadre->setTitle("Preview");
  FabBut->setText("Fabien");
  MatBut->setText("Mathieu");
  SamBut->setText("Sami");
  RomBut->setText("Romain");

  OpenBut->move(10, 30);  //emplacement
  QuitBut->move(10, 80);
  PreviewCadre->move(140, 10);
  FabBut->move(10, 320);
  MatBut->move(10, 170);
  SamBut->move(10, 220);
  RomBut->move(10, 270);
  
  PreviewCadre->resize(290, 400); //taille

  /* on relie nos boutons a nos fonctions */
  connect(OpenBut, SIGNAL(clicked()), this, SLOT(OuvrirImage()));
  connect(QuitBut, SIGNAL(clicked()), this, SLOT(close()));
  connect(FabBut, SIGNAL(clicked()), fab, SLOT(show()));
  connect(SamBut, SIGNAL(clicked()), sam, SLOT(show()));
  connect(MatBut, SIGNAL(clicked()), m, SLOT(show()));
  connect(RomBut, SIGNAL(clicked()), rom, SLOT(show()));
}

Fenetre::~Fenetre()
{

}

void Fenetre::OuvrirImage()
{
  int w,h;

  bool succesI, succesA;
  // QString FilePath; //dans fenetre.h
  QImage temp;

  FilePath = QFileDialog::getOpenFileName("~/",
					  "Images (*.png *.jpg *.bmp)",
					  this,
					  "openfiledialog",
					  "Choose an image to load");
  succesI = Partition.load(FilePath);
  w = Partition.width();
  h = Partition.height();
  if(w > 290)
    {
      h = (int) 290*h/w ;
      w = 290;
    }
  if(h > 400)
    {
      w = (int) 400*w/h;
      h = 400;
    }

  //  OpenBut->setText("OK 1");

  temp = Partition.smoothScale(w, h);//290x400

  succesA = PreviewCadre->Apercu.convertFromImage(temp);
  //  OpenBut->setText("OK 2");

  PreviewCadre->setPaletteBackgroundPixmap(PreviewCadre->Apercu);
}
