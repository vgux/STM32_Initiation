/*
 * huffman.c
 *
 *  Created on: Sep 27, 2021
 *      Author: user
 */

#ifndef INC_STDIO_H_
#include <stdio.h>
#endif

#ifndef INC_HUFFMAN_H_
#include <huffman.h>
#endif

uint16_t creerFeuille(struct noeud * arbre[256], uint32_t tab[256]) {
	uint16_t caseArbreLibre = 0;
	for(uint16_t i = 0; i < 256; i++) {
		if(tab[i] > 0) {
			arbre[caseArbreLibre] = (struct noeud*) malloc(sizeof(struct noeud));
			arbre[caseArbreLibre]->c = i;
			arbre[caseArbreLibre]->occurence = tab[i];
			arbre[caseArbreLibre]->gauche = NULL;
			arbre[caseArbreLibre]->droite = NULL;
			//printFeuille(arbre[caseArbreLibre], arbre[caseArbreLibre]);
			caseArbreLibre++;
			afficherTabArbreHuffman (arbre, caseArbreLibre);
		}
	}

	return(caseArbreLibre);
}

void printFeuille(struct noeud * arbre, uint32_t adresse) {
	printf("\n\n+-------------------------------+\n");
	printf("| Adresse \t| %#09x    |\n", adresse);
	printf("+-------------------------------+\n");
	printf("| Car \t\t| %c\t\t|\n", arbre->c);
	printf("+-------------------------------+\n");
	printf("| Occ \t\t| %d\t\t|\n", arbre->occurence);
	printf("+-------------------------------+\n");
	printf("| Gauche \t| %#09x \t|\n", arbre->gauche);
	printf("+-------------------------------+\n");
	printf("| Droite \t| %#09x \t|\n", arbre->droite);
	printf("+-------------------------------+\n");
}

void afficherTabArbreHuffman (struct noeud* arbre[256], uint32_t taille) {
	printf("\n\n---------------------------------------------------------------------------------+\n");
	printf(" Adresse \t | Caractere\t | Occurence\t | Gauche\t | Droite\t |\n");
	printf("---------------------------------------------------------------------------------+\n");
	for(uint16_t i = 0; i<taille; i++) {
		printf("%#09x\t | %c\t\t | %d\t\t |  %#09x \t |  %#09x \t |\n", arbre[i], arbre[i]->c, arbre[i]->occurence, arbre[i]->gauche, arbre[i]->droite);
		printf("---------------------------------------------------------------------------------+\n");
	}
}

void triArbre(struct noeud* arbre[256], uint32_t taille) {
  //Tri a bulle par ordre croissant
  for (uint16_t i = 0 ; i < taille-1; i++) {
	for (uint16_t j = 0 ; j < taille-i-1; j++) {
	  if (arbre[j]->occurence > arbre[j+1]->occurence) {
		uint32_t tmp = arbre[j];
		arbre[j] = arbre[j+1];
		arbre[j+1] = tmp;
	  }
	}
  }
}

struct noeud* creerRacine(struct noeud* arbre[256], uint32_t taille) {
	uint16_t i = 0;
	struct noeud* adresseNoeudPrecedent = arbre[0];
	struct noeud* adresseNoeud = 0;

	for(i = 1; i < taille; i++) {
		adresseNoeud = (struct noeud*) malloc(sizeof(struct noeud));
		adresseNoeud->c = '!';
		adresseNoeud->occurence = adresseNoeudPrecedent->occurence + arbre[i]->occurence;
		adresseNoeud->gauche = adresseNoeudPrecedent;
		adresseNoeud->droite = arbre[i];
		adresseNoeudPrecedent = adresseNoeud;
	}

	return(adresseNoeud); //retourne l'adresse de la racine
}