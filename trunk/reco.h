#ifndef RECO_H
#define RECO_H

#include<qlabel.h>
#include<qfiledialog.h>

#include "filtre.h"
#include "lignes.h"
#include "mat_list.h"
#include "morpho.h"



//void mat_Charger(QImage pix, QLabel *lblCadre);
void mat_Filtrer(QLabel *lblCadre);
void mat_Filtrer_bien(QImage *pix, QLabel *lblCadre, int NBelt_listdm,int s);
void mat_DelLignes(QLabel *lblCadre);
void mat_Eroder(QLabel *lblCadre);
void mat_Dilater(QLabel *lblCadre);
void mat_FindLignes(QLabel *lblCadre);
void mat_Creuser(QLabel *lblCadre);


#endif
