#include "morpho.h"

bool EgaleCouleur(QRgb r1, QRgb r2)
{
    return ((qBlue(r1) == qBlue(r2)) && (qGreen(r1) == qGreen(r2)) && (qRed(r1) == qRed(r2)));
}

bool Present(QImage *img, int x, int y, QRgb couleur)
{
    if 	(
	    EgaleCouleur(img->pixel(x+1,y+1),couleur) ||
	    EgaleCouleur(img->pixel(x+1,y),couleur) ||
	    EgaleCouleur(img->pixel(x+1,y-1),couleur) ||
	    EgaleCouleur(img->pixel(x,y+1),couleur) ||
	    EgaleCouleur(img->pixel(x,y-1),couleur) ||
	    EgaleCouleur(img->pixel(x-1,y+1),couleur) ||
	    EgaleCouleur(img->pixel(x-1,y),couleur) ||
	    EgaleCouleur(img->pixel(x-1,y-1),couleur) 
	    )
    {
	return (true);
    }
    else
    {
	return (false);
    }
}

void Eroder(QImage * img)
{
    QImage img_copie;
    int x,y;
    QRgb blanc = qRgb(255,255,255);
    
    img_copie = img->copy();
    
    for (x=1; img->valid(x+1,1);x++)
    {
	for (y=1; img->valid(1,y+1); y++)
	{
	    if (Present(&img_copie, x,y,blanc))
		img->setPixel(x,y,blanc);
	}
    }
}

void Dilater(QImage * img)
{
    QImage img_copie;
    int x,y;
    QRgb noir = qRgb(0,0,0);
    
    img_copie = img->copy();
    
    for (x=1; img->valid(x+1,1);x++)
    {
	for (y=1; img->valid(1,y+1); y++)
	{
	    if (Present(&img_copie, x,y,noir))
		img->setPixel(x,y,noir);
	}
    }
}

void Fermer(QImage * img)
{
  Dilater(img);
  Eroder(img);
}

void Ouvrir(QImage * img)
{
  Eroder(img);
  Dilater(img);
}

void Creuser (QImage *img)
{
    QImage img_copie;
  int i,j;
  QRgb blanc = qRgb(255,255,255);

  img_copie = img->copy();
  
  for (i=1; img_copie.valid(i+1,0); i++)
    {
      for (j=1; img_copie.valid(0,j+1); j++)
	{
	  if (!(Present(&img_copie,i,j,blanc)))
	  	img->setPixel(i,j,blanc);
	}
    }	      
}


int projection_horizontale(QImage * im, int j)
{
  int i=0,res=0,w= im->width();
  QRgb noir = qRgb(0,0,0);
  
  while(i<w)
    {
      if (im->pixel(i,j)== noir)
	res++;
      i++;
    }
  return res;
}

int projection_verticale(QImage * im, int i)
{

  int j=0,res=0,w= im->height();
  QRgb noir = qRgb(0,0,0);
  
  while(j<w)
    {
      if (im->pixel(i,j)== noir)
	res++;
      j++;
    }
  return res;
}


int projh(QImage * im)
{
  int j,h,res,tmp,pos;

  h = im->height();
  res = 0;
  pos = 0;
  j = 0;

  while(j<h)
    {
      tmp = projection_horizontale(im,j);
      if(tmp>res)
	{
	  res = tmp;
	  pos = j;
	}
      j++;
    }  
  return pos;
}


int projv(QImage * im)
{
  int i,w,res,tmp,pos;

  w = im->width();
  res = 0;
  pos = 0;
  i = 0;

  while(i<w)
    {
      tmp = projection_verticale(im,i);
      if(tmp>res)
	{
	  res = tmp;
	  pos = i;
	}
      i++;
    }  
  return pos;
}


t_rcle caracteristiques_cle(QImage * im)
{
  t_rcle res;
  int j=0,i=0,tmp;
  QImage tmp1,tmp2;

  res.largeur = im->width();
  res.hauteur = im->height();
  res.projh = projh(im);
  res.projv = projv(im);
  res.debutv=0;
  res.debuth=0;

  tmp1 = im->copy(); //pour ed (erosion puis dilatation)
  tmp2 = im->copy(); // pour eedd (erosion *2 puis dilatation*2)

  Eroder(&tmp1);
  Eroder(&tmp2);
  Eroder(&tmp2);
  Dilater(&tmp1);
  Dilater(&tmp2);
  Dilater(&tmp2);

  res.projhed = projh(&tmp1);
  res.projved = projv(&tmp1);
  res.projheedd = projh(&tmp2);
  res.projveedd = projv(&tmp2);

  while(j<res.hauteur)
    {
      tmp = projection_horizontale(im,j);
      if(tmp>2)
      {
	if(!res.debutv)
	  res.debutv = j;
	res.finv = j;
      }
      j++;
    }

  while(i<res.largeur)
    {
      tmp = projection_verticale(im,i);
      if(tmp>2)
      {
	if(!res.debuth)
	  res.debuth = i;
	res.finh = i;
      }
      i++;
    }

  return res;
}

void afficher_caracteristique_cle(t_rcle res)
{
  printf("\nlargeur = %i \t hauteur = %i\n",res.largeur,res.hauteur);
  printf("debutv = %i \t finv = %i\n",res.debutv,res.finv);
  printf("debuth = %i \t finh = %i\n",res.debuth,res.finh);
  printf("projh = %i \t projv = %i\n",res.projh,res.projv);  
  printf("projhed = %i \t projved = %i\n",res.projhed,res.projved);  
  printf("projheedd = %i \t projveedd = %i\n",res.projheedd,res.projveedd); 
  printf("-------------------------------------");
}

int reconnaissance_cle(QImage * im)
{
  t_rcle res;
  float v;

  res = caracteristiques_cle(im);
  v = (res.projved-res.debuth)*100/(res.finh-res.debuth) 
    - (res.projhed-res.debutv)*100/(res.finv-res.debutv);
  printf("\ncalcul des projections = %f ",v);
  //Rajouter ici les controles des tailles de la forme par rapport a l'espacement des lignes.

  if(v > 25)
    return 0;
  if(v<0 && -1*v < 20)
    return 1;
  if(v<0 && -1*v > 40)
    return 2;
  return 3;
}

void afficher_cle(QImage * im)
{
  printf("\n");
  switch(reconnaissance_cle(im))
    {  
    case 0 : printf("CLE DE FA\n");
      break;

    case 1 : printf("CLE DE SOL\n");
      break;

    case 2 : printf("CLE DE UT\n");
      break;

    case 3 : printf("CLE NON RECONNU ATTENTION\n");
      break;

    }
  
}
