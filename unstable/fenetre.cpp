#include<qfiledialog.h>

#include"fenetre.h"


Fenetre::Fenetre(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  /* on definit l'aspect de la fenetre*/
  resize(800, 600);  //taille
  setCaption("Maestro");  //nom

  /* on definit nos boutons et autres composantes de la fenetre*/
  OpenBut = new QPushButton(this, "OpenBut");  //allocation
  QuitBut = new QPushButton(this, "QuitBut");
  PreviewCadre = new ImageBox(this, "PreviewCadre");
  Apercu = new QLabel(this, "Apercu");
  DetecBut = new QPushButton(this, "DetecBut");
  RecBut = new QPushButton(this, "RecBut");
  SamBut = new QPushButton(this, "SamBut");
  RomBut = new QPushButton(this, "RomBut");
  detec = new Detection(this, "detec");
  rom = new Romain(this, "rom");
  sam = new Sami(this, "sam");
  rec = new Reco(this, "rec");

  OpenBut->setText("Open");  //nom affiche
  QuitBut->setText("Quit");
  PreviewCadre->setTitle("Preview");
  DetecBut->setText("Detection");
  RecBut->setText("Reconnaissance");
  SamBut->setText("Sami");
  RomBut->setText("Romain");

  OpenBut->move(10, 30);  //emplacement
  QuitBut->move(10, 80);
  PreviewCadre->move(170, 10);
  Apercu->move(180, 40);
  DetecBut->move(10, 320);
  RecBut->move(10, 170);
  SamBut->move(10, 220);
  RomBut->move(10, 270);
  
  PreviewCadre->resize(600, 550); //taille
  Apercu->resize(580, 510);
  RecBut->resize(140, 30);

  /* on relie nos boutons a nos fonctions */
  connect(OpenBut, SIGNAL(clicked()), this, SLOT(OuvrirImage()));
  connect(QuitBut, SIGNAL(clicked()), this, SLOT(close()));
  connect(DetecBut, SIGNAL(clicked()), detec, SLOT(show()));
  connect(SamBut, SIGNAL(clicked()), sam, SLOT(show()));
  connect(RecBut, SIGNAL(clicked()), rec, SLOT(show()));
  connect(RomBut, SIGNAL(clicked()), rom, SLOT(show()));
}

Fenetre::~Fenetre()
{

}

void Fenetre::OuvrirImage()
{
  bool succesI, succesA;
  QImage Mini;
  QPixmap temp;

  FilePath = QFileDialog::getOpenFileName("~/",
					  "Images (*.png *.jpg *.bmp)",
					  this,
					  "openfiledialog",
					  "Choose an image to load");
  succesI = pix.load(FilePath);
  Mini = pix.smoothScale(580, 510, pix.ScaleMin);
  succesA = temp.convertFromImage(Mini, 0);
  Apercu->setPixmap(temp); 
}
