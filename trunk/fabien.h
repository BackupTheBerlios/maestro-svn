#ifndef FABIEN_H
#define FABIEN_H

#include <qmainwindow.h>
#include <qimage.h>
#include "mat_list.h"


class Fabien : public QMainWindow
{
  Q_OBJECT
 public:
  Fabien(QWidget *parent=0, const char *name=0);
  ~Fabien();

  bool Est_ligne(QImage *picture, int ord, QRgb noir, int precision);
  p_liste Liste_lignes(QImage *picture);
};

#endif
