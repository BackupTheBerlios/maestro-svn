#ifndef ROMAIN_H
#define ROMAIN_H

#include<qmainwindow.h>
#include<qimage.h>
#include<qpushbutton.h>
#include<qlabel.h>
#include<qbuttongroup.h>
#include<qtoolbar.h>
#include<qcheckbox.h>



class Romain : public QMainWindow
{
  Q_OBJECT
 public:
  Romain(QWidget *parent=0, const char *name=0);
  ~Romain();

  QImage img, img_d;
  float filtre[3][3];

  QPushButton* charger;
  QPushButton* Filter;
  QLabel* cadre;
  QButtonGroup* buttonGroup2;
  QCheckBox* niveaux;
  QCheckBox* gaussien;
  QCheckBox* laplacien;
  QCheckBox* noir;
  QCheckBox* passeh;
  QCheckBox* median;
  QCheckBox* selectif;
  QToolBar *Toolbar;

public slots:
  virtual void Charger();
  virtual void FiltrerImage( QImage * img_s, QImage * img_d, float a, float b, float c, float d, float e, float f, float g, float h, float z );
  virtual void Filtrer();
  virtual void FiltreGris( QImage * img );
  virtual void FiltreNoir( QImage * img );
  virtual void FiltreSelectif( QImage * img_s, QImage * img_d );
  virtual void FiltreMedian( QImage * img_s, QImage * img_d );
};

#endif
