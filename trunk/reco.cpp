#include "reco.h"

#include <qpushbutton.h>
#include <qimage.h>
#include <qpixmap.h>

Reco::Reco( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    setCaption("Reconnaissance");

    lblCadre = new QLabel(this, "lblCadre" );
    lblCadre->setGeometry( QRect( 40, 20, 570, 110 ) );
    lblCadre->setScaledContents( FALSE );

    btnCharger = new QPushButton( this, "btnCharger" );
    btnCharger->setGeometry( QRect( 30, 139, 60, 31 ) );

    btnFiltrer = new QPushButton( this, "btnFiltrer" );
    btnFiltrer->setGeometry( QRect( 90, 139, 60, 31 ) );

    btnFiltrer_bien = new QPushButton( this, "btnFiltrer_bien" );
    btnFiltrer_bien->setGeometry( QRect( 90, 139, 60, 31 ) );


    btnEroder = new QPushButton( this, "btnEroder" );
    btnEroder->setGeometry( QRect( 330, 140, 61, 31 ) );

    btnDelLignes = new QPushButton( this, "btnDelLignes" );
    btnDelLignes->setGeometry( QRect( 250, 140, 80, 31 ) );

    btnDilater = new QPushButton( this, "btnDilater" );
    btnDilater->setGeometry( QRect( 390, 140, 51, 31 ) );

    btnFindLignes = new QPushButton( this, "btnFindLignes" );
    btnFindLignes->setGeometry( QRect( 150, 140, 100, 31 ) );


    lblLignes = new QLabel( this, "lblLignes" );
    lblLignes->setGeometry( QRect( 60, 200, 241, 21 ) );

    btnCreuser = new QPushButton( this, "btnCreuser" );
    btnCreuser->setGeometry( QRect( 440, 139, 61, 31 ) );

    languageChange();
    resize( QSize(632, 295).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    btnCharger->move(10, 50);
    btnFiltrer->move(90, 50);
    btnFiltrer_bien->move(90, 80);
    btnEroder->move(170, 50);
    btnDelLignes->move(250, 50);
    btnDilater->move(330, 50);
    btnFindLignes->move(410, 50);
    lblLignes->move(490, 50);
    btnCreuser->move(570, 50);

    connect( btnCharger, SIGNAL( clicked() ), this, SLOT( btnCharger_clicked() ) );
    connect( btnFiltrer, SIGNAL( clicked() ), this, SLOT( btnFiltrer_clicked() ) );
    connect( btnFiltrer_bien, SIGNAL( clicked() ), this, SLOT( btnFiltrer_bien_clicked() ) );
    connect( btnDelLignes, SIGNAL( clicked() ), this, SLOT( btnDelLignes_clicked() ) );
    connect( btnEroder, SIGNAL( clicked() ), this, SLOT( btnEroder_clicked() ) );
    connect( btnDilater, SIGNAL( clicked() ), this, SLOT( btnDilater_clicked() ) );
    connect( btnFindLignes, SIGNAL( clicked() ), this, SLOT( btnFindLignes_clicked() ) );
    connect( btnCreuser, SIGNAL( clicked() ), this, SLOT( btnCreuser_clicked() ) );
}

Reco::~Reco()
{
  
}

void Reco::languageChange()
{
    btnCharger->setText( tr( "Charger" ) );
    btnFiltrer->setText( tr( "Filtrer" ) );
    btnFiltrer_bien->setText( tr( "Filtrer2" ) );
    btnEroder->setText( tr( "Eroder" ) );
    btnDelLignes->setText( tr( "Virer lignes" ) );
    btnDilater->setText( tr( "Dilater" ) );
    btnFindLignes->setText( tr( "Trouver lignes" ) );
    lblLignes->setText( QString::null );
    btnCreuser->setText( tr( "Creuser" ) );
}

void Reco::btnCharger_clicked()
{
   QPixmap pix;
    QImage img;
    QString s = QFileDialog::getOpenFileName(	/* On demande de charger quelle image */
                    ".",
                    "Images (*.png *.xpm *.jpg *.gif *.bmp)",
                    this,
                    "Reco"
                    "Choisi un fichier" );
    
    img.load(s); 			/*On charge l'image dans b à partir du string s*/
    
    pix.convertFromImage(img);
    
    lblCadre->setPixmap(pix);
    lblCadre->adjustSize();
}


void Reco::btnFiltrer_clicked()
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Filtre(&img,200);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}

void Reco::btnFiltrer_bien_clicked()
{
 QImage ima;
 
 QPixmap * img;
 QImage pix;
 float angle;
 int w,h;
 
 img = lblCadre->pixmap();
 pix = img->convertToImage();
      
  //*******************************************************************/  

  pix = filtrer_redim(pix);

  w = pix.width();
  h = pix.height();
  lblCadre->setGeometry(QRect(10,130,w,h ));
  pix = filtrer_grayscale(pix);
  pix = filtrer_seuillage(pix);

    angle = rotation_calcul_angle(pix);

  if (angle != 0.0)   
    ima = filtrer_rotation(pix,angle);
  else
    ima = pix;
  
  ima = filtrer_median(ima);
  lblCadre->setPixmap(ima);
  pix = ima; 
}


void Reco::btnDelLignes_clicked()
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    SupprimerLignes(&img,3);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}


void Reco::btnEroder_clicked()
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Eroder(&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}


void Reco::btnDilater_clicked()
{
        QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Dilater(&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}


void Reco::btnFindLignes_clicked()
{
    QString s;
    QPixmap *pix;
    QImage img;
    p_liste2 p;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    p = TrouverLignes(&img);
    AfficherLignes(p,&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
    
}


void Reco::btnCreuser_clicked()
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Creuser(&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}
