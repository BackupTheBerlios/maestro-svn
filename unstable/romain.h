#ifndef ROMAIN_H
#define ROMAIN_H

#include <qimage.h>
#include <qcheckbox.h>
#include <qlabel.h>


// void rom_Charger();
void rom_FiltrerImage(QImage *img_s, QImage *img_d, float a, float b, float c, float d, float e, float f, float g, float h, float z );
void rom_Filtrer(QImage img, QImage img_d, QLabel *cadre, QCheckBox *gaussien, QCheckBox *laplacien, QCheckBox *passeh, 
		 QCheckBox *niveaux, QCheckBox *noir, QCheckBox *selectif, QCheckBox *median);
void rom_FiltreGris( QImage *img );
void rom_FiltreNoir( QImage *img );
void rom_FiltreSelectif( QImage *img_s, QImage *img_d );
void rom_FiltreMedian( QImage *img_s, QImage *img_d );



#endif
