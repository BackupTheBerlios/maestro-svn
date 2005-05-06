#include <qimage.h>
#include <qcolor.h>
#include "lignes.h"


// optimisation - lignes trouees
bool Est_ligne(QImage *picture, int ord, QRgb couleur, int depart, int g, int d)
{
  int i, gt, dt;

  i = 0;
  dt = d;
  gt = g;
  while (i < depart && ((dt > 0) && (gt > 0)))
    {
      if (picture->pixel(depart + i, ord) != couleur)
	dt--;
      else
	{
	  if (dt < d)
	    dt++;
	}
      if (picture->pixel(depart - i, ord) != couleur)
	gt--;
      else
	{
	  if (gt < g)
	    gt++;
	}
      i++;
    }

  return (i > (depart/3));
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
      if (Est_ligne(picture, i, qRgb(0, 0, 0), depart, 5, 5))
	{
	  cpt = 1;
	  while (Est_ligne(picture, i + cpt, qRgb(0, 0, 0), depart, 5, 5))
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

int EcartMin(p_liste2 liste)
{
  int debut, fin, res, temp;

  debut = liste->ord;
  liste = liste->next;
  fin = liste->ord;
  res = fin - debut;
  debut = fin;
  liste = liste->next;
  while (liste)
    {
      fin = liste->ord;
      temp = fin - debut;
      if (res > temp)
	res = temp;
      debut = fin;
      liste = liste->next;
    }

  return res;
}


p_coord GroupLignes(p_liste2 liste, int droite, int bas)
{
  p_coord result;
  int debut, fin, temp1, temp2, reference, ecart;

  Initialiser_coord(&result);
  debut = 0;
  reference = EcartMin(liste);
  temp1 = liste->ord;
  liste = liste->next;
  while (liste) 
    {
      temp2 = liste->ord;
      ecart = temp2 - temp1;
      if (ecart > 4 * reference)
	{ 
	  fin = temp1 + (ecart / 2);
	  Ajouter_coord(&result, 0, debut, droite, fin);
	  debut = fin + 1;
	}      
      temp1 = temp2;
      liste = liste->next;
      }
  Ajouter_coord(&result, 0, debut, droite, bas);
  
  return result;
}

int CalculLargeur(p_liste2 l)
{
int res=0;
p_liste2 tmp = l;
while(tmp)
{
  if (tmp->larg > res)
    res = tmp->larg;
  tmp = tmp->next;
}
return res;
}



int CalculEspacement(p_liste2 l)
{
int res=0,tmp2 = 0,i=1;
p_liste2 tmp = l;
while(tmp)
  {
    if (!tmp2)
      {
	tmp2 = tmp->ord;
      }
    else
      {
	res = res + (l->ord - tmp2);
	tmp2 = l->ord;
	i++;
      }
    tmp = tmp->next;
  }
 return (int(res/i));
}
