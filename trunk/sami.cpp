#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include"sami_list.h"

#include"sami.h"

Sami::Sami(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  resize(800, 600);
  setCaption("Sami");
  NBelt_listd = 0;

  pmap = new QLabel(this);

  QuitBut = new QPushButton(this, "QuitBut");
  QuitBut->setText("Quit");
  QuitBut->move(10, 80);

  AffBut =  new QPushButton(this, "AffBut");
  AffBut->setText("Afficher");
  AffBut->move(10,110);

  /*  RotBut = new QPushButton(this, "RotBut");
  RotBut->setText("Filtrer");
  RotBut->move(10, 140);*/

  SavBut = new QPushButton(this, "SavBut");
  SavBut->setText("Sauvegarder");
  SavBut->move(10, 140);

  CarcBut = new QPushButton(this, "CarcBut");
  CarcBut->setText("Caracteristiques");
  CarcBut->move(10, 170);

  connect(QuitBut, SIGNAL(clicked()), this, SLOT(close()));
  connect(AffBut, SIGNAL(clicked()), this, SLOT(affichage()));
  /* connect(RotBut, SIGNAL(clicked()), this, SLOT(rotation()));*/
  connect(SavBut, SIGNAL(clicked()), this, SLOT(sauvegarder()));
  connect(CarcBut, SIGNAL(clicked()), this, SLOT(carac()));

}

Sami::~Sami()
{

}

void Sami::affichage() //connection pour le bouton afficher
{
  int w,h;
  //  pix = QImage::QImage(FilePath); //on charge l'image en memoire
  
    w = pix.width();
    h = pix.height();    

    pmap->setGeometry(QRect(120,40,w,h ));

     pmap->setPixmap(pix);  
}


void Sami::sauvegarder() //connection pour le boutton sauvegarder
{
  pix.save("sauvegarde.png", "PNG");    
}


/*
void Sami::rotation() // connection Pour le boutton proj
{
  QImage ima;
  float angle;
  int w,h;
  

  pix = filtrer_redim(pix);

  w = pix.width();
  h = pix.height();
  pmap->setGeometry(QRect(120,40,w,h ));
  pix = filtrer_grayscale(pix);
  pix = filtrer_seuillage(pix);

    angle = rotation_calcul_angle(pix);

  if (angle != 0.0)   
    ima = filtrer_rotation(pix,angle);
  else
    ima = pix;
  
  ima = filtrer_median(ima);
  pmap->setPixmap(ima);
  pix = ima; 
}
*/

void Sami::carac()
{
  /**  printf("Fichier : %s", FilePath.ascii());**/
  afficher_caracteristique_cle(caracteristiques_cle(&pix));
  afficher_cle(&pix);
}
