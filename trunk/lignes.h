#ifndef LIGNES_H
#define LIGNES_H

#include "mat_list.h"

p_liste TrouverLignes(QImage *img);

void SupprimerLignes(QImage *img);

void AfficherLignes(p_liste p, QImage *img);

#endif
