#ifndef SAMI_H
#define SAMI_H

#include<qmainwindow.h>
#include<qimage.h>
#include<qlabel.h>
#include<qscrollbar.h>
#include<qpushbutton.h>
#include<qstring.h>

#include"morpho.h"

extern QString FilePath;
extern QImage pix; // parametre global L'image en memoire

class Sami : public QMainWindow
{
  Q_OBJECT
 public:
  Sami(QWidget *parent=0, const char *name=0);
  ~Sami();

  int NBelt_listd;
  QLabel *pmap;


  QPushButton *QuitBut;
  QPushButton * AffBut;
  QPushButton * RotBut;
  QPushButton * SavBut;
  QPushButton * CarcBut;


  QImage filtrer_grayscale(QImage pix); //  filtrage grayscale
  QImage filtrer_rotation( QImage im1, float angle ); // fais la rotation et renvoie l'image
  void image_vider(QImage pix); //vide l'image pix
  int arrondi(double a);
  QImage filtrer_median( QImage im1 );
  QImage filtrer_seuillage( QImage im1 );
  QImage filtrer_redim(QImage pix); 
  int rotation_proj( QImage im, int j );
  int filtrer_rot_calcul_proj(QImage pix);
  float rotation_calcul_angle(QImage pix);


  public slots:
    void affichage();
  void rotation();  // connection pour le bouton de rotation
  void sauvegarder(); // Connection pour la sauvegarde;
  void carac(); //connection pour afficher les caracterisitques de l'image
};

#endif
