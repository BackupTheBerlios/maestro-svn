#ifndef SAMI_H
#define SAMI_H

#include<qmainwindow.h>
#include<qimage.h>
#include<qlabel.h>
#include<qscrollbar.h>
#include<qpushbutton.h>

extern QString FilePath;
extern QImage pix; // parametre global L'image en memoire

class Sami : public QMainWindow
{
  Q_OBJECT
 public:
  Sami(QWidget *parent=0, const char *name=0);
  ~Sami();

  // QPixmap pmap; // c l'image afficher
  int NBelt_listd;
  QLabel *pmap;
  QScrollBar *value1;


  QPushButton *QuitBut;
  QPushButton * AffBut;
  QPushButton * RotBut;



  QImage filtrer_grayscale(QImage pix); //  filtrage grayscale
  QImage filtrer_rotation( QImage im1, float angle ); // fais la rotation et renvoie l'image
  void image_vider(QImage pix); //vide l'image pix
  int arrondi(double a);
  QImage filtrer_median( QImage im1 );
  QImage filtrer_seuillage( QImage im1 );
  void sauvegarder();
  int rotation_proj( QImage im, int j );
  int filtrer_rot_calcul_proj(QImage pix);
  float rotation_calcul_angle(QImage pix);
  //  void calcul_angle(); // connection pour le calcul de l'angle de rotation

  public slots:
    void affichage();
  void rotation();  // connection pour le bouton de rotation

};

#endif
