/*
 * huffman.h
 *
 *  Created on: Sep 27, 2021
 *      Author: user
 */

#ifndef INC_HUFFMAN_H_
#define INC_HUFFMAN_H_

#endif /* INC_HUFFMAN_H_ */

#ifndef INC_STDIO_H_
#include <stdio.h>
#endif


struct noeud {
	uint8_t c;						// Caractere initial
	uint32_t occurence;				// Nombre d'occurences
	uint32_t code;					// Code binaire dans l'arbre
	uint32_t tailleCode;			// Nombre de bits du code
	struct noeud *gauche, *droite;	// Lien vers les noeuds suivants
};

uint16_t creerFeuille(struct noeud * arbre[256], uint32_t tab[256]);
void printFeuille(struct noeud * arbre, uint32_t adresse);
void afficherTabArbreHuffman (struct noeud* arbre[256], uint32_t taille);
void triArbre(struct noeud* arbre[256], uint32_t taille);
struct noeud* creerRacine(struct noeud* arbre[256], uint32_t taille);
