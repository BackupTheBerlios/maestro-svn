#include <qimage.h>
#include <qcolor.h>
#include "mat_list.h"
#include "lignes.h"

p_liste TrouverLignes(QImage *img)
{
    int i,j,s,d=0;
    QRgb noir = qRgb(0,0,0);
    p_liste p;
    
    Initialiser_liste(&p);
    
    for (j=0;(img->valid(0,j));j++)
    {
	s = 0;
	for (i=0;(img->valid(i,0));i++)
	{
	    if (img->pixel(i,j) == noir)
	    {
		s += 1;
	    }
	    
	}
	if ((s >= ((img->width())/2)) && ((j-d)>3))
	{
	    Ajouter_liste(&p,j);
	    d = j;
	}
    }
    
    return p;
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
