#include<stdlib.h>
#include"sami_list.h"



listd min_listed(listd A) 
{
    listd B;
    
    B=A;
    while(A != NULL)
    {
      if (qBlue(A->elt) < qBlue(B->elt))
   B=A;
      A = A->suiv;
    }
    return(B);
}

void sw_listed(listd A, listd B)
{
   QRgb temp = (A->elt);
   A->elt = B->elt;
   B->elt = temp;
}

listd ajouter_listed(int x, listd A, int *NBelt_listd)
{
    listd b;
    b = (listd) malloc( sizeof(struct s_listd) );
    b->elt = qRgb(x,x,x);
    b->suiv = A;
    NBelt_listd++;
    return(b);
}
    
QRgb median_listd(listd a, int *NBelt_listd)
{
    int i=0;
    while((a != NULL) && i < ((*NBelt_listd-1) / 2))
    {
       a = a->suiv;
       i++;
   }
    return(a->elt);
}

void afficher_listd(listd a, int *NBelt_listd)
{
	listd b=a;
    while(a != NULL)
    {
     printf("%i ", qBlue(a->elt));
     a = a->suiv;
    }
    printf("\t%i -- %i \n",qBlue(median_listd(b, NBelt_listd)), *NBelt_listd);
}

void tri_listd(listd a)
{
    listd c;
    while(a != NULL)
    {
        c = min_listed(a);
        if (c->elt != a->elt)
     sw_listed(a,c);
        a = a->suiv;
    }
}

void vider_listd(listd A, int *NBelt_listd)
{
    listd B;
    NBelt_listd = 0;
    while(A != NULL)
    {
       B = A->suiv;
       free(A);
       A = B;
   }
}
