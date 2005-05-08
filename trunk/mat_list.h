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
  p_liste2 next;
} t_liste2;


void Ajouter_liste (p_liste * p, int i);
void Initialiser_liste (p_liste * p);

void Ajouter_portee(p_portee * p, p_liste pl);
void Initialiser_portee (p_portee * p);

void Ajouter_coord(p_coord * p, int x1, int y1, int x2, int y2);
void Initialiser_coord(p_coord *p);
void Supprimer_coord(p_coord *p);

void Ajouter_liste2 (p_liste2 * p, int m, int n);
void Initialiser_liste2 (p_liste2 *p);
void Supprimer_liste2(p_liste2 *p);

#endif
