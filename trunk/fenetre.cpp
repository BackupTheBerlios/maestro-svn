#include<qfiledialog.h>
#include<stdio.h>

#include"fenetre.h"

#include"lignes.h"
#include"filtre.h"
#include"morpho.h"
#include"reconnaissance.h"


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
  APropos = new QMessageBox(this ,"APropos");
  ABut = new QPushButton(this, "ABut");  
  BBut = new QPushButton(this, "BBut");
  CBut = new QPushButton(this, "CBut");
  DBut = new QPushButton(this, "DBut");
  EBut = new QPushButton(this, "EBut");
  FBut = new QPushButton(this, "FBut");
  AGroup = new QGroupBox(this, "AGroup");
  ABox = new QCheckBox(AGroup, "ABox");
  BBox = new QCheckBox(AGroup, "BBox");
  ALabel = new QLabel(this, "ALabel");

  NBelt_listd = 0;
  list_lignes = NULL;
  list_portees = NULL;

  OpenBut->setText("Open");  //nom affiche
  FiltBut->setText("Filtrer");
  RecoBut->setText("Detection");
  MusicBut->setText("Jouer Midi");
  AboutBut->setText("A Propos");
  QuitBut->setText("Quit");
  PreviewCadre->setTitle("Apercu");

  OpenBut->move(10, 20);  //emplacement
  FiltBut->move(80, 20);
  RecoBut->move(150, 20);
  MusicBut->move(240, 20);
  AboutBut->move(380, 20);
  QuitBut->move(470, 20);
  PreviewCadre->move(10, 80);
  Apercu->move(20, 100);

  OpenBut->resize(70, 40);  //taille
  FiltBut->resize(70, 40);
  RecoBut->resize(90, 40);
  MusicBut->resize(90, 40);
  AboutBut->resize(90, 40);
  QuitBut->resize(70, 40);
  PreviewCadre->resize(340, 410);
  Apercu->resize(320, 380);
  APropos->resize(250, 250);

  FiltBut->setEnabled(false);
  RecoBut->setEnabled(false);
  //MusicBut->setEnabled(false);

  ABut->hide();
  BBut->hide();
  CBut->hide();
  DBut->hide();
  EBut->hide();
  FBut->hide();
  ABox->hide();
  BBox->hide();
  AGroup->hide();
  ALabel->hide();

  /* on relie nos boutons a nos fonctions */
  connect(OpenBut, SIGNAL(clicked()), this, SLOT(OpenClick()));
  connect(FiltBut, SIGNAL(clicked()), this, SLOT(FiltClick()));
  connect(RecoBut, SIGNAL(clicked()), this, SLOT(RecoClick()));
  connect(MusicBut, SIGNAL(clicked()), this, SLOT(MusicClick()));
  connect(AboutBut, SIGNAL(clicked()), this, SLOT(AboutClick()));
  connect(QuitBut, SIGNAL(clicked()), this, SLOT(close()));
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
					  "Images (*.png *.jpg *.bmp *.gif sauvegarde)",
					  this,
					  "openfiledialog",
					  "Choose an image to load");
  succes = Picture.load(FilePath);
  Image2Apercu(&Picture);
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
  temp = Picture.copy();
  
  Supprimer_liste2(&list_lignes);
  list_lignes = TrouverLignes(&Picture);
  Supprimer_coord(&list_portees);
  list_portees = GroupLignes(list_lignes, w - 1, Picture.height() - 1);

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

  Image2Apercu(&temp);
}


