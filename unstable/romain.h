#ifndef ROMAIN_H
#define ROMAIN_H

#include<qmainwindow.h>
#include <qimage.h>
#include<qfiledialog.h>


class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QButtonGroup;
class QLineEdit;
class QPushButton;
class QLabel;
class QCheckBox;



class Romain : public QMainWindow
{
  Q_OBJECT
 public:
  Romain(QWidget *parent=0, const char *name=0);
  ~Romain();
  void Charger();
  void FiltrerImage(QImage *img_s, QImage *img_d, float a, float b, float c, float d, float e, float f, float g, float h, float z );
  void Filtrer();
  void FiltreGris( QImage *img );
  void FiltreNoir( QImage *img );
  void FiltreSelectif( QImage *img_s, QImage *img_d );
  void FiltreMedian( QImage *img_s, QImage *img_d );

  QImage img, img_d;
  float filtre[3][3];


  QButtonGroup * MatricePassage;
  QLineEdit * case1;
  QLineEdit * case2;
  QLineEdit * case3;
  QLineEdit * case4;
  QLineEdit * case5;
  QLineEdit * case6;
  QLineEdit * case7;
  QLineEdit * case8;
  QLineEdit * case9;
  QPushButton * charger;
  QPushButton * Filter;
  QLabel * cadre;
  QButtonGroup * buttonGroup2;
  QCheckBox * niveaux;
  QCheckBox * gaussien;
  QCheckBox * laplacien;
  QCheckBox * noir;
  QCheckBox * passeh;
  QCheckBox * median;
  QCheckBox * selectif;
  QToolBar * Toolbar;


};

#endif
