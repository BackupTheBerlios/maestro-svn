#include <qimage.h>
#include <qcolor.h>
#include "filtre.h"

int Moyenne ( QRgb r)
{
    return ((qRed(r) + qGreen(r) + qBlue(r))/3);	/*moyenne non pond�r�e*/
}

void Filtre( QImage *img , int seuil)
{
  int i=0,j=0;			/*i va parcourir les abscisses et j les ordonn�es*/
  QRgb r;			/*r va prendre la couleur noir ou blanc*/
  
  for (i=0;img->valid(i,0);i++)	/*on parcours les abscisses*/
    {
      for(j=0;img->valid(0,j);j++)	/*puis les ordonn�es*/
	{
	  if (Moyenne(img->pixel(i,j)) > seuil)		/*on teste si un point est plus banc que noir*/
	    r = qRgb(255,255,255);	/*si il est plus noir, il devient noir*/
	  else				/*sinon*/
	    r = qRgb(0,0,0);		/*on le met � blanc*/
	  
	  img->setPixel(i,j,r);		/*on met � jour le pixel dans l'image*/
	}
    }
}
