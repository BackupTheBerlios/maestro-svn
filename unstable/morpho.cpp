#include "morpho.h"

bool EgaleCouleur(QRgb r1, QRgb r2)
{
    return ((qBlue(r1) == qBlue(r2)) && (qGreen(r1) == qGreen(r2)) && (qRed(r1) == qRed(r2)));
}

bool Present(QImage *img, int x, int y, QRgb couleur)
{
    if 	(
	    EgaleCouleur(img->pixel(x+1,y+1),couleur) ||
	    EgaleCouleur(img->pixel(x+1,y),couleur) ||
	    EgaleCouleur(img->pixel(x+1,y-1),couleur) ||
	    EgaleCouleur(img->pixel(x,y+1),couleur) ||
	    EgaleCouleur(img->pixel(x,y-1),couleur) ||
	    EgaleCouleur(img->pixel(x-1,y+1),couleur) ||
	    EgaleCouleur(img->pixel(x-1,y),couleur) ||
	    EgaleCouleur(img->pixel(x-1,y-1),couleur) 
	    )
    {
	return (true);
    }
    else
    {
	return (false);
    }
}

void Eroder(QImage * img)
{
    QImage img_copie;
    int x,y;
    QRgb blanc = qRgb(255,255,255);
    
    img_copie = img->copy();
    
    for (x=1; img->valid(x+1,1);x++)
    {
	for (y=1; img->valid(1,y+1); y++)
	{
	    if (Present(&img_copie, x,y,blanc))
		img->setPixel(x,y,blanc);
	}
    }
}

void Dilater(QImage * img)
{
    QImage img_copie;
    int x,y;
    QRgb noir = qRgb(0,0,0);
    
    img_copie = img->copy();
    
    for (x=1; img->valid(x+1,1);x++)
    {
	for (y=1; img->valid(1,y+1); y++)
	{
	    if (Present(&img_copie, x,y,noir))
		img->setPixel(x,y,noir);
	}
    }
}

void Fermer(QImage * img)
{
  Dilater(img);
  Eroder(img);
}

void Ouvrir(QImage * img)
{
  Eroder(img);
  Dilater(img);
}

void Creuser (QImage *img)
{
    QImage img_copie;
  int i,j;
  QRgb blanc = qRgb(255,255,255);

  img_copie = img->copy();
  
  for (i=1; img_copie.valid(i+1,0); i++)
    {
      for (j=1; img_copie.valid(0,j+1); j++)
	{
	  if (!(Present(&img_copie,i,j,blanc)))
	  	img->setPixel(i,j,blanc);
	}
    }	      
}
