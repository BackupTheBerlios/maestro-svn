#include <qvariant.h>
#include <qbuttongroup.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qimage.h>
#include <qpixmap.h>

#include"romain.h"


Romain::Romain(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  resize(200, 200);
  setCaption("Romain");
}

Romain::~Romain()
{

}

void Fenetre::Charger()
{
    QPixmap p;
    bool b;
    
    QString s = QFileDialog::getOpenFileName(
                    "~",
                    "Images (*.png *.xpm *.jpg *.gif *.bmp)",
                    this,
                    "Romain"
                    "Choisi un fichier" );
    
    b = img.load(s); 
    b = img_d.load(s);
    
    b = p.convertFromImage(img);
   

    cadre->setAutoResize(true);
    cadre->setPixmap(p);
}


void Fenetre::FiltrerImage(QImage *img_s, QImage *img_d, float a, float b, float c, float d, float e, float f, float g, float h, float z )
{
    int x, y, i, j;
    float res_r, res_g, res_b;
    QRgb rgb;
    
    /* Définition du filtre */
    
   /*float filtre[3][3] = {{1.0,2.0,1.0},
		  {2.0,4.0,2.0},
		  {1.0,2.0,1.0}};*/
    
    float filtre[3][3] = {{a,b,c},
		  {d,e,f},
		  {g,h,z}};
    
   /* float filtre_div = 16.0;  */
    
    float filtre_div = a+b+c+d+e+f+g+h+z;
    if (filtre_div == 0)
	filtre_div = 1;
			  
    /* Début de l'algo */
 
    for (y=1;(img_s->valid(0,y))/*valid(i,1)*/;y++)
    {
	for(x=1;(img_s->valid(x,0))/*valid(1,j)*/;x++)
	{
	    res_r = 0;
	    res_g = 0;
	    res_b = 0;
	  
	     for(j=0;j<3;j++)
	    {
		for(i=0;i<3;i++)
		{
		    rgb = img_s->pixel(x-1+i, y-1+j);
		    res_r += ((float)qRed(rgb) * filtre[j][i]);
		    res_g += ((float)qGreen(rgb) * filtre[j][i]);
		    res_b += ((float)qBlue(rgb) * filtre[j][i]);
		}
	    }
	
	    res_r /= filtre_div;
	    res_g /= filtre_div;
	    res_b /= filtre_div;
	    
	    /* Saturation du résultat */
	    
	    res_r = (res_r > 255.0)? 255.0 : ((res_r < 0.0)? 0.0 : res_r);
	    res_g = (res_g > 255.0)? 255.0 : ((res_g < 0.0)? 0.0 : res_g);
	    res_b = (res_b > 255.0)? 255.0 : ((res_b < 0.0)? 0.0 : res_b);
	    
	    /* On remplace les valeurs du pixel en position (i,j) */
	    
	    rgb = qRgb((uint)res_r, (uint)res_g, (uint)res_b);
	    img_d->setPixel(x+1, y+1, rgb);
	}
    } 
}


void Romain::Filtrer()
{
    bool r;
    QPixmap p;
    float a,b,c,d,e,f,g,h,i;
    
    p = *(cadre->pixmap());
    
    img = p.convertToImage();
    
    if (gaussien->isChecked())
    {a = 1.0;
	b = 2.0;
	c = 1.0;
	d = 2.0;
	e = 4.0;
	f = 2.0;
	g = 1.0;
	h = 2.0;
	i = 1.0;
	FiltrerImage(&img, &img_d, a,b,c,d,e,f,g,h,i);
    };   
    
    if (laplacien->isChecked())
    {a = -1.0;
	b = -1.0;
	c = -1.0;
	d = -1.0;
	e = 8.0;
	f = -1.0;
	g = -1.0;
	h = -1.0;
	i = -1.0;
	FiltrerImage(&img, &img_d, a,b,c,d,e,f,g,h,i);
    };   
    
    if (passeh->isChecked())
    {a = 0.0;
	b = -1.0;
	c = 0.0;
	d = -1.0;
	e = 5.0;
	f = -1.0;
	g = 0.0;
	h = -1.0;
	i = 0.0;
	FiltrerImage(&img, &img_d, a,b,c,d,e,f,g,h,i);
    };   
    
    if (niveaux->isChecked())
	FiltreGris(&img_d);
    
    if (noir->isChecked())
    {
	FiltreGris(&img_d);
	FiltreNoir(&img_d);
    };
    
    if (selectif->isChecked())
	FiltreSelectif(&img, &img_d);
    
    if (median->isChecked())
	FiltreMedian(&img, &img_d);
    
    r = p.convertFromImage(img_d);
    cadre->setAutoResize(true);
    cadre->setPixmap(p);
}


