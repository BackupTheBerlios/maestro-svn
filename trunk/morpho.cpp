#include "morpho.h"


/*

fonction a faire is_blanche
continuer trouver_type_note
arranger verifie_point


*/


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

int reconnaissance_cle(QImage * im,int esp)
{
  t_rcle res;
  float v;


  Dilater(im);
  res = caracteristiques_cle(im);
  v = (res.projved-res.debuth)*100/(res.finh-res.debuth) 
    - (res.projhed-res.debutv)*100/(res.finv-res.debutv);
  printf("\ncalcul des projections = %f\n",v);
  //Rajouter ici les controles des tailles de la forme par rapport a l'espacement des lignes.

  printf("espacement_ligne= %i\n",esp);
  if ((res.largeur >= esp) && (res.largeur <= 3*esp))
    {
      if (v < 0 && -1*v > 40)
	return 4;
    }
  else
    if (res.largeur > 3*esp)
      {
	if(v > 25)
	  return 0; // cle de fa
	if((v<0 && -1*v < 20) || (v > 0 && v <= 25))
	  return 1; //cle de sol
	if(v<0 && -1*v > 40)
	  return 2; // cle de ut
      }
  
  return 3;
  
  
}

void afficher_cle(QImage * im,int esp)
{
  printf("\n");
  switch(reconnaissance_cle(im,esp))
    {  
    case 0 : printf("CLE DE FA\n");
      break;

    case 1 : printf("CLE DE SOL\n");
      break;

    case 2 : printf("CLE DE UT\n");
      break;

    case 3 : printf("CLE NON RECONNU ATTENTION\n");
      break;

    case 4 : printf("Bemol \n");
      break;

    }
  
}


/***************************************************/
/***      RECONNAISSANCE DES NOTES DE MUSIQUE    ***/
/***************************************************/

int largeur_noir(int x, int y, QImage * im , int esp) //donne la largeur de gauche a droite d'une bande noir;
{
  int res = 0;
  int x2 = x+1;
  QRgb noir = qRgb(0,0,0);
  while (im->valid(x2,y) && (im->pixel(x2,y) == noir) && (res < 3*esp))
    {
      x2++;
      res++;
    }
    x2 = x-1;
  while (im->valid(x2,y) && (im->pixel(x2,y) == noir) && (res < 3*esp))
    {
      x2--;
      res++;
      }
  return res;
}

int hauteur_noir(int x, int y, QImage * im, int esp)
{
  int res = 0;
  int y2 = y+1;
  QRgb noir = qRgb(0,0,0);
  while (im->valid(x,y2) && (im->pixel(x,y2) == noir) && (res < 3*esp))
    {
      y2++;
      res++;
    }
  y2 = y-1;
  while (im->valid(x,y2) && (im->pixel(x,y2) == noir) && (res < 3*esp))
    {
      y2--;
      res++;
      }
  return res;
}


void ajouter_plcord(p_lcord * p, int x, int y)
{
  while ((*p))
    p = &((*p)->suivant);

  if (!(*p))
    {
      (*p) = (p_lcord) (malloc(sizeof(s_lcord)));
      (*p)->x = x;
      (*p)->y = y;
      (*p)->suivant = NULL;
    }
}

void verifie_point( int esp, int x, int y, QImage * im, p_lcord * liste)
{
  int resx, resy, z, t;
  p_lcord l = (*liste);
  QRgb bleu=qRgb(0,0,255);
  z = largeur_noir (x,y+1, im,esp);
  t = hauteur_noir (x+1,y, im,esp);

  if (z > 3*esp/2) // largeur
    return;
  if (z < esp) // largeur
    return;
  if (t < 3*esp/4) //hauteur
    return;
  if (t > 3*esp/2) //hauteur
    return;


  z = largeur_noir (x,y-1, im,esp);
  t = hauteur_noir (x-1,y, im,esp);

  if (z > 3*esp/2) // largeur
    return;
  if (z < esp) // largeur
    return;
  if (t < 3*esp/4) //hauteur
    return;
  if (t > 3*esp/2) //hauteur
    return;


  z = largeur_noir (x,y, im,esp);
  t = hauteur_noir (x,y, im,esp);

  if (z > 3*esp/2) // largeur
    return;
  if (z < esp) // largeur
    return;
  if (t < 3*esp/4) //hauteur
    return;
  if (t > 3*esp/2) //hauteur
    return;


  resx = x ; //- int(z/2);
  resy = y ; //- int(t/2);

  // ajout dans la liste
  while (l)
    {
      if ((abs(resx - (l->x)) < 2*esp) && (abs(resy - (l->y)) < 2*esp))
	return;
      l = l->suivant;
    }
  ajouter_plcord(liste,resx,resy);
  printf("Croix detectee : x = %i \t y = %i\t h = %i \t l = %i\n",resx,resy,z,t);
    dessiner_croix(im,bleu,resx,resy);
}

