#ifndef LIGNES_H
#define LIGNES_H

#include "mat_list.h"

bool Est_ligne(QImage *picture, int ord, QRgb couleur, int precision);

p_liste TrouverLignes(QImage *picture);

void SupprimerLignes(QImage *img);

void AfficherLignes(p_liste p, QImage *img);

#endif
