#ifndef FILTRE_H
#define FILTRE_H

#include"sami_list.h"


void Charger(QImage * img);
int Moyenne ( QRgb r);
void Filtre( QImage *img , int seuil);


QImage filtrer_grayscale(QImage pix); //  filtrage grayscale
QImage filtrer_rotation( QImage im1, float angle ); // fais la rotation et renvoie l'image
void image_vider(QImage pix); //vide l'image pix
int arrondi(double a);
QImage filtrer_median( QImage im1, int NBelt_listd);
QImage filtrer_seuillage( QImage im1 );
QImage filtrer_redim(QImage pix); 
int rotation_proj( QImage im, int j );
int filtrer_rot_calcul_proj(QImage pix);
float rotation_calcul_angle(QImage pix);

#endif
