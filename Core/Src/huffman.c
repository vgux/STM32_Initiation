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

	afficherTabArbreHuffman(arbre, taille);

	do {
		adresseNoeud = (struct noeud*) malloc(sizeof(struct noeud));
		adresseNoeud->c = 0;
		adresseNoeud->occurence = arbre[0]->occurence + arbre[1]->occurence;
		adresseNoeud->gauche = arbre[0];
		adresseNoeud->droite = arbre[1];

		arbre[1] = adresseNoeud;

		taille = shiftArbre(arbre, taille);

		triArbre(arbre, taille);

		afficherTabArbreHuffman(arbre, taille);


	} while (taille > 1);

	/*for(i = 1; i < taille; i++) {
		adresseNoeud = (struct noeud*) malloc(sizeof(struct noeud));
		adresseNoeud->c = 0;
		adresseNoeud->occurence = adresseNoeudPrecedent->occurence + arbre[i]->occurence;
		adresseNoeud->gauche = adresseNoeudPrecedent;
		adresseNoeud->droite = arbre[i];
		adresseNoeudPrecedent = adresseNoeud;
	}*/

	return(adresseNoeud); //retourne l'adresse de la racine
}

void parcourirArbre(struct noeud* ptrNoeud) {
	if(ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
		printf("\n%c -> %u", ptrNoeud->c, ptrNoeud->occurence);
	} else {
		if(ptrNoeud->gauche) {
			parcourirArbre(ptrNoeud->gauche);
		}

		if(ptrNoeud->droite) {
			parcourirArbre(ptrNoeud->droite);
		}
	}
}

void creerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille) {
	if(ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
		ptrNoeud->tailleCode = taille;
		ptrNoeud->code = code;
		printf("%c \t code : %d \t taille : %d\n", ptrNoeud->c, ptrNoeud->code, ptrNoeud->tailleCode);

	} else {
		if(ptrNoeud->gauche) {
			creerCode(ptrNoeud->gauche, (code<<1)+1, taille+1);
		}

		if(ptrNoeud->droite) {
			creerCode(ptrNoeud->droite, code<<1, taille+1);
		}
	}
}

struct noeud* getAdress(struct noeud* ptrNoeud, uint8_t caractere) {
	struct noeud* adresseNoeud = 0;

	if(ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
		if(ptrNoeud->c == caractere) {
			return ptrNoeud;
		} else {
			return NULL;
		}
	} else {
		if(ptrNoeud->gauche) {
			adresseNoeud = getAdress(ptrNoeud->gauche, caractere);
			if(adresseNoeud) {
				return(adresseNoeud);
			}
		}

		if(ptrNoeud->droite) {
			adresseNoeud = getAdress(ptrNoeud->droite, caractere);
			if(adresseNoeud) {
				return(adresseNoeud);
			}
		}
	}
}

uint16_t textCompressor(struct noeud* ptrNoeud, uint8_t texte[256], uint8_t compressedText[256]) {

	uint16_t caseTableauCompress = 0, tailleCompresse = 0, i = 0;
	int8_t numeroBitDansCaseTableauCompress = 7;
	struct noeud* adresseCaractere = 0;
	while(texte[i] != 0) {
		adresseCaractere = getAdress(ptrNoeud, texte[i]);
		tailleCompresse += adresseCaractere->tailleCode;
		printf("%c", texte[i]);

		for(int16_t j = (adresseCaractere->tailleCode)-1; j >= 0; j--) {
			uint8_t codeDecale = (adresseCaractere->code >> j) & 1; //codeDecale vaut 0 ou 1

			//printf("\n%c : code %d >> %d\n\n", adresseCaractere->c, adresseCaractere->code, j);

			// insertion de 0 ou de 1 a la suite du texte compresse
			if(codeDecale) {
				compressedText[caseTableauCompress] |= 1 << numeroBitDansCaseTableauCompress;
			} else {
				compressedText[caseTableauCompress] &= ~(1 << numeroBitDansCaseTableauCompress);
			}

			numeroBitDansCaseTableauCompress--;

			if(numeroBitDansCaseTableauCompress < 0) {
				numeroBitDansCaseTableauCompress = 7;
				caseTableauCompress++;
			}
		}
		i++;
	}
	printf("\nContenu compresse : %d, %d, %d\n", compressedText[0], compressedText[1], compressedText[2]);

	return tailleCompresse;
}

void generateurEntete(uint8_t tabEntete[256], struct noeud* racine, uint16_t tailleFichierCompresse, uint8_t nbrCaractereTotal, uint32_t tabOccurence[256]){

	//Taille du fichier compresse en bits
	tabEntete[2] = tailleFichierCompresse >> 7 & 0xFF;
	tabEntete[3] = tailleFichierCompresse & 0xFF;

	//Nombre total de caracteres du fichier d origine
	tabEntete[4] = nbrCaractereTotal >> 7 & 0xFF;
	tabEntete[5] = nbrCaractereTotal & 0xFF;

	uint8_t cptCaractere = 0;
	//Pour chaque caractere
	for(uint8_t i = 0; i < 255; i++) {
		if(tabOccurence[i] > 0) {
			struct noeud* feuilleCaractere = getAdress(racine, i);
			printf("\nCaractere : %c", feuilleCaractere->c);
			tabEntete[6+(cptCaractere*3)] = feuilleCaractere->c;
		    tabEntete[7+(cptCaractere*3)] = feuilleCaractere->code;
			tabEntete[8+(cptCaractere*3)] = feuilleCaractere->tailleCode;
			cptCaractere++;
		}
	}

	//Taille de l entete en octets
	uint16_t taille = 6 + (cptCaractere * 3);
	tabEntete[0] =  taille >> 7 & 0xFF;
	tabEntete[1] = taille & 0xFF;

	for(uint16_t i = 0; i<taille; i++) {
		printf("\ntabEntete[%d] = %d", i, tabEntete[i]);
	}

}

/************************
 * Fonctions privees	*
 ************************/

static uint16_t shiftArbre(struct noeud* arbre[256], uint32_t taille) {
	uint16_t i = 0;
	for(i = 0; i<taille-1; i++) {
		arbre[i] = arbre[i+1];
	}
	arbre[i]=0;

	return (taille-1);
}
