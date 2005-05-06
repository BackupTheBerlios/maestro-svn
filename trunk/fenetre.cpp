#include<qfiledialog.h>
#include<stdio.h>

#include"fenetre.h"

#include"lignes.h"
#include"filtre.h"
#include"morpho.h"



/* Constructeur de la classe Fenetre */
Fenetre::Fenetre(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  /* on definit l'aspect de la fenetre*/
  resize(800, 600);  //taille
  setCaption("Maestro");  //nom

  /* on definit nos boutons et autres composantes de la fenetre*/
  OpenBut = new QPushButton(this, "OpenBut");  //allocation
  QuitBut = new QPushButton(this, "QuitBut");
  PreviewCadre = new QGroupBox(this, "PreviewCadre");
  Apercu = new QLabel(this, "Apercu");
  DetecBut = new QPushButton(this, "DetecBut");
  FiltBut = new QPushButton(this, "FiltBut");
  SaveBut = new QPushButton(this, "SaveBut");
  RecoBut = new QPushButton(this, "RecoBut");
  MidiBut = new QPushButton(this, "MidiBut");
  MusicBut = new QPushButton(this, "MusicBut");
  VirerligneBut = new QPushButton (this, "VirerligneBut");

  NBelt_listd = 0;
  list_lignes = NULL;

  OpenBut->setText("Open");  //nom affiche
  QuitBut->setText("Quit");
  PreviewCadre->setTitle("Preview");
  DetecBut->setText("Detection ligne");
  VirerligneBut->setText("Virer ligne");
  FiltBut->setText("FiltrerS");
  SaveBut->setText("Sauver");
  RecoBut->setText("Reconnaissance");
  MidiBut->setText("Creer Midi");
  MusicBut->setText("Jouer Midi");

  OpenBut->move(10, 30);  //emplacement
  QuitBut->move(10, 80);
  PreviewCadre->move(170, 10);
  Apercu->move(180, 40);
  DetecBut->move(10, 250);
  VirerligneBut->move(10,300);
  FiltBut->move(10, 150);
  RecoBut->move(10, 350);
  SaveBut->move(30, 190);
  MidiBut->move(10, 390);
  MusicBut->move(30, 430);

  PreviewCadre->resize(600, 550); //taille
  Apercu->resize(580, 510);
  RecoBut->resize(130, 30);

  /* on relie nos boutons a nos fonctions */
  connect(OpenBut, SIGNAL(clicked()), this, SLOT(OuvrirImage()));
  connect(QuitBut, SIGNAL(clicked()), this, SLOT(close()));
  connect(DetecBut, SIGNAL(clicked()), this, SLOT(DetectLignes()));
  connect(VirerligneBut, SIGNAL(clicked()), this, SLOT(VirerLignes()));
  connect(FiltBut, SIGNAL(clicked()), this, SLOT(Filtrage()));
  connect(SaveBut, SIGNAL(clicked()), this, SLOT(Sauvegarde()));
  connect(RecoBut, SIGNAL(clicked()), this, SLOT(Reconnaissance()));
  connect(MidiBut, SIGNAL(clicked()), this, SLOT(CreationMidi()));
  connect(MusicBut, SIGNAL(clicked()), this, SLOT(JouerMidi()));
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
  PictModif = Picture;
  Image2Apercu(&Picture);
}

/* On convertit une image en pixmap et on l'affiche 
sur le label Apercu de la classe Fenetre */
void Fenetre::Image2Apercu(QImage *picture)
{
  QImage Mini;
  QPixmap temp;

  Mini = picture->smoothScale(580, 510, picture->ScaleMin);
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
  DetecBut->setText("Detection");
  list_lignes = TrouverLignes(&Picture);
  if (list_lignes == NULL)
	DetecBut->setText("Echec");
  rouge = qRgb(255, 0, 0);
  bleu = qRgb(0, 0, 255);
  w = Picture.width();
  temp = Picture;
  list_portees = GroupLignes(list_lignes, w - 1, Picture.height() - 1);
  largeur_ligne = 0;

  while (list_lignes) // on verifie
    {
      for (i=0; i<w; i++)
	{
	  for (j=0; j<list_lignes->larg; j++)
	    temp.setPixel(i, list_lignes->ord + j, rouge);
	}      
      printf("%i est ligne de %i\n", list_lignes->ord, list_lignes->larg);

      if(list_lignes->larg > largeur_ligne) // on assigne espacement_ligne (variable globle dans fenetre.h)
	largeur_ligne = list_lignes->larg;

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


void Fenetre::VirerLignes()
{
  p_liste2 l = TrouverLignes(&PictModif);
  QRgb blanc =  qRgb(255,255,255);
  QRgb noir =  qRgb(0,0,0);
  int i,j,k,x;
  PictModif = Picture;
  largeur_ligne = CalculLargeur(l);
  printf("Virer lignes active\n");
  while (l != NULL )
    {
      i = l->ord;
      j = l->larg;
      printf("ordonee = %i, largeur = %i , espacement_ligne = %i",i,j, largeur_ligne);;
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
      l = l->next;
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
}

void Fenetre::Filtrage_simple(QImage * im) // filtrage pour les tests : pas de rotation.
{
  *im = filtrer_median(*im, NBelt_listd);
  Image2Apercu(im);
}

/* On sauvegarde l'image modifiee apres filtrage */
void Fenetre::Sauvegarde()
{
  Picture = PictModif;
  PictModif.save("sauvegarde", "PNG" );
}

void Fenetre::Reconnaissance()
{
  Filtrage_simple(&Picture); // On repasse une couche de filtrage c mieu.
  // Reconnaissance des notes noire Pour le moment.
  p_lcord l;
  //  p_liste2 ll = TrouverLignes(&Picture);
  //  l = liste_noire(&Picture,CalculEspacement(ll));
  l = liste_noire(&Picture,18); /************************* ligne a modifier qd on regroupe tout *******/
  Image2Apercu(&Picture);
}

void Fenetre::CreationMidi()
{

}

void Fenetre::JouerMidi()
{

}
