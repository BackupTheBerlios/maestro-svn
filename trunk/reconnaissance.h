#ifndef RECONNAISSANCE_H
#define RECONNAISSANCE_H

bool AGauche(QPoint pref, QPoint p);

bool EnHaut(QPoint pref, QPoint p);

void Morceau(QPoint p, QImage *img, QImage *copie, QRect *r);

p_liste_img TrouverMorceaux (QImage *img, int h);

void Efface(QImage *img, QRect r);

#endif
