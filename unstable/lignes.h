#ifndef LIGNES_H
#define LIGNES_H

#include "mat_list.h"

bool Est_ligne(QImage *picture, int ord, QRgb couleur, int precision);

p_liste TrouverLignes(QImage *picture);

float Moyenne_Largeur(p_liste2 liste);

float Max_Largeur(p_liste2 liste);

void SupprimerLignes(QImage *img,int h);

void AfficherLignes(p_liste p, QImage *img);

#endif
