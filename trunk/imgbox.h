#ifndef IMGBOX_H
#define IMGBOX_H

#include<qwidget.h>
#include<qgroupbox.h>
#include<qstring.h>
#include<qimage.h>
#include<qpixmap.h>


class ImageBox : public QGroupBox
{
	Q_OBJECT
public:
  ImageBox(QWidget *parent, const char *name);
  ~ImageBox();
  
  QPixmap Apercu;
};

#endif
