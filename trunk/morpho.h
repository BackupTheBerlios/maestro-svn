#ifndef MORPHO_H
#define MORPHO_H

#include <qimage.h>
#include <qcolor.h>

bool EgaleCouleur(QRgb r1, QRgb r2);

bool Present(QImage *img, int x, int y, QRgb couleur);

void Eroder(QImage * img);

void Dilater(QImage * img);

void Fermer(QImage * img);

void Ouvrir(QImage * img);

void Creuser(QImage * img);

#endif
