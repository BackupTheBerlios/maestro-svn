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
  QPushButton *CBut;
  QPushButton *DBut;
  QPushButton *EBut;
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

  p_liste2 list_lignes;
  p_coord list_portees;

  int NBelt_listd;
  int largeur_ligne; // donne la largeur d'une ligne
  int espacement_ligne; // Donne l'espacement entre deux lignes d'une portee
    
  public slots:
    void OpenClick();
    void FiltClick();
    void RecoClick();
    void MusicClick();
    void AboutClick();
 
    void OuvrirImage();
    void Image2Apercu(QImage *picture);
    void DetectLignes();
    void VirerLignes();
    void Filtrage();
    void Sauvegarde();
    void Reconnaissance();
    void Filtrage_simple(QImage * im); // filtrage pour les tests : pas de rotation.
};

#endif
