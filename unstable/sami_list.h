#include<qimage.h>
#ifndef SAMI_LIST_H
#define SAMI_LIST_H



typedef struct s_listd
{
    QRgb elt;
    struct s_listd * suiv;
} * listd ;



listd min_listed(listd);   
void sw_listed(listd, listd);
listd ajouter_listed(int, listd, int*);
QRgb median_listd(listd, int*);
void afficher_listd(listd, int*);
void tri_listd(listd);
void vider_listd(listd, int*);


#endif
