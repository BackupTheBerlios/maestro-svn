#ifndef LISTE_H
#define LISTE_H
#include<qrect.h>

typedef struct t_liste * p_liste;

typedef struct t_liste
{
    int n;
    p_liste p;
} t_liste;

typedef struct t_portee * p_portee;

typedef struct t_portee
{
    p_liste b;
    p_portee s;
} t_portee;

typedef struct t_coord * p_coord;

typedef struct t_coord
{
    QRect pos;
    p_coord next;
} t_coord;

typedef struct t_liste2 * p_liste2;

typedef struct t_liste2
{
  int ord;
  int larg;
  p_liste next;
} t_liste2;


void Ajouter_liste (p_liste * p, int i);

void Initialiser_liste (p_liste * p);

void Ajouter_portee(p_portee * p, p_liste pl);

void Initialiser_portee (p_portee * p);

#endif
