#ifndef LISTE_H
#define LISTE_H



typedef struct t_liste * p_liste;
typedef struct t_liste
{
  int n;
  p_liste p;
} t_liste;


p_liste Ajouter (p_liste p, int i);
p_liste Initialiser (p_liste p);


#endif
