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
  void (*print)(Object);     /*!< Pointeur sur la procedure d'affichage. */
  void (*clear)(Object *); /*!< Pointeur sur la procedure de testament. */
  void (*init)(Object *,
               Object); /*!< Pointeur sur la procedure d'initialisation. */
  int (*compare)(Object,
                 Object); /*!< Pointeur sur la fonction de comparaison. */
} ObjectPack;

#endif
