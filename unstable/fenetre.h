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
#include<qcheckbox.h>
#include<qsound.h>
#include<qmessagebox.h>

#include"mat_list.h"



class Fenetre : public QMainWindow
{
  Q_OBJECT
 public:
  Fenetre(QWidget *parent=0, const char *name=0);
  ~Fenetre(); 

  QPushButton *OpenBut;
  QPushButton *FiltBut;
  QPushButton *RecoBut;
  QPushButton *MusicBut;
  QPushButton *AboutBut;
  QPushButton *QuitBut;

  QPushButton *ABut;
  QPushButton *BBut;
  QCheckBox *ABox;
  QCheckBox *BBox;
  QGroupBox *AGroup;
  QLabel *ALabel;
  
  QGroupBox *PreviewCadre;
  QLabel *Apercu;
  QMessageBox *APropos;

  QImage Picture;
  QImage PictModif;
  QString FilePath;
  int NBelt_listd;

  p_liste2 list_lignes;
  p_coord list_portees;

  QSound *midi;

    
  public slots:
    void OuvrirImage();
    void Image2Apercu(QImage *picture);
    void SteackHache();
    void DetectLignes();
    void Filtrage();
    void Sauvegarde();

    void OpenClick();
    void FiltClick();
    void RecoClick();
    void MusicClick();
    void AboutClick();
};

#endif
