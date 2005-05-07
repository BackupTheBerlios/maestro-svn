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
  setFixedSize(550, 80);  //taille
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
  ABut = new QPushButton(this, "ABut");
  AGroup = new QGroupBox(this, "AGroup");
  ABox = new QCheckBox(AGroup, "ABox");
  BBox = new QCheckBox(AGroup, "BBox");
  ALabel = new QLabel(this, "ALabel");
  
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
  PreviewCadre->setTitle("Apercu");

  OpenBut->move(10, 20);  //emplacement
  FiltBut->move(80, 20);
  RecoBut->move(150, 20);
  MusicBut->move(240, 20);
  AboutBut->move(380, 20);
  QuitBut->move(470, 20);
  PreviewCadre->move(10, 80);
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
  PreviewCadre->resize(340, 410);
  Apercu->resize(320, 380);
  APropos->resize(250, 250);
  dev->resize(280, 280);

  FiltBut->setEnabled(false);
  RecoBut->setEnabled(false);
  MusicBut->setEnabled(false);

  ABut->hide();
  ABox->hide();
  BBox->hide();
  AGroup->hide();
  ALabel->hide();

  /* on relie nos boutons a nos fonctions */
  connect(OpenBut, SIGNAL(clicked()), this, SLOT(OpenClick()));
  connect(QuitBut, SIGNAL(clicked()), this, SLOT(close()));
  //connect(DetecBut, SIGNAL(clicked()), this, SLOT(DetectLignes()));
  connect(FiltBut, SIGNAL(clicked()), this, SLOT(FiltClick()));
  //connect(SaveBut, SIGNAL(clicked()), this, SLOT(Sauvegarde()));
  connect(RecoBut, SIGNAL(clicked()), this, SLOT(RecoClick()));
  //connect(MidiBut, SIGNAL(clicked()), this, SLOT(CreationMidi()));
  //connect(MusicBut, SIGNAL(clicked()), this, SLOT(JouerMidi()));
  connect(AboutBut, SIGNAL(clicked()), APropos, SLOT(show()));
}

/* Destructeur - fait automatiquement */
Fenetre::~Fenetre()
{

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
  ABox->hide();
  BBox->hide();
  AGroup->hide();
  disconnect(ABut, 0, 0, 0);

  OuvrirImage();
  setFixedSize(550, 500);
  FiltBut->setEnabled(true);
  RecoBut->setEnabled(true);
  ABut->show();
  ABut->resize(90, 40);
  ABut->setText("Changer");
  ABut->move(440, 350);
  connect(ABut, SIGNAL(clicked()), this, SLOT(OuvrirImage()));
  ALabel->show();
  ALabel->move(360, 80);
  ALabel->resize(180, 220);
  ALabel->setText("Vous pouvez desormais \nchoisir de filtrer l'image \nou bien de lancer \ndirectement la \nreconnaissance.\n\nVous pouvez changer \nd'image si vous vous etes \ntrompe.");
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
  p_liste2 toto;
  p_coord tata;

  rouge = qRgb(255, 0, 0);
  bleu = qRgb(0, 0, 255);
  w = Picture.width();
  temp = Picture;
  
  Supprimer_liste2(&list_lignes);
  list_lignes = TrouverLignes(&Picture);
  Supprimer_coord(&list_portees);
  list_portees = GroupLignes(list_lignes, w - 1, Picture.height() - 1);

  if (ABox->isChecked())
    {
      toto = list_lignes;
      while (toto) // on verifie
	{
	  for (i=0; i<w; i++)
	    {
	      for (j=0; j<toto->larg; j++)
		temp.setPixel(i, toto->ord + j, rouge);
	    }      
	  toto = toto->next;
	}
    }

  if (BBox->isChecked())
    {
      tata = list_portees;
      while (tata) // on verifie
	{
	  for (i=0; i<w; i++)
	    {
	      temp.setPixel(i, tata->pos.top(), bleu);
	      temp.setPixel(i, tata->pos.bottom(), bleu);
	    }      
	  tata = tata->next;
	}
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
  Picture = PictModif;
  Image2Apercu(&PictModif);
}

/* On sauvegarde l'image modifiee apres filtrage */
void Fenetre::Sauvegarde()
{
  Picture = PictModif;
}

void Fenetre::RecoClick()
{
  ALabel->hide();
  disconnect(ABut, 0, 0, 0);
  
  AGroup->show();
  AGroup->setTitle("Options");
  AGroup->move(360, 80);
  AGroup->resize(180, 150);
  ABox->show();
  ABox->setChecked(false);
  ABox->setText("Voir lignes");
  ABox->move(10, 40);
  ABox->resize(120, 20);
  BBox->show();
  BBox->setChecked(false);
  BBox->setText("Voir portees");
  BBox->move(10, 60);
  BBox->resize(120, 20);
  ABut->show();
  ABut->setText("Go !");
  connect(ABut, SIGNAL(clicked()), this, SLOT(DetectLignes()));
}

void Fenetre::FiltClick()
{
  ABox->hide();
  BBox->hide();
  AGroup->hide();
  disconnect(ABut, 0, 0, 0);

  ALabel->show();
  ALabel->setText("Cliquez sur 'Go !' \npour traiter l'image.");
  ABut->show();
  ABut->setText("Go !");
  connect(ABut, SIGNAL(clicked()), this, SLOT(Filtrage()));
}
