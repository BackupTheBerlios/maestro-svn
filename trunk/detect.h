#ifndef DETECT_H
#define DETECT_H

#include <qmainwindow.h>
#include <qimage.h>

#include "mat_list.h"


class Detect : public QMainWindow
{
  Q_OBJECT
 public:
  Detect(QWidget *parent=0, const char *name=0);
  ~Detect();
};

#endif
