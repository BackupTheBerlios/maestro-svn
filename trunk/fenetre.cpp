#include<qpoint.h>
#include<qfiledialog.h>
#include<qstring.h>

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
  DetecBut = new QPushButton(this, "DetecBut");
  RecBut = new QPushButton(this, "RecBut");
  SamBut = new QPushButton(this, "SamBut");
  RomBut = new QPushButton(this, "RomBut");
  detec = new Detect(this, "dect");
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
  DetecBut->move(10, 320);
  RecBut->move(10, 170);
  SamBut->move(10, 220);
  RomBut->move(10, 270);
  
  PreviewCadre->resize(600, 550); //taille
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
  int wi, hi, wc, hc;
  QImage temp;

  FilePath = QFileDialog::getOpenFileName("~/",
					  "Images (*.png *.jpg *.bmp)",
					  this,
					  "openfiledialog",
					  "Choose an image to load");

  succesI = pix.load(FilePath);
  wi = pix.width();
  hi = pix.height();
  wc = PreviewCadre->width();
  hc = PreviewCadre->height();
  if (wi > wc)
    {
      wi = wc;
      hi = wc*hi/wi;
    }
  if (hi > hc)
    {
      hi = hc;
      wi = wc*hc/hi;
    }
  temp = pix.smoothScale(wi, hi);
  succesA = PreviewCadre->Apercu.convertFromImage(temp);
  PreviewCadre->setPaletteBackgroundPixmap(PreviewCadre->Apercu);
  
}
