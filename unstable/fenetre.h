#ifndef FENETRE_H
#define FENETRE_H

#include<qwidget.h>
#include<qmainwindow.h>
#include<qpushbutton.h>
#include<qstring.h>
#include<qimage.h>
#include<qlabel.h>
#include<qpixmap.h>

#include"imgbox.h"
#include"detect.h"
#include"sami.h"
#include"romain.h"
#include"reco.h"


extern QString FilePath;
extern QImage pix;

class QPushButton;

class Fenetre : public QMainWindow
{
  Q_OBJECT
 public:
  Fenetre(QWidget *parent=0, const char *name=0);
  ~Fenetre(); 

  Detection *detec;
  Romain *rom;
  Sami *sam;
  Reco *rec;

  QPushButton *OpenBut;
  QPushButton *QuitBut;
  QPushButton *DetecBut;
  QPushButton *RecBut;
  QPushButton *SamBut;
  QPushButton *RomBut;
  ImageBox *PreviewCadre;
  QLabel *Apercu;

    
  public slots:
    void OuvrirImage();
};

#endif
