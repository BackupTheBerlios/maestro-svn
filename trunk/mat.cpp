#include "mat.h"

#include <qpushbutton.h>
#include <qimage.h>
#include <qpixmap.h>

Mat::Mat( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    (void)statusBar();
    if ( !name )
	setName( "Fenetre" );
    setCentralWidget( new QWidget( this, "qt_central_widget" ) );

    lblCadre = new QLabel( centralWidget(), "lblCadre" );
    lblCadre->setGeometry( QRect( 40, 20, 570, 110 ) );
    lblCadre->setScaledContents( FALSE );

    btnCharger = new QPushButton( centralWidget(), "btnCharger" );
    btnCharger->setGeometry( QRect( 30, 139, 60, 31 ) );

    btnFiltrer = new QPushButton( centralWidget(), "btnFiltrer" );
    btnFiltrer->setGeometry( QRect( 90, 139, 60, 31 ) );

    btnEroder = new QPushButton( centralWidget(), "btnEroder" );
    btnEroder->setGeometry( QRect( 330, 140, 61, 31 ) );

    btnDelLignes = new QPushButton( centralWidget(), "btnDelLignes" );
    btnDelLignes->setGeometry( QRect( 250, 140, 80, 31 ) );

    btnDilater = new QPushButton( centralWidget(), "btnDilater" );
    btnDilater->setGeometry( QRect( 390, 140, 51, 31 ) );

    btnFindLignes = new QPushButton( centralWidget(), "btnFindLignes" );
    btnFindLignes->setGeometry( QRect( 150, 140, 100, 31 ) );


    lblLignes = new QLabel( centralWidget(), "lblLignes" );
    lblLignes->setGeometry( QRect( 60, 200, 241, 21 ) );

    btnCreuser = new QPushButton( centralWidget(), "btnCreuser" );
    btnCreuser->setGeometry( QRect( 440, 139, 61, 31 ) );

    languageChange();
    resize( QSize(632, 295).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    connect( btnCharger, SIGNAL( clicked() ), this, SLOT( btnCharger_clicked() ) );
    connect( btnFiltrer, SIGNAL( clicked() ), this, SLOT( btnFiltrer_clicked() ) );
    connect( btnDelLignes, SIGNAL( clicked() ), this, SLOT( btnDelLignes_clicked() ) );
    connect( btnEroder, SIGNAL( clicked() ), this, SLOT( btnEroder_clicked() ) );
    connect( btnDilater, SIGNAL( clicked() ), this, SLOT( btnDilater_clicked() ) );
    connect( btnFindLignes, SIGNAL( clicked() ), this, SLOT( btnFindLignes_clicked() ) );
    connect( btnCreuser, SIGNAL( clicked() ), this, SLOT( btnCreuser_clicked() ) );
}

Mat::~Mat()
{
  
}

void Mat::languageChange()
{
    setCaption( tr( "Soutenance 2" ) );
    btnCharger->setText( tr( "Charger" ) );
    btnFiltrer->setText( tr( "Filtrer" ) );
    btnEroder->setText( tr( "Eroder" ) );
    btnDelLignes->setText( tr( "Virer lignes" ) );
    btnDilater->setText( tr( "Dilater" ) );
    btnFindLignes->setText( tr( "Trouver lignes" ) );
    lblLignes->setText( QString::null );
    btnCreuser->setText( tr( "Creuser" ) );
}

void Mat::btnCharger_clicked()
{
    QPixmap pix;
    QImage img;
    QString s = QFileDialog::getOpenFileName(	/* On demande de charger quelle image */
                    ".",
                    "Images (*.png *.xpm *.jpg *.gif *.bmp)",
                    this,
                    "Mat"
                    "Choisi un fichier" );
    
    img.load(s); 			/*On charge l'image dans b � partir du string s*/
    
    pix.convertFromImage(img);
    
    lblCadre->setPixmap(pix);
    lblCadre->adjustSize();
}


void Mat::btnFiltrer_clicked()
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Filtre(&img,200);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}


void Mat::btnDelLignes_clicked()
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    SupprimerLignes(&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}


void Mat::btnEroder_clicked()
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Eroder(&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}


void Mat::btnDilater_clicked()
{
        QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Dilater(&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}


void Mat::btnFindLignes_clicked()
{
    QString s;
    QPixmap *pix;
    QImage img;
    p_liste p;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    p = TrouverLignes(&img);
    AfficherLignes(p,&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
    
}


void Mat::btnCreuser_clicked()
{
    QPixmap *pix;
    QImage img;
    
    pix = lblCadre->pixmap();
    img = pix->convertToImage();
    Creuser(&img);
    pix->convertFromImage(img);
    lblCadre->setPixmap(*pix);
}
