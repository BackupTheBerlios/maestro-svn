#include <qimage.h>
#include <qcolor.h>
#include "liste.h"
#include "reconnaissance.h"

void Morceau(QPoint p, QImage *img, QRect *r, QRgb *blanc)
{
  if (img->valid(p.x,p.y))
    {
      if (AGauche(r->topLeft,p))
	r->setLeft(p.x);
      if (EnHaut(r->topLeft,p))
	r->setTop(p.y);
      if (EnBas(r->bottomRight,p))
	r->setBottom(p.y);
      if (ADroite(r->bottomRight,p))
	r->setRight(p.x);
     
      img->setPixel(p.x,p.y,*blanc);

      if (!EgaleCouleur(blanc, img->pixel(p.x-1,p.y)))
	Morceau(QPoint(p.x-1,p.y),img,r,blanc);
      if (!EgaleCouleur(blanc, img->pixel(p.x+1,p.y)))
	Morceau(QPoint(p.x+1,p.y),img,r,blanc);
      if (!EgaleCouleur(blanc, img->pixel(p.x,p.y-1)))
	Morceau(QPoint(p.x,p.y-1),img,r,blanc);
      if (!EgaleCouleur(blanc, img->pixel(p.x,p.y+1)))
	Morceau(QPoint(p.x,p.y+1),img,r,blanc);
    }
}

p_liste TrouverMorceaux (QImage * img)
{
  int i,j;
  bool b = false, a;
  QRgb noir = qRgb(0,0,0), rouge = qRgb(255,0,0);
  p_liste p;

  Initialiser_liste(&p);

  for (i=0;img->valid(i,0);i++)
    {
      a = b;
      b = false;
      for(j=0;(img->valid(0,j)) && (!b);j++)
	{
	  if (img->pixel(i,j) == noir)
	    b = true;
	}
      if (a == (!b))
	Ajouter_liste(&p,i);
    }

  if (b)
    Ajouter_liste(&p,i-1);

  return p;
}
