#ifndef SAMI_H
#define SAMI_H

#include<qmainwindow.h>
#include<qimage.h>
#include<qlabel.h>
#include<qscrollbar.h>
#include<qpushbutton.h>
#include<qstring.h>

#include"morpho.h"
#include"filtre.h"

extern QString FilePath;
extern QImage pix; // parametre global L'image en memoire

class Sami : public QMainWindow
{
  Q_OBJECT
 public:
  Sami(QWidget *parent=0, const char *name=0);
  ~Sami();


  QLabel *pmap;


  QPushButton *QuitBut;
  QPushButton * AffBut;
  //  QPushButton * RotBut;
  QPushButton * SavBut;
  QPushButton * CarcBut;


  public slots:
    void affichage();
  //  void rotation();  // connection pour le bouton de rotation
  void sauvegarder(); // Connection pour la sauvegarde;
  void carac(); //connection pour afficher les caracterisitques de l'image
};

#endif
