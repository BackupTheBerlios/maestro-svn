#ifndef FENETRE_H
#define FENETRE_H

#include<qwidget.h>
#include<qmainwindow.h>
#include<qpushbutton.h>

#include<imgbox.h>
#include"fabien.h"
#include"sami.h"
#include"romain.h"
#include"mat.h"


class QPushButton;

class Fenetre : public QMainWindow
{
  Q_OBJECT
 public:
  Fenetre(QWidget *parent=0, const char *name=0);
  ~Fenetre(); 

  Fabien *fab;
  Romain *rom;
  Sami *sam;
  Mat *m;

  QPushButton *OpenBut;
  QPushButton *QuitBut;
  ImageBox *PreviewCadre;
  QImage Partition;
  
  public slots:
    void OuvrirImage();
};

#endif