void Romain::FiltreGris( QImage *img )
{
    int x, y;
    int res_r, res_g, res_b, filtre_div;
    QRgb rgb;
    

    filtre_div = 3;
			  
    /* Début de l'algo */
 
    for (y=0;(img->valid(0,y));y++)
    {
	for(x=0;(img->valid(x,0));x++)
	{
	    /*s = 0;
	    res_g = 0;
	    res_b = 0;*/
	    rgb = img->pixel(x, y);
	    res_r = qRed(rgb) + qGreen(rgb) + qBlue(rgb);
	    res_g = res_b = res_r;
	
	    res_r /= 3;
	    res_g = res_b = res_r;
	    
	    /* Saturation du résultat */
	    
	    res_r = (res_r > 255)? 255 : ((res_r < 0)? 0 : res_r);
	    res_g = res_b = res_r;
	    
	    /* On remplace les valeurs du pixel en position (x,y) */
	    
	    rgb = qRgb((uint)res_r, (uint)res_g, (uint)res_b);
	    img->setPixel(x, y, rgb);
	}
    }    
}


void Romain::FiltreNoir( QImage *img )
{
    int i, j;
    QRgb rgb;
     for (i=0;img->valid(i,0);i++)
    {
	for(j=0;img->valid(0,j);j++)
	{
	    rgb = img->pixel(i,j);
	    if (qGray(rgb) >= 75)
		rgb = qRgb(255,255,255);
	    else
		rgb = qRgb(0,0,0);
	    
	    img->setPixel(i,j,rgb);
	}
    }
    
}


void Romain::FiltreSelectif( QImage *img_s, QImage *img_d )
{
  int vx,vy;
  int i,j;
  float res_r, res_g, res_b;
  QRgb vpix,cpix, rgb;
  /* definition di filtre utilise (en forme de cloche => gaussien) */
  float filter_red  [3][3];
  float filter_green[3][3];
  float filter_blue [3][3];
  float filter_red_sum, filter_green_sum, filter_blue_sum;

  for(vy = 0;(img_s->valid(0,vy)); vy++)
  {
    for(vx = 0;(img_s->valid(vx,0)); vx++)
    {
      filter_red_sum = filter_green_sum = filter_blue_sum = 0.0;
      /* recupere le point que l'on traite */
      cpix = img_s->pixel(vx, vy);
      /* fabrique la matrice de convolution en fonction des variations */
      /* de l'intensité (fabrique le filtre local)                     */
      for(j=0;j<3;j++)
        for(i=0;i<3;i++)
        {
          if((j == 1) && (i == 1))
          {
            filter_red  [1][1] = 0.5;
            filter_green[1][1] = 0.5;
            filter_blue [1][1] = 0.5;
          } else {
            vpix = img_s->pixel(vx-(3>>1)+i, vy-(3>>1)+j);
                  
            res_r = ((float)qRed(cpix)) - ((float)qRed(vpix));
            if(res_r < 0.0) res_r = -res_r;
            if(res_r != 0)
              filter_red  [j][i] = 1.0/res_r;
            else
              filter_red  [j][i] = 1.0;
            
            res_g = ((float)qGreen(cpix)) - ((float)qGreen(vpix));
            if(res_g < 0.0) res_g = -res_g;
            if(res_g != 0)
              filter_green[j][i] = 1.0/res_g;
            else
              filter_green[j][i] = 1.0;
            
            res_b = ((float)qBlue(cpix)) - ((float)qBlue(vpix));
            if(res_b < 0.0) res_b = -res_b;
            if(res_b != 0)
              filter_blue [j][i] = 1.0/res_b;
            else
              filter_blue [j][i] = 1.0;
          }
          filter_red_sum   += filter_red  [j][i];
          filter_green_sum += filter_green[j][i];
          filter_blue_sum  += filter_blue [j][i];
        }
      for(j=0;j<3;j++)
        for(i=0;i<3;i++)
        {
          if(filter_red_sum != 0.0)
            filter_red  [j][i] /= filter_red_sum;
          if(filter_green_sum != 0.0)
            filter_green[j][i] /= filter_green_sum;
          if(filter_blue_sum != 0.0)
            filter_blue [j][i] /= filter_blue_sum;
        }
      /* on applique le filtre calculé */
      res_r = 0.0;
      res_g = 0.0;
      res_b = 0.0;
      for(j=0;j<3;j++)
        for(i=0;i<3;i++)
        {
          vpix = img_s->pixel(vx-(3>>1)+i, vy-(3>>1)+j);
          res_r += (float)qRed(vpix) * filter_red  [j][i];
          res_g += (float)qGreen(vpix) * filter_green[j][i];
          res_b += (float)qBlue(vpix) * filter_blue [j][i];
        }

      /* on sature le résultat */
      res_r = (res_r > 255.0)? 255.0 : ((res_r < 0.0)? 0.0:res_r);
      res_g = (res_g > 255.0)? 255.0 : ((res_g < 0.0)? 0.0:res_g);
      res_b = (res_b > 255.0)? 255.0 : ((res_b < 0.0)? 0.0:res_b);

      /* on place le résultat dans l'image destination */      
      
      rgb = qRgb((uint)res_r, (uint)res_g, (uint)res_b);
      img_d->setPixel(vx, vy, rgb);
    }
  }
}


