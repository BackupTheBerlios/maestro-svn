#ifndef SAMI_H
#define SAMI_H

#include<qmainwindow.h>
#include<qpushbutton.h>



class Sami : public QMainWindow
{
  Q_OBJECT
 public:
  Sami(QWidget *parent=0, const char *name=0);
  ~Sami();
  QPushButton *But_filtre_gs;
};

#endif
