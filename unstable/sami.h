#ifndef SAMI_H
#define SAMI_H

#include"morpho.h"
#include"filtre.h"

#include<qimage.h>
#include<qlabel.h>


void sami_affichage(QImage pix, QLabel *pmap);
//  void sami_rotation();  // connection pour le bouton de rotation
void sami_sauvegarder(QImage pix); // Connection pour la sauvegarde;
void sami_carac(QImage pix); //connection pour afficher les caracterisitques de l'image


#endif
