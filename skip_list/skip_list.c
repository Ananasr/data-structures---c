/**
 * \file skip_list.c
 * \brief Fichier source
 * \author Hedi Nasr
 * \version 0.2
 * \date 19 d�cembre 2016
 *
 * Fichier source contenant les d�finitions et les prototypes des fonctions et
 * proc�dures manipulant le type SkipList.
 */
#include "skip_list.h"
#include <stdio.h>
#include <stdlib.h>

/*
  Pr�condition(s): *l non pr�alablement initialis�e
  Post-condition(s): la liste *l initialis�e est vide
*/
void init(SkipList *list, ObjectPack pack) {
  Cellule *dummy = (Cellule *)malloc(sizeof(Cellule));

  list->pack = pack;
  list->dummy = dummy;
  list->size = list->level = 0;

  dummy->suivant = dummy->dessous = NULL;
}

/*
  Pr�condition(s): l pr�alablement initialis�e et manipul�e uniquement
  � travers les op�rations du module.

  R�sultat: retourne 1 si l est vide, 0 sinon.
*/
int empty(const SkipList *list) {
  if (list->size == 0)
    return 1;
  return 0;
}

static void _deleteLine(Cellule *dummy, SkipList *list) {
  // Tant qu'il reste un �l�ment dans la ligne
  while (dummy->suivant != NULL) {
    Cellule *foo = dummy->suivant;
    dummy->suivant = foo->suivant;
    if (foo->dessous == NULL) {
      list->size--;
      list->pack.testament(&(foo->data));
    }
    free(foo);
  }
}

static void _clear(SkipList *list) {
  while (list->dummy != NULL) {
    // On descend d'un niveau
    Cellule *foo = list->dummy;
    list->dummy = foo->dessous;
    // et on supprime la ligne du dessus.
    _deleteLine(foo, list);
    free(foo);
    list->level--;
  }
}

/*
  Pr�condition(s): *l pr�alablement initialis�e et manipul�e uniquement
  � travers les op�rations du module.

  Post-condition(s): *l pr�te � �tre d�truite
*/
void clear(SkipList *list) { _clear(list); }

/*
  R�sultat: retourne l'adresse de l'�l�ment ins�r�.
*/
static Cellule *insertElemInterne(Object e, Cellule *bidon, const SkipList *l) {
  if (bidon->suivant && l->pack.compare(e, bidon->suivant->data) >= 0) {
    // Va � droite
    return insertElemInterne(e, bidon->suivant, l);
  } else {
    /* Dernier niveau ? */
    if (bidon->dessous == NULL) {
      Cellule *p = (Cellule *)malloc(sizeof(Cellule));
      /* Chainage sur le dernier niveau ("en t�te") */
      p->data = e;
      p->suivant = bidon->suivant;
      bidon->suivant = p;
      p->dessous = NULL;
      return p;
    } else {
      /* Va en bas */
      Cellule *a = insertElemInterne(e, bidon->dessous, l);
      if (a && rand() % 2 == 0) {
        Cellule *c = (Cellule *)malloc(sizeof(Cellule));
        c->data = a->data;
        c->dessous = a;
        c->suivant = bidon->suivant;
        bidon->suivant = c;
        return c;
      } else {
        return NULL;
      }
    }
  }
}

/*
  Precondition : *l et e initialises et manipules uniquement a travers les
  operations de leurs modules respectifs)

  Postcondition : Rajoute des niveaux en fonction du pile ou face
*/
void push_back(SkipList *l, Object e) {
  Object b;
  Cellule *p, *c;
  l->pack.init(&b, e); /* Initialise l'élément */
  c = insertElemInterne(b, l->dummy, l);
  l->size++;
  while (c && rand() % 2 == 0) /* Pile ou face */
  {
    Cellule *bidon = (Cellule *)malloc(sizeof(Cellule));
    bidon->dessous = l->dummy;
    l->dummy = bidon;
    p = (Cellule *)malloc(sizeof(Cellule));
    bidon->suivant = p;
    p->data = c->data;
    p->suivant = NULL;
    p->dessous = c;
    c = p;
    l->level++;
  }
}

/*
  Pr�condition(s): l initialis�e et manipul�e uniquement � travers les
  op�rations du module.

  R�sultat: affichage exhaustif de tous les �l�ments de l.
*/
void
print(const SkipList *l) {
  if (empty(l) == 0) {
    Cellule *foo = l->dummy;
    while (foo->dessous != NULL) {
      Cellule *bar = foo->suivant;
      while (bar->suivant != NULL) {
        l->pack.affiche(bar->data);
        bar = bar->suivant;
      }
      foo = foo->dessous;
      printf("\n");
    }
  }
}

static
Cellule *
_searchCell(const SkipList *l, Cellule *bidon, Object e) {
  if (bidon->suivant && l->pack.compare(e, bidon->suivant->data) == 0) {
    return bidon->suivant;
  } else {
    if (bidon->suivant && l->pack.compare(e, bidon->suivant->data) > 0)
      return _searchCell(l, bidon->suivant, e);
    if (bidon->dessous)
      return _searchCell(l, bidon->dessous, e);
  }
  return NULL;
}

Cellule *search(const SkipList *l, Object e) {
  return _searchCell(l, l->dummy, e);
}

static void _deleteCell(SkipList *l, Cellule *bidon, Object e) {
  Cellule *temp, *st = l->dummy;
  while (bidon->suivant != NULL &&
         l->pack.compare(e, bidon->suivant->data) == 0) {
    while (st->dessous != NULL) {
      if (st->suivant == bidon->suivant) {
        if (bidon->suivant->suivant != NULL)
          l->level--;
      }
      st = st->dessous;
    }
    temp = bidon->suivant;
    bidon->suivant = temp->suivant;

    l->pack.testament(&(temp->data));
    if (bidon->dessous != NULL) {
      _deleteCell(l, bidon->dessous, e);
    }
  }
  if (bidon->suivant != NULL && l->pack.compare(e, bidon->suivant->data) > 0) {
    _deleteCell(l, bidon->suivant, e);
  }
  if (bidon->dessous != NULL) {
    _deleteCell(l, bidon->dessous, e);
  }
}

void delete (SkipList *l, Object e) {
  if (search(l, e) != NULL) {
    l->size--;
    _deleteCell(l, l->dummy, e);
  } else
    printf("Suppression impossible\n");
}