void Romain::FiltreMedian( QImage *img_s, QImage *img_d )
{  
  int x, y, i, j;
  int res_r, res_b, res_g;
  QRgb rgb;
  QRgb rgb_tab[9];
  float lum_tab[9];
  float lum_swap;
  QRgb rgb_swap;
  int pos;

  /* Début de l'algo */

  for (y = 0;(img_s->valid(0,y)); y++)
  {
      for (x = 0; (img_s->valid(x,0)); x++)
      {
	/*rgb = img_s->pixel(x, y);
	res_r = qRed(rgb) + qGreen(rgb) + qBlue(rgb);
	res_g = res_b = res_r;
	
	res_r /= 3;
	res_g = res_b = res_r;
	
	
	
	res_r = (res_r > 255)? 255 : ((res_r < 0)? 0 : res_r);
	res_g = res_b = res_r;
	
	
	
	rgb = qRgb((uint)res_r, (uint)res_g, (uint)res_b);
	img_s->setPixel(x, y, rgb);*/
	
	pos = 0;
	for (j=0;j<3;j++)
 
	    for (i=0;i<3;i++)
	    {
	    rgb =  img_s->pixel(x-(3>>1)+i, y-(3>>1)+j);
          
	    rgb_tab[pos] = rgb;
	  
	    /* on calcule la luminance */
	  
	    lum_tab[pos] = 0.299*(float)qRed(rgb) +
			   0.587*(float)qGreen(rgb) +
			   0.114*(float)qBlue(rgb);
	    pos++;
	}
	
	/* on tri le tableau des pixels en fonction de la luminance */
	
	for (j=0;j<8;j++)
	{
	    pos = j;
	    for (i=j+1;i<9;i++)
	    {
		if (lum_tab[i] < lum_tab[pos])
		    pos = i;
	    }
	    lum_swap = lum_tab[j];
	    rgb_swap = rgb_tab[j];
	    lum_tab[j] = lum_tab[pos];
	    rgb_tab[j] = rgb_tab[pos];
	    lum_tab[pos] = lum_swap;
	    rgb_tab[pos] = rgb_swap;
	}
	
	/* on place le point avec l'intensité moyenne dans l'image destination */
	
	rgb = qRgb(qRed(rgb_tab[4]),
		   qGreen(rgb_tab[4]),
		   qBlue(rgb_tab[4]));
	img_d->setPixel(x, y, rgb);
    }
  }
}
