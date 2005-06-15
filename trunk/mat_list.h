#ifndef LISTE_H
#define LISTE_H
#include<qimage.h>
#include<qrect.h>
#include "morpho.h"

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

enum t_type {ronde, blanche, noire, croche, dcroche, tcroche, qcroche};

enum t_cle {sol, ut, fa};

union cle_note
{
  t_type note;
  t_cle cle;
} ;

typedef struct t_note
{
  cle_note type;
  int niveau;
} t_note;

typedef struct t_list_note * p_list_note;

typedef struct t_list_note
{
  bool cle;
  t_note info;
  p_list_note p;
} t_list_note;

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

void Ajouter_liste_note (p_list_note *p, bool cle, p_lcord s, int niv0, int d);

#endif
