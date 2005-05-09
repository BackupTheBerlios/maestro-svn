#ifndef LISTE_H
#define LISTE_H
#include<qimage.h>
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
    int ligne;
    p_coord next;
} t_coord;

typedef struct t_liste2 * p_liste2;

typedef struct t_liste2
{
  int ord;
  int larg;
  p_liste2 next;
} t_liste2;

typedef struct t_liste_img * p_liste_img;

typedef struct t_liste_img
{
  QImage img;
  QRect r;
  p_liste_img p;
} t_liste_img;


void Ajouter_liste (p_liste * p, int i);
void Initialiser_liste (p_liste * p);

void Ajouter_portee(p_portee * p, p_liste pl);
void Initialiser_portee (p_portee * p);

void Ajouter_coord(p_coord * p, int x1, int y1, int x2, int y2, int ligne);
void Supprimer_coord(p_coord *p);

void Ajouter_liste2 (p_liste2 * p, int m, int n);
void Supprimer_liste2(p_liste2 *p);

void Initialiser_liste_img (p_liste_img *p);
void Ajouter_liste_img (p_liste_img *p, QImage img, QRect r);
void Fusion_liste_img (p_liste_img *p1,p_liste_img p2);

#endif
