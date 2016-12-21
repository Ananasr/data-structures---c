/**
 * \file skip_list.h
 * \brief Fichier d'en-t�te pour le type SkipList
 * \author Hedi Nasr
 * \version 0.2
 * \date 19 d�cembre 2016
 *
 * Fichier d'en-t�te contenant les prototypes des fonctions et
 * proc�dures manipulant le type SkipList.
 *
 * Inclusion des modules utilis�s par le module SkipList
 * (A l'exclusion de ceux qui sont seulement utilises dans l'implantation:
 * ceux la sont inclus dans le fichier d'implantation)
 */
#ifndef _SKIP_LIST
#define _SKIP_LIST

#include "../utils/object.h"

/**
 * \struct Cellule
 * \brief Structure Cellule (entit�e de la liste)
 */
typedef struct Cellule {
  Object data;             /*!< Datarmation contenue dans la Cellule */
  struct Cellule *suivant; /*!< Pointeur sur la Cellule suivante */
  struct Cellule *dessous; /*!< Pointeur sur la Cellule d'en dessous */
} Cellule;

/**
 * \struct SkipList
 * \brief Structure representant la SkipList
 */
typedef struct SkipList {
  Cellule *dummy;  /*!< Pointeur sur la Cellule bidon */
  ObjectPack pack; /*!< Indique le type d'�l�ment de la SkipList */
  int size;        /*!< Nombre d'�lement(s) de la SkipList */
  int level;       /*!< Nombre de niveau(x) de la SkipList */
} SkipList;

/**
 * \fn void init(SkipList *list, ObjectPack pack);
 * \brief initialise la liste list
 *
 * \param *list  non pr�alablement initialis�e
 * \param pack indique le type d'�l�ment de la SkipList
 *
 */
void init(SkipList *list, ObjectPack pack);

/**
 * \fn void clear(SkipList *l);
 * \brief *l pr�te � �tre d�truite
 * \param *l pr�alablement initialis�e et manipul�e uniquement � travers les
 * op�rations du module.
 */
void clear(SkipList *l);

/**
 * \fn int empty(const SkipList *l);
 * \brief retourne 1 si l est vide, 0 sinon
 * \param l pr�alablement initialis�e et manipul�e uniquement � travers les
 * op�rations du module.
 */
int empty(const SkipList *l);

/**
 * \fn void print(const SkipList *l);
 * \brief Affichage exhaustif de tous les �l�ments de l
 * \param l initialis�e et manipul�e uniquement � travers les op�rations du
 * module.
 */
void print(const SkipList *l);

/**
 * \fn void push_back(SkipList *l, Object e);
 * \brief L'Object e est ajout� en t�te de *l
 * \param *l initialis� et manipul� uniquement � travers les op�rations du
 * module
 * \param e initialis� et manipul� uniquement � travers les op�rations du
 * module
 */
void push_back(SkipList *l, Object e);

/**
 * \fn Cellule * search(const SkipList *l, Object e);
 * \brief retourne l'�l�ment si celui-ci � �t� trouv�
 * \param *l initialis� et manipul� uniquement � travers les op�rations du
 * module
 * \param e initialis� et manipul� uniquement � travers les op�rations du
 * module
 */
Cellule *search(const SkipList *l, Object e);

/**
 * \fn void delete(SkipList *l, Object e);
 * \brief toutes les occurrences de e sont supprim�es
 * \param *l initialis� et manipul� uniquement � travers les op�rations du
 * module
 * \param e initialis� et manipul� uniquement � travers les op�rations du
 * module
 */
void delete (SkipList *l, Object e);

#endif
