#include<stdio.h>
#include "reco.h"

#include <qimage.h>
#include <qpixmap.h>



// Le 'this' ne pointe vers rien
//void mat_Charger(QImage pix, QLabel *lblCadre)
//{
//   QPixmap pix2;
//   //   QImage img;
//
//   QString s = QFileDialog::getOpenFileName(	/* On demande de charger quelle image */
//					    ".",
//					    "Images (*.png *.xpm *.jpg *.gif *.bmp)",
//					    this,
//					    "Reco"
//					    "Choisi un fichier" );
//   
//    pix.load(s); 			/*On charge l'image dans b à partir du string s*/
//    pix2.convertFromImage(pix);
//    
//    lblCadre->setPixmap(pix2);
//    lblCadre->adjustSize();
//}


void mat_Filtrer(QLabel *lblCadre)
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Filtre(&img,200);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}

void mat_Filtrer_bien(QImage *pix, QLabel *lblCadre, int NBelt_listd,int s)
{
 QImage ima;
 QPixmap * img;
 // QImage pix;
 float angle;
 int w,h;
 
 // img = lblCadre->pixmap();
 //pix = img->convertToImage();
      
  //*******************************************************************/  

  *pix = filtrer_redim(*pix);

  w = pix->width();
  h = pix->height();
  lblCadre->setGeometry(QRect(10,130,w,h ));
  *pix = filtrer_grayscale(*pix);
  *pix = filtrer_seuillage(*pix,s);

    angle = rotation_calcul_angle(*pix);

  if (angle != 0.0)   
    ima = filtrer_rotation(*pix,angle);
  else
    ima = *pix;
  
  ima = filtrer_median(ima, NBelt_listd,s);
  lblCadre->setPixmap(ima);
  *pix = ima;
}


void mat_DelLignes(QLabel *lblCadre)
{
    QPixmap *pix;
    QImage img;
    p_liste2 l;
    float m;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    l = TrouverLignes(&img);
    // m = Max_Largeur(l);
    SupprimerLignes(&img, 8);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}


void mat_Eroder(QLabel *lblCadre)
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Eroder(&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}


void mat_Dilater(QLabel *lblCadre)
{
  QPixmap *pix;
  QImage img;
    
  pix = lblCadre->pixmap();
  img = pix->convertToImage();
  Dilater(&img);
  pix->convertFromImage(img);
  lblCadre->setPixmap(*pix);
}


void mat_FindLignes(QLabel *lblCadre)
{
    QString s;
    QPixmap *pix;
    QImage img;
    p_liste2 liste;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    liste = TrouverLignes(&img);
    while (liste != NULL)
    {
      printf("%i est une ligne de %i\n", liste->ord, liste->larg);
      liste = liste->next;
    }
    AfficherLignes(liste, &img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
    
}


void mat_Creuser(QLabel *lblCadre)
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Creuser(&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}
