#include <qimage.h>
#include <qcolor.h>
#include "lignes.h"


bool Est_ligne(QImage *picture, int ord, QRgb couleur, int depart, int g, int d)
{
  int i;

  i = 0;
  while (picture->valid(depart + i, ord) && ((d > 0) || (g > 0)))
    {
      if (picture->pixel(depart + i, ord) != couleur)
	d--;
      if (picture->pixel(depart - i, ord) != couleur)
	g--;
      i++;
    }

  return (i > (depart/2));
}


p_liste2 TrouverLignes(QImage *picture)
{
  p_liste2 liste;
  int i, fin, cpt, depart;

  Initialiser_liste2(&liste);
  i = 0;
  fin = picture->height();
  depart = (picture->width())/2;

  while (i < fin)
    {
      if (Est_ligne(picture, i, qRgb(0, 0, 0), depart, 3, 3))
	{
	  cpt = 1;
	  while (Est_ligne(picture, i + cpt, qRgb(0, 0, 0), depart, 3, 3))
	      cpt++;
	  Ajouter_liste2(&liste, i, cpt);
	  i = i + cpt;
	}
      else
	i++;
    }

  return liste;
}

float Moyenne_Largeur(p_liste2 liste)
{
  float count;
  int nbr;

  count = nbr = 0;
  while (!(liste))
    {
      nbr++;
      count += liste->larg;
      liste = liste->next;
    }
  
  return (count/nbr);
}


float Max_Largeur(p_liste2 liste)
{
  float temp;

  temp = 0;
  while (!(liste))
    {
      if (temp < liste->larg)
	temp = liste->larg;
    }

  return temp;
}

void SupprimerLignes(QImage *img, int h)
{
    int i,j,t;
    QRgb blanc = qRgb(255,255,255);
     
    
    for (i=0;img->valid(i,0);i++)
    {
	t = 0;
	for (j=0;img->valid(0,j);j++)
	{
	    if ((img->pixel(i,j)) == blanc)
		if (t<=h)
		while(t)
		    img->setPixel(i,(j - (t--)),blanc);
		 else
		     t = 0;
	    else
		t++;
	}
    }
    
}

void AfficherLignes(p_liste2 p, QImage *img)
{
  int i;
  QRgb rouge = qRgb(255,0,0);
    
  while (p)
    {
      for (i=0;img->valid(i,0);i++)
	img->setPixel(i,p->ord,rouge);
      p = p->next;
    }
}