p_lcord liste_noire (QImage * im, int esp, int larg )
{
  p_lcord liste = NULL;
  p_lcord liste2;
  int x = 0, y = 0;
  int h = im->height();
  int l = im->width();
  int i=0;
  QRgb noir = qRgb(0,0,0);
  QRgb rouge = qRgb(255,0,0);

  while( x < l )
    {
      y = 0;
      while( y < h )
	{
	  if (im->pixel(x,y) == noir)
	    verifie_point(esp,x,y,im,&liste);
	  y++;
	}
      x++;
    }

  if (liste==NULL)
  {
    for (i=1; i<=larg;i++) 
      Dilater(im);
  
  for (i=1; i<=larg;i++)
    Eroder(im);

  // on fait la verification que ca ne soit pas des notes blanches.
  x = 0;
  y = 0;
  while( x < l )
    {
      y = 0;
      while( y < h )
	{
	  if (im->pixel(x,y) == noir)
	    verifie_point(esp,x,y,im,&liste);
	  y++;
	}
      x++;
    }
  if (i && liste) // on a cherche desnotes blanches
	liste->type = blanche;

  }

  trouver_centre(im,&liste);
  trouver_type_note(liste,im,larg);
  

	
  liste2 = liste;
  while(liste2)
    {
      dessiner_croix(im,rouge,liste2->x,liste2->y);
      liste2 = liste2 -> suivant;
    }
  
  return liste;
}

void trouver_centre(QImage * im, p_lcord * liste) // trouve le centre d'une note
{
  int resx,resy;
  int tx, ty;
  int tmp1,tmp2;
  p_lcord l = *liste;
  QRgb blanc = qRgb(255,255,255);

  while(l)
    {
      tmp1 = 0;
      tmp2 = 0;
      tx = l->x;
      ty = l->y;
      while (im->valid(tx,ty) && (im->pixel(tx,ty) != blanc))
	{
	  tx++;
	  tmp1++;
	}
      tx = l->x;
      while (im->valid(tx,ty) && (im->pixel(tx,ty) != blanc))
	{
	  tx--;
	  tmp2++;
	}
      resx = l->x - tmp2 + int((tmp1+tmp2)/2);
      l->x = resx;
      tmp1 = 0;     tmp2 = 0;
      tx = l->x;    ty = l->y;
      while (im->valid(tx,ty) && (im->pixel(tx,ty) != blanc))
	{
	  ty++;
	  tmp1++;
	}
      ty = l->y;
      while (im->valid(tx,ty) && (im->pixel(tx,ty) != blanc))
	{
	  ty--;
	  tmp2++;
	}
      resy = l->y - tmp2 + int((tmp1+tmp2)/2);
      l->y = resy;      
      tmp1 = 0;
      tmp2 = 0;
      tx = l->x;
      ty = l->y;
      while (im->valid(tx,ty) && (im->pixel(tx,ty) != blanc))
	{
	  tx++;
	  tmp1++;
	}
      tx = l->x;
      while (im->valid(tx,ty) && (im->pixel(tx,ty) != blanc))
	{
	  tx--;
	  tmp2++;
	}
      resx = l->x - tmp2 + int((tmp1+tmp2)/2);
      l->x = resx;
        l = l->suivant;
    }
}

