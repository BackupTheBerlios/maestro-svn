#ifndef LIGNES_H
#define LIGNES_H

#include "mat_list.h"

bool Est_ligne(QImage *picture, int ord, QRgb couleur, int depart, int g, int d);

p_liste2 TrouverLignes(QImage *picture);

float Moyenne_Largeur(p_liste2 liste);

float Max_Largeur(p_liste2 liste);

void SupprimerLignes(QImage *img,int h);

void AfficherLignes(p_liste2 p, QImage *img);

#endif
