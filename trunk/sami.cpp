#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include"sami_list.h"

#include"sami.h"



Sami::Sami(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  resize(800, 600);
  setCaption("Sami");
  NBelt_listd = 0;

  pmap = new QLabel(this);

  QuitBut = new QPushButton(this, "QuitBut");
  QuitBut->setText("Quit");
  QuitBut->move(10, 80);

  AffBut =  new QPushButton(this, "AffBut");
  AffBut->setText("Afficher");
  AffBut->move(10,110);

  RotBut = new QPushButton(this, "RotBut");
  RotBut->setText("Filtrer");
  RotBut->move(10, 140);

  SavBut = new QPushButton(this, "SavBut");
  SavBut->setText("Sauvegarder");
  SavBut->move(10, 170);


  connect(QuitBut, SIGNAL(clicked()), this, SLOT(close()));
  connect(AffBut, SIGNAL(clicked()), this, SLOT(affichage()));
  connect(RotBut, SIGNAL(clicked()), this, SLOT(rotation()));
  connect(SavBut, SIGNAL(clicked()), this, SLOT(sauvegarder()));

}

Sami::~Sami()
{

}



void Sami::affichage() //connection pour le bouton afficher
{
  int w,h;
  //  pix = QImage::QImage(FilePath); //on charge l'image en memoire
  
    w = pix.width();
    h = pix.height();    

    pmap->setGeometry(QRect(120,40,w,h ));

     pmap->setPixmap(pix);  
}




QImage Sami::filtrer_grayscale(QImage pix) // Mise au niveau de gris connection pour le bouton filtre
{
  QRgb rgb;    
  int i,j,k; // i et j pour parcourir l'image  *****   k : coefficiant du grayscale
  
  i = 0;
  while ( i < pix.width() )
    {
      j = 0 ;
      while ( j < pix.height() )
	{  
	  k = qGray( pix.pixel(i,j) );
	  rgb = qRgb (k,k,k);
	  pix.setPixel(i,j, rgb);
	  j++;
	} 
      i++;
    }    
  //pmap->setPixmap(pix);   // Mise a jour de l'image pmap 
  return pix;
}



QImage Sami::filtrer_rotation( QImage im1, float angle ) //fais la rotation et renvoie l'image rotatee
{
  QImage im2;
  QRgb p; // Le utilise pour les calculs
  int cx, cy; // Centre de l'image
  double r; // Radian de l'image
  double a; // Angle pour centrer l'image
  int ix, iy; // Pour le parcours de l'image 1
  //  int i2x, i2y; // Pour le parcours de l'image 2
  int x,y; // Distance entre le centre et le point de parcours image1
  int x2,y2; // Distance entre le centre et le point de parcours image2
  
  im2 = im1.copy() ; //on prepare la deuxieme image
  image_vider(im2);  
  
  cx = (int)  ( im1.width() / 2) ;
  cy = (int)  (im1.height() / 2) ;

  
  ix = 0;
  while (ix < im1.width() )
    {
      iy = 0;
      while(iy < im1.height() )
	{
	  x = ix - cx;
	  y = iy - cy;
   
	  if(x)
	    a = atan2( y , x );   //on utilise atan2 pke atan fou la merde
	  else
	    //   if (y >= 0)
	    a = M_PI / 2;
	  /*     else
		 a = -1*M_PI / 2;*/
   
	  r = sqrt(1*x*x + 1*y*y);
   
	  x2 = arrondi( (r*cos(a + angle*M_PI/180)) );
	  y2 = arrondi( (r*sin(a + angle*M_PI/180)) );
   
	  /*   printf("[ix = %i iy = %i a = %f x2 = %i y2 = %i r = %f v = %i]\n",ix, iy, a,x2,y2,r,im2.valid(cx + x2, cy - y2));*/
	  if (im2.valid(cx + x2, cy + y2))
	    {
	      p = im1.pixel(ix, iy) ;
	      im2.setPixel(cx + x2, cy + y2, p);
	    }
	  iy++;
	}
      ix++;
    }
  /* printf("[xwidth = %i yheight = %i ; cx = %i cy = %i  angle = %f ]\n", im1.width(), im1.height(), cx, cy,angle);*/
  //pix = im2; 
  //pmap->setPixmap(im2);
  return im2;
}


void Sami::image_vider(QImage pix)
{
  int x,y;
  QRgb rgb;
  x = 0;
  rgb = qRgb (255,255,255);
  while (x < pix.width())
    {
      y = 0;
      while(y < pix.height() )
	{
	  pix.setPixel(x,y, rgb);
	  y++;
	}
      x++;
    }
  
}


int Sami::arrondi(double a)
{
  double tmp;
  tmp = (a / (int)(a) ) *10;
  if (tmp >= 5)
    return((int)(a)+1);
  else
    return((int)(a));
}



