#include "mat_list.h"
#include <stdlib.h>

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