void Fenetre::VirerLignes()
{
  QRgb blanc =  qRgb(255,255,255);
  QRgb noir =  qRgb(0,0,0);
  int i,j,k,x;

  PictModif = Picture;
  largeur_ligne = Max_Largeur(list_lignes);
  espacement_ligne = CalculEspacement(list_lignes);
  printf("esp = %i \t largeur = %i\n", espacement_ligne, largeur_ligne);
  printf("Virer lignes active\n");
  while (list_lignes != NULL )
    {
      i = list_lignes->ord;
      j = list_lignes->larg;
      printf("ordonee = %i, largeur = %i , espacement_ligne = %i\n",i,j, espacement_ligne);;
      for( x=-1* largeur_ligne ; x < j + largeur_ligne; x++ )
	{
	  // printf("Virer ligne de %i\n",x+i);
	  for(k=0;PictModif.valid(k,x+i);k++)
	    {
	      if ( (PictModif.pixel(k,i+j +int(largeur_ligne/2+ largeur_ligne/3)) != noir)
		   && (PictModif.pixel(k,i-j) != noir) )
		PictModif.setPixel(k,x+i,blanc);
	    }
	}  
      list_lignes = list_lignes->next;
    }
 Image2Apercu(&PictModif);
 printf("Fin de virer lignes\n");;
 
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

  BBut->show(); // on propose de sauvegarder
  BBut->resize(90, 40);
  BBut->move(440, 400);
  BBut->setText("Sauver");
  connect(BBut, SIGNAL(clicked()), this, SLOT(Sauvegarde()));
}

void Fenetre::Filtrage_simple(QImage * im) // filtrage pour les tests : pas de rotation.
{
  *im = filtrer_median(*im, NBelt_listd);
 // Image2Apercu(im);
}

/* On sauvegarde l'image modifiee apres filtrage */
void Fenetre::Sauvegarde()
{
  Picture = PictModif;
  PictModif.save("sauvegarde", "PNG" );
}

void Fenetre::Reconnaissance()
{
  QImage img;
  QPixmap pix;
  p_lcord l;
  int i;
    
  img = ALabel->pixmap()->convertToImage();
  Filtrage_simple(&img); // On repasse une couche de filtrage c mieu.
  // Reconnaissance des notes noire Pour le moment.
  //  p_liste2 ll = TrouverLignes(&Picture);
  //  l = liste_noire(&Picture,CalculEspacement(ll));
  printf("esp = %i \n", espacement_ligne);
  l = liste_noire(&img,espacement_ligne); 
  
  if (l==NULL)
  {
    for (i=1; i<=largeur_ligne;i++)
    Dilater(&img);
  
  for (i=1; i<=largeur_ligne;i++)
    Eroder(&img);
      l = liste_noire(&img,espacement_ligne); 
  }
  pix.convertFromImage(img);
  ALabel->setPixmap(pix);
}

void Fenetre::Reconnaissance_cle()
{
  QImage img;
  
  img = ALabel->pixmap()->convertToImage();
  afficher_caracteristique_cle(caracteristiques_cle(&img));
  afficher_cle(&img);
}

void Fenetre::ClickTrouver()
{
  QImage img;
  int i;
  p_coord p=list_portees;
  
  list_images = NULL;
  
  img = Picture.copy();
  for (i=1; i<=largeur_ligne;i++)
    Dilater(&img);
  
  for (i=1; i<=largeur_ligne;i++)
    Eroder(&img);

  if (list_portees)
  list_images =TrouverMorceaux(&(img.copy(list_portees->pos)),espacement_ligne);
   
  ALabel->show();
  ALabel->resize(180, 150);
  ALabel->move(360, 340);
  ALabel->setPixmap(NULL);
}

void Fenetre::ClickDefiler()
{
  QImage tmp;
  QImage morceau;
  QPixmap temp;

  if (list_images)
  {
    morceau = Picture.copy(list_portees->pos).copy(list_images->r);
    tmp = morceau;
    /*tmp = morceau.smoothScale(ALabel->width(), ALabel->height(), morceau.ScaleMin);*/
    temp.convertFromImage(tmp, 0);
    ALabel->setPixmap(temp);
    list_images = list_images->p;
  }
  else
  if (list_portees)
  {
    list_portees = list_portees->next;
    ClickTrouver();
  }
}



/***** FONCTIONS CLICK *****/


