#ifndef MAT_H
#define MAT_H

#include<qmainwindow.h>
#include<qcheckbox.h>
#include<qpushbutton.h>
#include<qlabel.h>
#include<qslider.h>
#include"mat_list.h"



class Mat : public QMainWindow
{
  Q_OBJECT
 public:
  Mat(QWidget *parent=0, const char *name=0);
  ~Mat();

  QCheckBox* radio;
  QPushButton* pushButton5;
  QLabel* textLabel1;
  QLabel* cadre;
  QPushButton* pushButton2;
  QPushButton* pushButton1;
  QCheckBox* Automatik;
  QSlider* slider1;
  QPushButton* pushButton3;

  virtual bool Fonction( QRgb r );
  virtual int Moyenne( QRgb r );
  virtual p_liste TrouverLignes( QImage * img );

 public slots:
  virtual void ChargerImage();
  virtual void Filtre(QImage *img);
  virtual void Reconnaissance(QImage *img);
  virtual void Reconnaitre();
  virtual void AfficherLignes(p_liste p, QImage *img);
  virtual void BoutonLigne();
  virtual void Filtre2(QImage *img);
  virtual void BoutonFiltre();
  virtual void slider1_valueChanged(int i);
};

#endif
