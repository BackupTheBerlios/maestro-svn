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

  return (i > depart/2);
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
      if (Est_ligne(picture, i, QRgb(0, 0, 0), 0))
	{
	  liste = Initialiser(liste);
	  liste->n = i;
	}
      i++;
    }
  while (i < fin)
    {
      if (Est_ligne(picture, i, QRgb(0, 0, 0), 0))
	Ajouter(liste, i);
      i++;
    }

  return liste;
}