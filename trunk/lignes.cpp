#include <qimage.h>
#include <qcolor.h>
#include "lignes.h"



bool Est_ligne(QImage *picture, int ord, QRgb couleur, int precision)
{
  int i, depart;

  i = 0;
  depart = (picture->width())/2;
  while (picture->valid(depart + i, ord) && precision >= 0)
    {
      if (picture->pixel(depart + i, ord) != couleur)
	precision--;
      if (picture->pixel(depart - i, ord) != couleur)
	precision--;
      i++;
    }

  return (i > (depart/2));
}

p_liste2 TrouverLignes(QImage *picture)
{
  p_liste2 liste;
  int i, fin, cpt;

  liste = NULL;
  i = 0;
  cpt = 0;
  fin = picture->height();
  while ((i < fin) && (liste == NULL))
    {
      if (Est_ligne(picture, i, qRgb(0, 0, 0), 0))
	{
	  Initialiser_liste2(&liste);
	  cpt++;
	  while (Est_ligne(picture, i + cpt, qRgb(0, 0, 0), 0))
	      cpt++;
	  Ajouter_liste2(&liste, i, cpt);
	  i = i + cpt;
	}
      else
	i++;
    }
  while (i < fin)
    {
      cpt = 0;
      if (Est_ligne(picture, i, qRgb(0, 0, 0), 0))
	{
	  cpt++;
	  while (Est_ligne(picture, i, qRgb(0, 0, 0), 0))
	    cpt++;
	  Ajouter_liste2(&liste, i, cpt);
	  i = i + cpt;
	}
      else
	i++;
    }

  return liste;
}

void SupprimerLignes(QImage *img)
{
    const int h=3;
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

void AfficherLignes(p_liste p, QImage *img)
{
    int i;

    QRgb rouge = qRgb(255,0,0);
    

    
    while (p)
    {
	for (i=0;img->valid(i,0);i++)
	    img->setPixel(i,p->n,rouge);
	p = p->p;
    }
}
