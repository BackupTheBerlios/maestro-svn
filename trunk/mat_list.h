#ifndef LISTE_H
#define LISTE_H

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

void Ajouter_liste (p_liste * p, int i);

void Initialiser_liste (p_liste * p);

void Ajouter_portee(p_portee * p, p_liste pl);

void Initialiser_portee (p_portee * p);

#endif