int is_blanche (p_lcord l, QImage * im)
{
// fonction a faire
return 0;
}

void trouver_type_note (p_lcord  l, QImage * im , int esp)
{
// fonction qui rempli le champ type qui di si c une blanche croche ...
int nb_note=0; // nb de notes dans la liste
p_lcord l2=l;
int i,j;
QRgb noir = qRgb(255,255,255);

while (l!= NULL)
{
  nb_note++;
  l = l-> suivant;
}
l=l2;
switch(nb_note)
{
  case 1 : {
  if (l->type == blanche)
  {
    l->type = blanche;
    printf("blanche \n");
  }
  else
  {
    i = l->x;
    j = l-> y;
    while (im->valid(i,j) && im->pixel(i,j) != noir)  // on va tout a droite et on verifie que c une croche ou pas
      i++;
    if ((im->width() - i) > im->width() / 10) // facteur a verifier
    {
      l->type = croche;
      printf("croche\n");
    }
    else
    {
      l->type = noire;
      printf("noire\n");
    }
  }
  }
   break;
   
  case 2 :{
  i = projection_verticale(im,int ((l->x + l->suivant->x)/2));
  if ((i>= 1.5*esp) && (i<= 4*esp))
  {
    l->type = croche;
    l->suivant->type = croche;
    printf("croche x 2\n");
  }
  
  if ((i>= 4.5*esp) && (i<= 6*esp))
  {
    l->type = dcroche;
    l->suivant->type = dcroche;
    printf("dcroche x 2\n");
  }  
   // case de 2 note detectee
   }
   break;
   
  case 3 :{
  i = projection_verticale(im,int ((l->x + l->suivant->x)/2));
  if ((i>= 1.5*esp) && (i<= 4*esp)) // 1 bare
  {
    l->type = croche;
    printf("croche\n");
  }
  
  if ((i>= 4.5*esp) && (i<= 6*esp)) // 2 barre
  {
    l->type = dcroche;
    printf("dcroche x 2\n");
  }    
  
  l2 = l->suivant;
  i = projection_verticale(im,int ((l2->x + l2->suivant->x)/2));

  
  if ((i>= 1.5*esp) && (i<= 4*esp)) // 1 barre
  {
    if (l->type = dcroche)
    {
    	l->suivant->type = dcroche;
	printf("dcroche\n");
    }
    else
    {
    	l->suivant->type = croche;
	printf("croche\n");
    }
	
    l2->suivant->type = croche;
    printf("croche\n");
  }
  
  if ((i>= 4.5*esp) && (i<= 6*esp)) //2 barre
  {
    if (l->type = croche)
    {
    	l->suivant->type = dcroche;
	printf("dcroche\n");
	}
    else
    {
    	l->suivant->type = croche;
	printf("croche\n");
	}
	
    l2->suivant->type = dcroche;
    printf("dcroche\n");
  }
   // case de 3 note detectee
   }
   break;
   
  case 4 :{
	l->type = dcroche;
	l = l->suivant;
	l->type = dcroche;
	l = l->suivant;
	l->type = dcroche;
	l = l->suivant;
	l->type = dcroche;
	printf("dcroche x 4\n");
   // case de 4 note detectee
   }
   break; 
}

}


void dessiner_croix(QImage * im, QRgb coul, int x, int y) // dessiner les croix placant les notes.
{
  int x2=x, y2=y;
  int l = 3; //longueur de la croix
  while((im->valid(x2,y2)) && ((x2-x) < l))
    {
      im->setPixel(x2,y2,coul);
      x2++;
    }
  x2 = x;
  while((im->valid(x2,y2)) && ((x-x2) < l))
    {
      im->setPixel(x2,y2,coul);
      x2--;
    }
  x2 = x;
  while((im->valid(x2,y2)) && ((y2-y) < l))
    {
      im->setPixel(x2,y2,coul);
      y2++;
    }
  y2 = y;
  while((im->valid(x2,y2)) && ((y-y2) < l))
    {
      im->setPixel(x2,y2,coul);
      y2--;
    }
  y2 = y;
}
