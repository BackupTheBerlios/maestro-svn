#ifndef DETECT_H
#define DETECT_H

#include<qmainwindow.h>
#include<qpushbutton.h>


class Detection : public QMainWindow
{
  Q_OBJECT
 public:
  Detection(QWidget *parent=0, const char *name=0);
  ~Detection();

  QPushButton *DectLignes;


  public slots:
    void DetectLignes();
};

#endif
