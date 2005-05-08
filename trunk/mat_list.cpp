#include "mat_list.h"
#include<qpoint.h>
#include <stdlib.h>



/*** LISTE ***/

void Ajouter_liste (p_liste * p, int i)
{
  while ((*p) && (((*p)->n) != i))
    p = &((*p)->p);
  
  if (!(*p))
    {
      (*p) = (p_liste) (malloc(sizeof(t_liste)));
      (*p)->n = i;
      (*p)->p = NULL;
    }       
}

void Initialiser_liste (p_liste *p)
{
  *p = NULL;
}



/*** PORTEE ***/

void Initialiser_portee (p_portee *p)
{
  *p = NULL;
}

void Ajouter_portee(p_portee *p, p_liste pl)
{
  while (*p)
    p = &((*p)->s);
  
  (*p) = (p_portee) malloc(sizeof(t_portee));
  
  (*p)->b = pl;
  (*p)->s = NULL;
}




/*** COORD ***/

void Ajouter_coord(p_coord * p, int x1, int y1, int x2, int y2)
{
  while ((*p))
    p = &((*p)->next);
  
  if (!(*p))
    {
      (*p) = (p_coord) (malloc(sizeof(t_coord)));
      (*p)->pos = QRect(QPoint(x1, y1), QPoint(x2, y2));
      (*p)->next = NULL;
    }       
}

void Initialiser_coord(p_coord *p)
{
  *p = NULL;
}

void Supprimer_coord(p_coord *p)
{
  p_coord temp;

  while ((*p))
    {
      temp = *p;
      *p = (*p)->next;
      free(temp);
    }
}




/*** LISTE2 ***/

void Ajouter_liste2(p_liste2 * p, int m, int n)
{
  while ((*p))
    p = &((*p)->next);
  
  if (!(*p))
    {
      (*p) = (p_liste2) (malloc(sizeof(t_liste2)));
      (*p)->ord = m;
      (*p)->larg = n;
      (*p)->next = NULL;
    }       
}

void Initialiser_liste2(p_liste2 *p)
{
  *p = NULL;
}

void Supprimer_liste2(p_liste2 *p)
{
  p_liste2 temp;

  while ((*p))
    {
      temp = *p;
      *p = (*p)->next;
      free(temp);
    }
}
