#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include"sami_list.h"
#include"sami.h"



void sami_affichage(QImage pix, QLabel *pmap) //connection pour le bouton afficher
{
  int w,h;
  //  pix = QImage::QImage(FilePath); //on charge l'image en memoire
  
    w = pix.width();
    h = pix.height();    

    pmap->setGeometry(QRect(120,40,w,h ));

     pmap->setPixmap(pix);  
}


void sami_sauvegarder(QImage pix) //connection pour le boutton sauvegarder
{
  pix.save("sauvegarde.png", "PNG");    
}


/*
void sami_rotation() // connection Pour le boutton proj
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

void sami_carac(QImage pix)
{
  /**  printf("Fichier : %s", FilePath.ascii());**/
  afficher_caracteristique_cle(caracteristiques_cle(&pix));
  afficher_cle(&pix);
}
