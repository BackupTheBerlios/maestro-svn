#include "fabien.h"


Fabien::Fabien(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  resize(200, 200);
  setCaption("Fabien");
}

Fabien::~Fabien()
{

}



// modif de sami : ca veut pas compiler alors je met en commentaire on verra ca plus tard
/*
// ENCORE DES MODIFS MAT A CHANGE LE NOM DE SON MAT_LIST ET SES FONCTIONS ALORS CA REMARCHE ENCORE PAS !!

bool Fabien::Est_ligne(QImage *picture, int ord, QRgb couleur, int precision)
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

p_liste Fabien::Liste_lignes(QImage *picture)
{
  p_liste liste;
  int i, fin;

  liste = NULL;
  i = 0;
  fin = picture->height();
  while ((i < fin) && (liste == NULL))
    {
      if (Est_ligne(picture, i, qRgb(0, 0, 0), 0))
	{
	  liste = Initialiser(liste);
	  liste->n = i;
	  i++;
	  while (Est_ligne(picture, i, qRgb(0, 0, 0), 0))
	    i++;
	}
      else
	i++;
    }
  while (i < fin)
    {
      if (Est_ligne(picture, i, qRgb(0, 0, 0), 0))
	{
	  Ajouter(liste, i);
	  i++;
	  while (Est_ligne(picture, i, qRgb(0, 0, 0), 0))
	    i++;
	}
      else
	i++;
    }

  return liste;
}
*/
