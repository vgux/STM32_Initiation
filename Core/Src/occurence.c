/*
 * occurence.c
 *
 *  Created on: Sep 27, 2021
 *      Author: user
 */


#include "occurence.h"
/**
  * @brief  Obtention de l'occurence de chaque caractere
  * @param  chaine: texte dans lequel on souhaite compter l'apparition de chaque caractère
  * @param  tab: tableau contenant l'occurence de chaque caractere
  * @retval None
  */
void occurence(uint8_t* chaine, uint32_t tab[256]) {
  while(*chaine != '\0') {
	  tab[*chaine]++;
	  chaine++;
  }

}

/**
  * @brief  Affiche chaque caractere ainsi que son occurence sous forme de tableau
  * @param  tab: Tableau des occurences
  * @retval None
  */
void occurencePrint(uint32_t tab[256]) {
	  printf("\n\n");
	  printf("+-------+-------+\n");
	  printf("| Car \t| Occ\t|\n");
	  printf("+-------+-------+\n");
	  for(int i = 0; i<256; i++) {
		  printf("| %c \t| %d \t|\n", i, tab[i]);
		  printf("+-------+-------+\n");
	  }

}

/**
  * @brief  Calcul du nombre de caractere differents presents au sein du tableau des occurences
  * @param  tab: Tableau des occurences
  * @retval nbCarDifferent
  */
uint16_t obtenirNbCarDifferent(uint32_t tab[256]) {
	uint16_t nbCarDifferent = 0;
	for(uint8_t i = 0; i < 255; i++) {
		if(tab[i] > 0) {
			nbCarDifferent++;
		}
	}
	return nbCarDifferent;
}
