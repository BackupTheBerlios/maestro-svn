#include<stdio.h>
#include"detect.h"
#include"fenetre.h"
#include"lignes.h"
#include"mat_list.h"


Detection::Detection(QWidget *parent, const char *name)
  : QMainWindow(parent, name)
{
  resize(200, 200);
  setCaption("Detection");

  DectLignes = new QPushButton(this, "DectLignes");

  DectLignes->setText("Chercher");

  DectLignes->move(10, 30);

  connect(DectLignes, SIGNAL(clicked()), this, SLOT(DetectLignes()));
}

Detection::~Detection()
{

}

void Detection::DetectLignes()
{
  p_liste2 liste;

  liste = TrouverLignes(&pix);
  if (liste == NULL)
    DectLignes->setText("Echec");
  else
    DectLignes->setText("Succes");
  while (liste != NULL)
    {
      printf("%i est une ligne de %i\n", liste->ord, liste->larg);
      liste = liste->next;
    }
}
