#ifndef RECO_H
#define RECO_H

#include<qmainwindow.h>
#include<qpushbutton.h>
#include<qlabel.h>
#include<qfiledialog.h>

#include "filtre.h"
#include "lignes.h"
#include "mat_list.h"
#include "morpho.h"


class Reco : public QMainWindow
{
  Q_OBJECT
 public:
  Reco(QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel);
  ~Reco();

    QPushButton* btnCharger;
    QPushButton* btnFiltrer;
    QPushButton* btnEroder;
    QPushButton* btnDelLignes;
    QPushButton* btnDilater;
    QPushButton* btnFindLignes;
    QLabel* lblCadre;
    QLabel* lblLignes;
    QPushButton* btnCreuser;

public slots:
    virtual void btnCharger_clicked();
    virtual void btnFiltrer_clicked();
    virtual void btnDelLignes_clicked();
    virtual void btnEroder_clicked();
    virtual void btnDilater_clicked();
    virtual void btnFindLignes_clicked();
    virtual void btnCreuser_clicked();

protected:

protected slots:
    virtual void languageChange();
};

#endif
