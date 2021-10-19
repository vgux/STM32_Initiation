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

/**
  * @brief  Initialisation du tableau de Huffman avec chacun des caracteres du texte a compresser
  * @param  arbre: structure contenant l'adresse des differentes feuilles
  * @param  tab: Tableau des occurences
  * @retval caseArbreLib: taille de l'arbre a la fin de l'initialisation
  */
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


/**
  * @brief  Affichage des caracteristiques de chaque feuille
  * @param  arbre:  structure contenant l'adresse des differentes feuilles
  * @param  adresse: adresse de la feuille
  * @retval None
  */
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

/**
  * @brief  Affichage en totalite du tableau de l'arbre de Huffman
  * @param  arbre:  structure contenant l'adresse des differentes feuilles
  * @param  taille: taille du tableau de l'arbre de Huffman
  * @retval None
  */
void afficherTabArbreHuffman (struct noeud* arbre[256], uint32_t taille) {
	printf("\n\n---------------------------------------------------------------------------------+\n");
	printf(" Adresse \t | Caractere\t | Occurence\t | Gauche\t | Droite\t |\n");
	printf("---------------------------------------------------------------------------------+\n");
	for(uint16_t i = 0; i<taille; i++) {
		printf("%#09x\t | %c\t\t | %d\t\t |  %#09x \t |  %#09x \t |\n", arbre[i], arbre[i]->c, arbre[i]->occurence, arbre[i]->gauche, arbre[i]->droite);
		printf("---------------------------------------------------------------------------------+\n");
	}
}

/**
  * @brief  tri des feuilles / noeuds de l'arbre de maniere croissante
  * @param  arbre:  structure contenant l'adresse des differentes feuilles
  * @param  taille: taille du tableau de l'arbre de Huffman
  * @retval None
  */
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

/**
  * @brief  Simplification de l'arbre de Huffman pour obtenir la racine de cet arbre
  * @param  arbre:  structure contenant l'adresse des differentes feuilles
  * @param  taille: taille du tableau de l'arbre de Huffman
  * @retval adresseNoeud: adresse de la structure racine
  */
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

	return(adresseNoeud); //retourne l'adresse de la racine
}

/**
  * @brief  Parcours completement l'arbre et affiche le caractere si l'element est une feuille
  * @param  ptrNoeud: pointeur vers une structure de type noeud
  * @retval None
  */
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

/**
  * @brief  Creation du code de chaque caractere afin de realiser la compression ulterieurement
  * @param  ptrNoeud: pointeur vers une structure de type noeud
  * @param  code: code de depart
  * @param  taille: taille du code au depart
  * @retval None
  */
void creerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille) {
	if(ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
		ptrNoeud->tailleCode = taille;
		ptrNoeud->code = code;
		printf("\n--------+------------------------------+\n"
				"%c \t| code : %d \t| taille : %d   |", ptrNoeud->c, ptrNoeud->code, ptrNoeud->tailleCode);

	} else {
		if(ptrNoeud->gauche) {
			creerCode(ptrNoeud->gauche, (code<<1)+1, taille+1);
		}

		if(ptrNoeud->droite) {
			creerCode(ptrNoeud->droite, code<<1, taille+1);
		}
	}
}

/**
  * @brief  Retourne l'adresse de la feuille ayant le caractere recherche
  * @param  ptrNoeud: pointeur vers une structure de type noeud
  * @param  caractere: caractere a trouver
  * @retval adresseNoeud: adresse du noeud ayant le caractere recherche
  */
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

/**
  * @brief  Realise la compression du texte
  * @param  ptrNoeud: pointeur vers la racine (structure noeud)
  * @param  texte: texte a compresser
  * @param  compressedText: texte compressé
  * @retval tailleCompress: taille totale du texte compresse en bits
  */
uint16_t textCompressor(struct noeud* ptrNoeud, uint8_t texte[256], uint8_t compressedText[256]) {

	uint16_t caseTableauCompress = 0, tailleCompresse = 0, i = 0;
	int8_t numeroBitDansCaseTableauCompress = 7;
	struct noeud* adresseCaractere = 0;
	while(texte[i] != 0) {
		adresseCaractere = getAdress(ptrNoeud, texte[i]);
		tailleCompresse += adresseCaractere->tailleCode;
		//printf("%c", texte[i]);

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

/**
  * @brief  Genere l'entete necessaire pour la decompression
  * @param  tabEntete: sortie contenant l'entete generee
  * @param  racine: racine de l'arbre de Huffman
  * @param  tailleFichierCompresse: taille du texte compressé
  * @param  nbrCaractereTotal: nombre total de caractere au sein du texte compresse
  * @param  tabOccurence: Tableau des occurences de chaque caractere
  * @retval None
  */
void generateurEntete(uint8_t tabEntete[256], struct noeud* racine, uint16_t tailleFichierCompresse, uint8_t nbrCaractereTotal, uint32_t tabOccurence[256]){

	//Taille du fichier compresse en bits
	tabEntete[2] = tailleFichierCompresse >> 7 & 0xFF;
	tabEntete[3] = tailleFichierCompresse & 0xFF;

	//Nombre total de caracteres du fichier d origine
	tabEntete[4] = nbrCaractereTotal >> 7 & 0xFF;
	tabEntete[5] = nbrCaractereTotal & 0xFF;

	uint8_t cptCaractere = 0;

	//Pour chaque caractere
	printf("\n\nCaractere presents dans entete");
	for(uint8_t i = 0; i < 255; i++) {
		if(tabOccurence[i] > 0) {
			struct noeud* feuilleCaractere = getAdress(racine, i);
			printf("\nCaractere : %c", feuilleCaractere->c);
			//Caractere 1 octet
			tabEntete[6+(cptCaractere*6)] = feuilleCaractere->c;

			//Code 4 octets
		    tabEntete[7+(cptCaractere * 6)] = feuilleCaractere->code >> 23 & 0xFF;
		    tabEntete[8+(cptCaractere * 6)] = feuilleCaractere->code >> 15 & 0xFF;
		    tabEntete[9+(cptCaractere * 6)] = feuilleCaractere->code >> 7 & 0xFF;
		    tabEntete[10+(cptCaractere * 6)] = feuilleCaractere->code & 0xFF;

		    //Taille Code 1 octet
			tabEntete[11+(cptCaractere * 6)] = feuilleCaractere->tailleCode;

			cptCaractere++;
		}
	}
	printf("\n");

	//Taille de l entete en octets
	uint16_t taille = 6 + (cptCaractere * 6);
	tabEntete[0] =  taille >> 7 & 0xFF;
	tabEntete[1] = taille & 0xFF;

	for(uint16_t i = 0; i<taille; i++) {
		printf("\ntabEntete[%d] = %d", i, tabEntete[i]);
	}

}

/************************
 * Fonctions privees	*
 ************************/

/**
  * @brief  Retire le premier element de l'arbre et decale le reste de l'arbre
  * @param  arbre: structure contenant l'adresse des differentes feuilles
  * @param  taille: taille de l'arbre
  * @retval taille: taille actualisee de l'arbre
  */
static uint16_t shiftArbre(struct noeud* arbre[256], uint32_t taille) {
	uint16_t i = 0;
	for(i = 0; i<taille-1; i++) {
		arbre[i] = arbre[i+1];
	}
	arbre[i]=0;

	return (taille-1);
}
