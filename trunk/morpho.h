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


// Type pour la reconnaissance des cles, on recupere les caracteristiques de l'image
typedef struct s_reconnaissance_cle t_rcle;
struct s_reconnaissance_cle
{
  int largeur; // largeur de l'image passee en parametre
  int hauteur; // hauteur de l'image passee en parametre
  int debutv,finv; // hauteur du debut et fin de la forme.
  int debuth,finh; // largeur du debut et fin de la forme.
  int projh; // emplacement ou la projection horizontale est maximale
  int projhed; // projection horizontale avec une erosion et une dilatation
  int projheedd; // projection horizontale avec deux erosions et deux dilatations
  int projv;
  int projved;
  int projveedd;
};



int projection_horizontale(QImage * im, int j);

int projection_verticale(QImage * im, int i);

int projh(QImage * im);

int projv(QImage * im);

t_rcle caracteristiques_cle(QImage * im);

void afficher_caracteristique_cle(t_rcle res);

int reconnaissance_cle(QImage * im);//0:fa 1:sol 2:ut

void afficher_cle(QImage * im);

/***** Reconnaissance des notes de musique ***/

typedef struct s_lcord * p_lcord; // liste de coordonnees x y;
struct s_lcord
{
  int x;
  int y;
  p_lcord suivant;
};
int largeur_noir(int x, int y, QImage * im ,int esp);
int hauteur_noir(int x, int y, QImage * im,int esp);
void ajouter_plcord(p_lcord * p, int x, int y);
void verifie_point( int esp, int x, int y, QImage * im, p_lcord * liste);
p_lcord liste_noire (QImage * im, int esp );
void dessiner_croix(QImage * im, QRgb coul, int x, int y);



#endif
