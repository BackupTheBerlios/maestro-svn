#include<qfiledialog.h>
#include<stdio.h>

#include"fenetre.h"

#include"lignes.h"
#include"filtre.h"



/* Constructeur de la classe Fenetre */
Fenetre::Fenetre(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  /* on definit l'aspect de la fenetre*/
  resize(550, 80);  //taille
  setCaption("Maestro - A Optical Musicscore Recognition");  //nom

  /* on definit nos boutons et autres composantes de la fenetre*/
  OpenBut = new QPushButton(this, "OpenBut");  //allocation
  FiltBut = new QPushButton(this, "FiltBut");
  RecoBut = new QPushButton(this, "RecoBut");
  MusicBut = new QPushButton(this, "MusicBut");
  AboutBut = new QPushButton(this, "AboutBut");
  QuitBut = new QPushButton(this, "QuitBut");
  PreviewCadre = new QGroupBox(this, "PreviewCadre");
  Apercu = new QLabel(this, "Apercu");
  APropos = new QFrame(this ,0, WType_Popup);

  QLabel *dev = new QLabel(APropos, "dev");

  NBelt_listd = 0;
  list_lignes = NULL;

  OpenBut->setText("Open");  //nom affiche
  FiltBut->setText("Filtrer");
  RecoBut->setText("Detection");
  MusicBut->setText("Jouer Midi");
  AboutBut->setText("A Propos");
  QuitBut->setText("Quit");
  dev->setText("Maestro 0.7\n \nEn cours de developpement\n \nAH-TEC Mathieu\nFRELING Fabien\nSMATI Sami\nVENTURI Romain");

  OpenBut->move(10, 20);  //emplacement
  FiltBut->move(80, 20);
  RecoBut->move(150, 20);
  MusicBut->move(240, 20);
  AboutBut->move(380, 20);
  QuitBut->move(470, 20);
  PreviewCadre->move(10, 90);
  Apercu->move(20, 100);
  APropos->move(this->x() + 150, this->y() + 100);
  dev->move(10, 10);

  //APropos->setFrameStyle(WinPanel | Raised);

  OpenBut->resize(70, 40);  //taille
  FiltBut->resize(70, 40);
  RecoBut->resize(90, 40);
  MusicBut->resize(90, 40);
  AboutBut->resize(90, 40);
  QuitBut->resize(70, 40);
  PreviewCadre->resize(340, 400);
  Apercu->resize(320, 380);
  APropos->resize(250, 250);
  dev->resize(280, 280);

  FiltBut->setEnabled(false);
  RecoBut->setEnabled(false);
  MusicBut->setEnabled(false);

  /* on relie nos boutons a nos fonctions */
  connect(OpenBut, SIGNAL(clicked()), this, SLOT(OpenClick()));
  connect(QuitBut, SIGNAL(clicked()), this, SLOT(close()));
  //connect(DetecBut, SIGNAL(clicked()), this, SLOT(DetectLignes()));
  connect(FiltBut, SIGNAL(clicked()), this, SLOT(Filtrage()));
  //connect(SaveBut, SIGNAL(clicked()), this, SLOT(Sauvegarde()));
  connect(RecoBut, SIGNAL(clicked()), this, SLOT(DetectLignes()));
  //connect(MidiBut, SIGNAL(clicked()), this, SLOT(CreationMidi()));
  //connect(MusicBut, SIGNAL(clicked()), this, SLOT(JouerMidi()));
  connect(AboutBut, SIGNAL(clicked()), APropos, SLOT(show()));
}

/* Destructeur - fait automatiquement */
Fenetre::~Fenetre()
{

}

/* On agrandit la fenetre */
void Fenetre::Agrandissement()
{
  resize(550, 500);
}

/* On ouvre une image qu'on stocke dans la variable Picture 
de la classe Fenetre, le chemin est sauvegarde dans 
FilePath */
void Fenetre::OuvrirImage()
{
  bool succes;

  FilePath = QFileDialog::getOpenFileName("~/",
					  "Images (*.png *.jpg *.bmp *.gif)",
					  this,
					  "openfiledialog",
					  "Choose an image to load");
  succes = Picture.load(FilePath);
  Image2Apercu(&Picture);
}

/* On clique sur 'Open' */
void Fenetre::OpenClick()
{
  OuvrirImage();
  Agrandissement();
  FiltBut->setEnabled(true);
  RecoBut->setEnabled(true);
}

/* On convertit une image en pixmap et on l'affiche 
sur le label Apercu de la classe Fenetre */
void Fenetre::Image2Apercu(QImage *picture)
{
  QImage Mini;
  QPixmap temp;

  Mini = picture->smoothScale(Apercu->width(), Apercu->height(), picture->ScaleMin);
  temp.convertFromImage(Mini, 0);
  Apercu->setPixmap(temp); 
}

/* On detecte les lignes qu'on stocke dans une p_liste2 
de la classe Fenetre, puis on affiche en rouge les lignes 
pour verifier en meme temps qu'on les affiche dans le term */
void Fenetre::DetectLignes()
{
  int i, j, w;
  QRgb rouge, bleu;
  QImage temp;

  Supprimer_liste2(&list_lignes);
  //DetecBut->setText("Detection");
  list_lignes = TrouverLignes(&Picture);
  //if (list_lignes == NULL)
  //	DetecBut->setText("Echec");
  rouge = qRgb(255, 0, 0);
  bleu = qRgb(0, 0, 255);
  w = Picture.width();
  temp = Picture;
  list_portees = GroupLignes(list_lignes, w - 1, Picture.height() - 1);

  while (list_lignes) // on verifie
    {
      for (i=0; i<w; i++)
	{
	  for (j=0; j<list_lignes->larg; j++)
	    temp.setPixel(i, list_lignes->ord + j, rouge);
	}      
      printf("%i est ligne de %i\n", list_lignes->ord, list_lignes->larg);
      list_lignes = list_lignes->next;
    }

  while (list_portees) // on verifie
    {
      for (i=0; i<w; i++)
	{
	  temp.setPixel(i, list_portees->pos.top(), bleu);
	  temp.setPixel(i, list_portees->pos.bottom(), bleu);
	}      
      list_portees = list_portees->next;
    }

  Image2Apercu(&temp);
}

/* On filtre l'image sans la redimensionner */
void Fenetre::Filtrage()
{
  float angle;

  PictModif = filtrer_grayscale(Picture);
  PictModif = filtrer_seuillage(PictModif);
  angle = rotation_calcul_angle(PictModif);

  if (angle != 0.0)   
    PictModif = filtrer_rotation(PictModif, angle);

  PictModif = filtrer_median(PictModif, NBelt_listd);
  Image2Apercu(&PictModif);
}

/* On sauvegarde l'image modifiee apres filtrage */
void Fenetre::Sauvegarde()
{
  Picture = PictModif;
}

void Fenetre::Reconnaissance()
{

}

void Fenetre::CreationMidi()
{

}

void Fenetre::JouerMidi()
{

}
