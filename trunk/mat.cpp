#include<qimage.h>
#include<qpixmap.h>
#include<qfiledialog.h>

#include"mat.h"


Mat::Mat(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  resize(400, 400);
  setCaption("Mat");

  pushButton1 = new QPushButton(this, "pushButton1" );
  pushButton2 = new QPushButton(this, "pushButton2" );
  pushButton3 = new QPushButton(this, "pushButton3" );
  pushButton5 = new QPushButton(this, "pushButton5" );
  textLabel1 = new QLabel(this, "textLabel1" );
  cadre = new QLabel(this, "cadre" );
  radio = new QCheckBox(this, "radio" );
  Automatik = new QCheckBox(this, "Automatik" );
  slider1 = new QSlider(this, "slider1" );

  pushButton1->setText("Charger");
  pushButton2->setText("Reconnaitre");
  pushButton5->setText("Filtre 2");
  
  pushButton1->move(10, 10);
  pushButton2->move(10, 80);
  pushButton3->move(10, 120);
  pushButton5->move(10, 150);
  textLabel1->move(120, 10);
  cadre->move(120, 60);
  radio->move(120, 100);
  Automatik->move(200, 10);
  slider1->move(200, 50);

  radio->setChecked( TRUE );
  slider1->setMaxValue( 255 );
  slider1->setValue( 80 );
  slider1->setOrientation( QSlider::Horizontal );
}

Mat::~Mat()
{

}

void Mat::ChargerImage()
{
  QImage img;
  QPixmap p;
  bool b;
  p_liste t;
  
  QString s = QFileDialog::getOpenFileName(
					   ".",
					   "Images (*.png *.xpm *.jpg *.gif *.bmp)",
					   this,
					   "Mat"
					   "Choisi un fichier" );
  b = img.load(s); 
   
  if (Automatik->isChecked())
    {
      slider1->setValue(200);
      Filtre(&img);
      t = TrouverLignes(&img);       
      Filtre2(&img);
      AfficherLignes(t,&img);
    }
  else     
    if (radio->isChecked())
      Filtre(&img);
  b = p.convertFromImage(img);
  cadre->setAutoResize(true);
  cadre->setPixmap(p);
}


void Mat::Filtre( QImage *img )
{
  int i=0,j=0;
  QRgb r;
 
  for (i=0;img->valid(i,0);i++)
    {
      for(j=0;img->valid(0,j);j++)
	{
	  if (Fonction(img->pixel(i,j)))
	    r = qRgb(255,255,255);
	  else
	    r = qRgb(0,0,0);
	  img->setPixel(i,j,r);
	}
    }
}


bool Mat::Fonction( QRgb r )
{
  if (/*qGray(r)*/ Moyenne(r) >= (slider1->value()))
      return true;
    else
      return false;
}

int Mat::Moyenne ( QRgb r)
{
  return ((qRed(r) + qGreen(r) + qBlue(r))/3);
}

void Mat::Reconnaissance(QImage *img)
{
  int i=0,j=0;
  bool b = false,a = false;
  QRgb rose = qRgb(128,0,128), noir =qRgb(0,0,0);
  p_liste p=NULL;
    
  p = Initialiser(p);
  for (i=0;img->valid(i,0);i++)
    {
      a = b;
      b = false;
      for(j=0;(img->valid(0,j)) && (!b);j++)
	{
	  if (img->pixel(i,j) == noir)
	    b = true;
	}
      if (a == (!b))
	Ajouter(p,i);
    }
  Ajouter(p,(i-1));
    
  while (p)
    {
      for (i=(p->n);i<=(p->p->n);i++)
	{
	  for(j=0;(img->valid(0,j)) && (!b);j++)
	    {
	      img->setPixel(i,j,rose);
	    }
	}
      p = p->p->p;
    }
}


void Mat::Reconnaitre()
{
  QImage img;
  QPixmap p;
  bool b;
    
  p = *(cadre->pixmap());
  img = (p.convertToImage());
  Reconnaissance(&img);
  b = p.convertFromImage(img);
  cadre->setPixmap(p);
}

p_liste Mat::TrouverLignes(QImage *img)
{
  int i,j,s,d=0;
  QRgb noir = qRgb(0,0,0);
  p_liste p = NULL;
    
  p = Initialiser(p);
    
  for (j=0;(img->valid(0,j));j++)
    {
      s = 0;
      for (i=0;(img->valid(i,0));i++)
	{
	  if (img->pixel(i,j) == noir)
	    s += 1;
	}
      if ((s >= ((img->width())/2)) && ((j-d)>3))
	{
	  Ajouter(p,j);
	  d = j;
	}
    }
    p = p->p;
    
    return p;
}

void Mat::AfficherLignes(p_liste p, QImage *img)
{
  int i;
  QRgb rouge = qRgb(255,0,0);
    
  while (p)
    {
      for (i=0;img->valid(i,0);i++)
	img->setPixel(i,p->n,rouge);
      p = p->p;
    }
}

void Mat::BoutonLigne()
{
  QImage img;
  QPixmap *p;
  bool b;
      
  p = (cadre->pixmap());  
  img = (p->convertToImage());
  AfficherLignes(TrouverLignes(&img),&img);
  b = (p->convertFromImage(img));
  cadre->setPixmap(*p);
}

void Mat::Filtre2(QImage *img)
{
  int i,j,t,n;
  QRgb blanc = qRgb(255,255,255);
    
  n = 3;  
  t = 0;
    
  for (i=0;img->valid(i,0);i++)
    {
      t = 0;
      for (j=0;img->valid(0,j);j++)
	{
	  if ((img->pixel(i,j)) == blanc)
	    if (t<=n)
	      while(t)
		img->setPixel(i,(j - (t--)),blanc);
	    else
	      t = 0;
	  else
	    t++;
	}
    }
  
}

void Mat::BoutonFiltre()
{
  QImage img;
  QPixmap *p;
  bool b;
    
  p = (cadre->pixmap());
  img = (p->convertToImage()); 
  Filtre2(&img); 
  b = (p->convertFromImage(img)); 
  cadre->setPixmap(*p);
}

void Mat::slider1_valueChanged(int i)
{
  textLabel1->setText(QString::number(i,10));
}
