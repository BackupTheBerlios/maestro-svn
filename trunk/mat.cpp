#include<qpoint.h>

#include"mat.h"


Mat::Mat(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  resize(200, 200);
  setCaption("Mat");
}

Mat::~Mat()
{

}
