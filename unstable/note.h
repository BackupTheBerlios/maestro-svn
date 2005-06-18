#ifndef NOTE_H
#define NOTE_H

enum t_type {ronde, blanche, noire, croche, dcroche, tcroche, qcroche};

enum t_cle {sol, ut, fa};

union cle_note
{
  t_type note;
  t_cle cle;
} ;

typedef struct t_note
{
  cle_note type;
  int niveau;
} t_note;

typedef struct t_list_note * p_list_note;

typedef struct t_list_note
{
  bool cle;
  t_note info;
  p_list_note p;
} t_list_note;

#endif