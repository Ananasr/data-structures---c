/**
 * \file object.h
 * \brief Fichier d'en-t�te pour le type Object
 * \author Hedi Nasr
 * \version 0.2
 * \date 19 d�cembre 2016
 *
 * Fichier d'en-t�te contenant les prototypes des fonctions et proc�dures
 * manipulant le type Object.
 */
#ifndef _OBJECT
#define _OBJECT

#include <stdio.h>

/**
 * \typedef Object
 * \brief Object nous permettras de faire abstraction sur le type des �l�ments
 * manipul�s.
 */
typedef void *Object;

/**
 * \struct ObjectPack
 * \brief Structure pack d'�l�ments
 *
 * ObjectPack est une structure de gestion d'�l�ments. Celle-ci nous permet de
 * manipuler
 * des "pack" d'�l�ments, afin d'avoir plus de fl�xibilit� pour la g�n�ricit�.
 * Celle-ci
 * contient les pointeurs sur les diff�rentes fonctions manipulant les �l�ments.
 */
typedef struct ObjectPack {
  void (*affiche)(Object);     /*!< Pointeur sur la procedure d'affichage. */
  void (*testament)(Object *); /*!< Pointeur sur la procedure de testament. */
  void (*init)(Object *,
               Object); /*!< Pointeur sur la procedure d'initialisation. */
  int (*compare)(Object,
                 Object); /*!< Pointeur sur la fonction de comparaison. */
} ObjectPack;

/**
 * \fn void afficheInt(Object e);
 * \brief Affiche l'�l�ment sur la sortie standard
 *
 * \param e l'�l�ment � afficher
 * Pr�condition(s): e initialis� et manipul� uniquement a travers les fonctions
 * du
 * module.
 */
void afficheInt(Object e);

/**
 * \fn void initInt(Object * e1, Object e2);
 * \brief e1 clone de l'element correspondant a e2
 *
 * \param [in] e2 initialise de type effectif int ou bien e2 adresse d'une
 * variable de type int
 * \param [in,out] e1
 */
void initInt(Object *e1, Object e2);

/**
 * \fn int compareInt(Object e1, Object e2);
 * \brief Si e1 > e2 retourne 1, 0 sinon
 *
 * \param e1 initialise
 * \param e2 initialise
 */
int compareInt(Object e1, Object e2);

/**
 * \fn void testamentInt(Object *e1);
 * \brief e1 libere et detruit
 *
 * \param e1 initialise et manipule uniquement � travers le module
 */
void testamentInt(Object *e1);

static const ObjectPack Int = {afficheInt, testamentInt, initInt, compareInt};

#endif