QImage Sami::filtrer_median( QImage im1 )
{
  QImage im2 = im1.copy();
  listd p=NULL;
  int x=1, y=1;
  im1 = filtrer_seuillage(im1);
  
  image_vider(im2);    
  while(x < (im1.width() -1) )
    {
      y = 1;
      while ( y < (im1.height()-1))
	{
	  vider_listd(p, &NBelt_listd);
	  p = NULL;
	  p = ajouter_listed(qBlue(im1.pixel(x-1,y-1)),p, &NBelt_listd);
	  p = ajouter_listed(qBlue(im1.pixel(x,y-1))  ,p, &NBelt_listd);
	  p = ajouter_listed(qBlue(im1.pixel(x+1,y-1)),p, &NBelt_listd);
	  p = ajouter_listed(qBlue(im1.pixel(x-1,y))  ,p, &NBelt_listd);
	  p = ajouter_listed(qBlue(im1.pixel(x+1,y))  ,p, &NBelt_listd);
	  p = ajouter_listed(qBlue(im1.pixel(x-1,y+1)),p, &NBelt_listd);
	  p = ajouter_listed(qBlue(im1.pixel(x,y+1))  ,p, &NBelt_listd);   
	  p = ajouter_listed(qBlue(im1.pixel(x+1,y+1)),p, &NBelt_listd);   
	  tri_listd(p);
	  //afficher_listd(p);
	  im2.setPixel(x,y,median_listd(p, &NBelt_listd));
	  y++;
	}
      x++;
    }
  vider_listd(p, &NBelt_listd);
  
  return(im2);
}


QImage Sami::filtrer_seuillage( QImage im1 )
{
  int x=0,y=0;
  while (x<im1.width())
    {
      y=0;
      while(y<im1.height())
	{
	  if (qBlue(qGray(im1.pixel(x,y))) < 155)
	    im1.setPixel(x,y,qRgb(0,0,0));
	  else
	    im1.setPixel(x,y,qRgb(255,255,255));
	  y++;
	}
      x++;
    }
  return im1;    
}

QImage filtrer_redime(QImage pix) // fonction de redimmensionnement de l'image
{
  QImage im;
  int w,h;
 
    w = pix.width();
    h = pix.height();
    
    if(w > 1700)
      {
       pix = pix.scaleHeight(1700*h/w);
       pix = pix.scaleWidth(1700);
       
      }
    if(h > 2000)
      {
	pix = pix.scaleWidth( (int) 2000*w/h);
	pix = pix.scaleHeight(2000);
      }
    
    w = pix.width();
    h = pix.height();  
    printf("Redimmensionnement de l'image au format %i x %i\n",w,h);
    im = pix.smoothScale(w, h);
    //   pix = im;
  return im;
}



void Sami::sauvegarder() //connection pour le boutton sauvegarder
{
  pix.save("sauvegarde.png", "PNG");    
}



int Sami::rotation_proj( QImage im, int j ) //Fais la projection de j sur l'axe Oy
{
  int i = 0, res = 0;
  while (i < im.width() )
    {
      if(qBlue(qGray(im.pixel(i,j)) == 0))
	res ++;
      i++;
    }
  return res;
}


int Sami::filtrer_rot_calcul_proj(QImage pix) // fais le calcul de la projection sur l'axe oy 
{
  int i = 0, res;
  int debut=0,tmp=0;
  
  while( i <  pix.height() )
    {
      res =  rotation_proj(pix,i);
      if(res > 7)
	{
	  if(!debut && !tmp)
	    debut = i;
	  tmp = i;
	  // printf("Projection sur %i = %i\n",i, res );
	}
      i++;
    }
  /* printf("Projection axiale = %i\n",tmp-debut);*/
  return (tmp-debut);
}



float Sami::rotation_calcul_angle(QImage pix) //fais le calcul de l'angle de rotation
{ 
  float angle=-0.01;
  float angl1,angl2;
  int res=0;
  float pitch = -0.08;
  QImage ima;
    
  res = filtrer_rot_calcul_proj(pix);
  ima = filtrer_rotation(pix,angle);
  while(filtrer_rot_calcul_proj(ima) <= res )
    {
      if(filtrer_rot_calcul_proj(ima) < res)
	res = filtrer_rot_calcul_proj(ima); 
      angle = angle +pitch; 
      ima = filtrer_rotation(pix,angle);
    }
  angl1 = angle-pitch;
    
  angle = 0.01;
  pitch =-1*pitch;
  res = filtrer_rot_calcul_proj(pix);
  ima = filtrer_rotation(pix,angle);
  while(filtrer_rot_calcul_proj(ima) <= res )
    {
      if(filtrer_rot_calcul_proj(ima) < res)
	res = filtrer_rot_calcul_proj(ima); 
      angle = angle +pitch; 
      ima = filtrer_rotation(pix,angle);
    }    
  angl2 = angle - pitch;
  printf("Angle1 = %f - Angle2 = %f \n",angl1,angl2);
    
  if( (angl1!= 0.01) && (angl2!= -0.01) )
    if((angl2)>(-1*angl1))
      angle = angl1;
    else
      {
      if (angl1 != -1*angl2)
	angle = angl2;
      else
	angle = angl1/2;
      }
  else
    {
      if(angl1==-0.01)
	{
	  if(angl2==0.01)
	    {
	      angle = 0;
	    }
	  else
	    {
	      angle = angl2;
	    }
	}
      else
	{
	  angle = angl1;
	}
    }
  printf("meilleur angle = %f pour projection = %i\n",angle,filtrer_rot_calcul_proj(filtrer_rotation(pix,angle)) );
  return (angle);
}



void Sami::rotation() // connection Pour le boutton proj
{
  QImage ima;
  float angle;
  int w,h;
  

  pix = filtrer_redime(pix);

  w = pix.width();
  h = pix.height();
  pmap->setGeometry(QRect(120,40,w,h ));
  pix = filtrer_grayscale(pix);
  pix = filtrer_seuillage(pix);

    angle = rotation_calcul_angle(pix);

  if (angle != 0.0)   
    ima = filtrer_rotation(pix,angle);
  else
    ima = pix;
  
  ima = filtrer_median(ima);
  pmap->setPixmap(ima);
  pix = ima; 
}
