#ifndef FENETRE_H
#define FENETRE_H

#include<qwidget.h>
#include<qmainwindow.h>
#include<qpushbutton.h>
#include<qstring.h>
#include<qimage.h>
#include<qlabel.h>
#include<qpixmap.h>
#include<qgroupbox.h>

#include"mat_list.h"



class Fenetre : public QMainWindow
{
  Q_OBJECT
 public:
  Fenetre(QWidget *parent=0, const char *name=0);
  ~Fenetre(); 

  /*Romain *rom;
  Sami *sam;
  Reco *rec;*/

  QPushButton *OpenBut;
  QPushButton *QuitBut;
  QPushButton *DetecBut;
  QGroupBox *PreviewCadre;
  QLabel *Apercu;

  QImage Picture;
  QString FilePath;
  int NBelt_listd;
  p_liste2 list_lignes;

    
  public slots:
    void OuvrirImage();
    void Image2Apercu(QImage *picture);
    void DetectLignes();
};

#endif
