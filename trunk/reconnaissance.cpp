#include <qimage.h>
#include <qcolor.h>
#include "mat_list.h"
#include "reconnaissance.h"
#include "morpho.h"

bool AGauche(QPoint pref, QPoint p)
{
	return (pref.x() > p.x());
}

bool EnHaut(QPoint pref, QPoint p)
{
	return (pref.y() > p.y());
}


void Morceau(QPoint p, QImage *img, QImage *copie, QRect *r)
{
  if (EgaleCouleur(qRgb(0,0,0), img->pixel(p.x(),p.y())))
    {
      if (AGauche(r->topLeft(),p))
	r->setLeft(p.x());
      if (EnHaut(r->topLeft(),p))
	r->setTop(p.y());
      if (!EnHaut(r->bottomRight(),p))	/* En Bas */
	r->setBottom(p.y());
      if (!AGauche(r->bottomRight(),p))	/* A Droite */
	r->setRight(p.x());
     
      img->setPixel(p.x(),p.y(),qRgb(255,255,255));
      copie->setPixel(p.x(),p.y(),qRgb(0,0,0));
	
      if ((img->valid(p.x()-1,p.y())) && (EgaleCouleur(qRgb(0,0,0), img->pixel(p.x()-1,p.y()))))
	Morceau(QPoint(p.x()-1,p.y()),img,copie,r);
      if ((img->valid(p.x()+1,p.y())) && (EgaleCouleur(qRgb(0,0,0), img->pixel(p.x()+1,p.y()))))
	Morceau(QPoint(p.x()+1,p.y()),img,copie,r);
      if ((img->valid(p.x(),p.y()-1)) && (EgaleCouleur(qRgb(0,0,0), img->pixel(p.x(),p.y()-1))))
	Morceau(QPoint(p.x(),p.y()-1),img,copie,r);
      if ((img->valid(p.x(),p.y()+1)) && (EgaleCouleur(qRgb(0,0,0), img->pixel(p.x(),p.y()+1))))
	Morceau(QPoint(p.x(),p.y()+1),img,copie,r);
    }
}

p_liste_img TrouverMorceaux (QImage * img, int h)
{
  int i,j;
  QRect rect;
  QRgb noir = qRgb(0,0,0);
  p_liste_img p;
  QImage copie = QImage(img->width(),img->height(),img->depth()),tmp;
  
  Initialiser_liste_img(&p);
  
  for (i=0;img->valid(i,0);i++)
    {
      for(j=0;img->valid(0,j);j++)
	{
	  if (img->pixel(i,j) == noir)
	    {
	    	rect.setTopLeft(QPoint(i,j));
		rect.setBottomRight(QPoint(i,j));
	    	Morceau(QPoint(i,j),img,&copie,&rect);
		if ((rect.width() > h/3) && (rect.height() > h/3))
		  {
		  tmp = copie.copy(rect);
		  Efface(&copie,rect);
		  Ajouter_liste_img(&p,tmp,rect);
	          }
	    }
	}
    }

  return p;
}

void Efface(QImage *img, QRect r)
{
  int i,j;
  QRgb blanc = qRgb(255,255,255);
  
  for (i=r.left();i<=r.right();i++)
  {
    for (j=r.top();j<=r.bottom();j++)
    {
      img->setPixel(i,j,blanc);
    }
  }
}
