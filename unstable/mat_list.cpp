#ifndef MAT_LIST_H
#define MAT_LIST_H
#include "mat_list.h"
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif



p_liste Ajouter (p_liste p, int i)
{
  p_liste t;
  t = p;
  while (t->p)
    t = t->p;
  (t->p) = (p_liste) (malloc(sizeof(t_liste)));
  t = t->p;
  t->n = i;
  t->p = NULL;

  return p;    
}

p_liste Initialiser (p_liste p)
{
  p = (p_liste) (malloc(sizeof(t_liste)));
  p->n = 0;
  p->p = NULL;
}