/* On clique sur 'Open' */
void Fenetre::OpenClick()
{
  BBut->hide();
  CBut->hide();
  DBut->hide();
  EBut->hide();
  FBut->hide();
  ABox->hide();
  BBox->hide();
  AGroup->hide();
  disconnect(ABut, 0, 0, 0);
  disconnect(BBut, 0, 0, 0);
  disconnect(CBut, 0, 0, 0);
  disconnect(DBut, 0, 0, 0);
  disconnect(EBut, 0, 0, 0);
  disconnect(FBut, 0, 0, 0);

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

/* On clique sur 'Filtrer' */
void Fenetre::FiltClick()
{
  ALabel->hide();
  BBut->hide();
  CBut->hide();
  DBut->hide();
  EBut->hide();
  FBut->hide();
  disconnect(ABut, 0, 0, 0);
  disconnect(BBut, 0, 0, 0);
  disconnect(CBut, 0, 0, 0);
  disconnect(DBut, 0, 0, 0);
  disconnect(EBut, 0, 0, 0);
  disconnect(FBut, 0, 0, 0);

  AGroup->show();
  AGroup->setTitle("Type");
  AGroup->move(360, 80);
  AGroup->resize(180, 120);

  ABox->show();
  ABox->setChecked(false);
  ABox->setText("Nette");
  ABox->move(10, 40);
  ABox->resize(120, 20);

  BBox->show();
  BBox->setChecked(true);
  BBox->setText("Scannée");
  BBox->move(10, 60);
  BBox->resize(120, 20);

  ABut->show();
  ABut->resize(90, 40);
  ABut->move(440, 350);
  ABut->setText("Go !");
  connect(ABut, SIGNAL(clicked()), this, SLOT(Filtrage()));
}

/* On clique sur 'Detecter' */
void Fenetre::RecoClick()
{
  ALabel->hide();
  AGroup->hide();
  ABox->hide();
  BBox->hide();
  disconnect(ABut, 0, 0, 0);
  disconnect(BBut, 0, 0, 0);
  disconnect(CBut, 0, 0, 0);
  disconnect(DBut, 0, 0, 0);
  disconnect(EBut, 0, 0, 0);
  disconnect(FBut, 0, 0, 0);

  ABut->show();
  ABut->setText("Lignes");
  ABut->resize(80, 40);
  ABut->move(360, 120);
  connect(ABut, SIGNAL(clicked()), this, SLOT(DetectLignes()));

  BBut->show();
  BBut->resize(80, 40);
  BBut->move(360, 230);
  BBut->setText("Note");
  connect(BBut, SIGNAL(clicked()), this, SLOT(Reconnaissance()));

  CBut->show();
  CBut->resize(80, 40);
  CBut->move(450, 230);
  CBut->setText("Cle");
  connect(CBut, SIGNAL(clicked()), this, SLOT(Reconnaissance_cle()));

  DBut->show();
  DBut->resize(80, 40);
  DBut->move(360, 180);
  DBut->setText("Trouver");
  connect(DBut, SIGNAL(clicked()), this, SLOT(ClickTrouver()));

  EBut->show();
  EBut->resize(80, 40);
  EBut->move(450, 180);
  EBut->setText(">>");
  connect(EBut, SIGNAL(clicked()), this, SLOT(ClickDefiler()));

  FBut->show();
  FBut->resize(80, 40);
  FBut->move(450, 120);
  FBut->setText("Virer");
  connect(FBut, SIGNAL(clicked()), this, SLOT(VirerLignes()));
}

/* On clique sur 'Jouer Midi' */
void Fenetre::MusicClick()
{
  QSound::play("green_day.mid");
}

/* On clique sur 'A Propos' */
void Fenetre::AboutClick()
{
  APropos->about(this, "E=mb²", 
		 "<p><b>Maestro 0.7b</b>"
		 "<br>Version en cours de développement"
		 "<p>Programmeurs :"
		 "<br>Mathieu AH-TEC, "
		 "Fabien FRELING\n"
		 "<br>Sami SMATI, "
		 "Romain VENTURI");
}
