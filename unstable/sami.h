#ifndef SAMI_H
#define SAMI_H

#include<qmainwindow.h>
#include<qimage.h>
#include<qlabel.h>
#include<qscrollbar.h>

  

class Sami : public QMainWindow
{
  Q_OBJECT
 public:
  Sami(QWidget *parent=0, const char *name=0);
  ~Sami();

  QImage pix; // parametre global L'image en memoire
// QPixmap pmap c l'image afficher
  int NBelt_listd;
  QLabel *pmap;
  QScrollBar *value1;

  void test_affichage();
  void filtrer_grayscale();
  void rotation();  
  QImage filtrer_rotation( QImage im1, float angle );
  void image_vider(QImage pix);
  int arrondi(double a);
  void test();
  QImage filtrer_median( QImage im1 );
  QImage filtrer_seuillage( QImage im1 );
  void sauvegarder();
  int rotation_proj( QImage im, int j );
  int filtrer_rot_calcul_proj(QImage pix);
  float rotation_calcul_angle();
  void calcul_angle();
};

#endif
