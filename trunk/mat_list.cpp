#include "mat_list.h"
#include<qpoint.h>
#include <stdlib.h>
#include "reco.h"
#include "note.h"


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

void Ajouter_coord(p_coord * p, int x1, int y1, int x2, int y2, int ligne)
{
  while ((*p))
    p = &((*p)->next);
  
  if (!(*p))
    {
      (*p) = (p_coord) (malloc(sizeof(t_coord)));
      (*p)->pos = QRect(QPoint(x1, y1), QPoint(x2, y2));
      (*p)->ligne = ligne;
      (*p)->next = NULL;
    }       
}

void Supprimer_coord(p_coord *p)
{
  p_coord temp;

  while (*p)
    {
      temp = *p;
      *p = (*p)->next;
      free(temp);
    }
}




/*** LISTE2 ***/

void Ajouter_liste2(p_liste2 *p, int m, int n)
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

void Supprimer_liste2(p_liste2 *p)
{
  p_liste2 temp;

  while (*p)
    {
      temp = *p;
      *p = (*p)->next;
      free(temp);
    }
}

void Initialiser_liste_img (p_liste_img *p)
{
  *p = NULL;
}

void Ajouter_liste_img (p_liste_img *p, QImage img, QRect rect)
{
  p_liste_img pointeur;
  
  while (*p)
   p = &((*p)->p);
   
  pointeur = (p_liste_img) malloc (sizeof(t_liste_img));
  /*pointeur->img = img.copy();*/
  pointeur->r = rect;
  pointeur->p = NULL;
  
  (*p) = pointeur;
}

void Fusion_liste_img (p_liste_img *p1,p_liste_img p2)
{
    while (*p1)
   p1 = &((*p1)->p);
   
   (*p1)= p2;
}

void Initialiser_liste_note (p_list_note *p)
{
  (*p) = NULL;
}

void Ajouter_liste_note (p_list_note *p, int cle, p_lcord s, int niv0, int d)
{
  t_note t;
  
  while (*p)
    p = &((*p)->p);
  
  if (cle=3)
  {
    while (s)
    {
      (*p) = (p_list_note) malloc(sizeof(t_list_note));
      (*p)->cle = false;
      t.type.note = noire; /* trouver le type */
      t.niveau = niveau (s->y, niv0, d);
      (*p)->info = t;
      (*p)->p = NULL;
      s = s->suivant;
      p = &((*p)->p);
    }
  }
  else
  {
     (*p) = (p_list_note) malloc(sizeof(t_list_note));
     (*p)->cle=true;
     switch(cle) 
     {
       case 0 : t.type.cle = fa;
       break;
       case 1 : t.type.cle = sol;
       break;
       case 2 : t.type.cle = ut;
     };
     t.niveau = 0;
     (*p)->info = t;
     (*p)->p = NULL; 
  }
}
