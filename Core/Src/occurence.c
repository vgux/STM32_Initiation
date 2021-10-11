/*
 * occurence.c
 *
 *  Created on: Sep 27, 2021
 *      Author: user
 */


#include "occurence.h"

void occurence(uint8_t* chaine, uint32_t tab[256]) {
  //Obtention des occurences de chaque caractere
  while(*chaine != '\0') {
	  tab[*chaine]++;
	  chaine++;
  }

}

void occurencePrint(uint8_t* chaine, uint32_t tab[256]) {
	  //Affiche chaque caractere ainsi que son occurence sous forme de tableau
	  printf("\n\n");
	  printf("+-------+-------+\n");
	  printf("| Car \t| Occ\t|\n");
	  printf("+-------+-------+\n");
	  for(int i = 0; i<256; i++) {
		  printf("| %c \t| %d \t|\n", i, tab[i]);
		  printf("+-------+-------+\n");
	  }

}

uint16_t obtenirNbCarDifferent(uint32_t tab[256]) {
	uint16_t nbCarDifferent = 0;
	for(uint8_t i = 0; i < 255; i++) {
		if(tab[i] > 0) {
			nbCarDifferent++;
		}
	}
	return nbCarDifferent;
}
