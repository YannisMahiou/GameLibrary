#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*STRUCTURES:*/

typedef struct{
		char nom[27],type[27];
		int nbExemplaire;
	    }Jeux;

typedef struct{
		int jour;
		int mois;
		int an;
	    }Date;

typedef struct{
		char identifiant[5];
		char nom[27],prenom[27];
		Date DateAd;
		int NbEmprunts;
	    }Adherent;

typedef struct {
		Adherent a;
		Jeux j;
		Date Demp;
		}Emprunt;

typedef struct maillonAdherent
		{
		Adherent a;
		struct maillonAdherent *suiv;	
		}MaillonAd, *ListeAdherent;

typedef struct{
		int places;
		ListeAdherent lAdh;
		char titre[27];
		}ApremTH;

typedef struct maillonJeu
		{
		Jeux j;
		struct maillonJeu *suiv;	
		}MaillonJeu, *ListeJeu;

typedef struct maillonEmprunt
		{
		Emprunt e;
		struct maillonEmprunt *suiv;	
		}MaillonEmprunt, *ListeEmprunt;


/*********************************************************/


/* MENU */

void afficherMenu(void);
int menu(void);

/*choix1  --> INSCRIPTION ADHERENT */

Adherent LireAdherent(FILE *flot);
ListeAdherent EnregistrerAdherent(ListeAdherent la);
ListeAdherent InsertionAdherent(ListeAdherent la, Adherent A);
ListeAdherent InsertionEnT(ListeAdherent la,Adherent A);
Adherent EntrerAdherent(void);
ListeAdherent ListeADvide(void);

/*choix2  --> SUPPRESSION ADHERENT */

ListeAdherent suptAD (ListeAdherent l);
ListeAdherent supprimerAD (ListeAdherent l, Adherent A);
ListeAdherent SupprimerAdherent(ListeAdherent la);

/*	TRI LISTE DE JEUX 	*/

void echangerJ (Jeux *tJeux, int i, int j);
int plusGrandJ (Jeux *tJeux, int n);
Jeux *TrierJeux (Jeux *tJeux, int n);

/*choix3  -->  ENREGISTRER UN EMPRUNT */

Emprunt LireEmprunt(FILE *flot);
Adherent rechercherAdherent(ListeAdherent la, char *identifiant,int *RA);
Jeux lireJeux(FILE *flot);
Jeux *chargerJeux(FILE *flot,Jeux *tJeux,int *nb,int *max);
int rechercherJeux(Jeux *tJeux,char *nom,int max);
ListeEmprunt InsertionEmpT(ListeEmprunt le,Emprunt E);
ListeEmprunt InsertionEmprunt(ListeEmprunt le, Emprunt E);
ListeEmprunt EnregistreEmprunt(ListeAdherent la,ListeEmprunt lE);
void AfficherJeux(Jeux tJeux[],int nb);
ListeEmprunt ListeEMvide(void);

/*choix4  -->  ENREGISTRER APREM THEMATIQUE */

void afficherAP (ApremTH A);
void afficher(ApremTH **tapth,int nb);
ApremTH lireAP(FILE *flot);
ApremTH **ChargeAPTH (int *max,int *i);
int rechercheAp (ApremTH **tapth, int max, char *nom, int *trouv);
int plusGrand (ApremTH **tapth, int n);
void echanger (ApremTH **tapth, int i, int j);
ApremTH **trierParEchange (ApremTH **tapth, int n);
int nouveauApTH (ApremTH **tapth, int pos,ApremTH A,int tLog);
void sauvegarde(ApremTH **tapth,int tLog);
void EnregistrerAPTH (void);

/*choix5 --> AJOUTER UN ADHERENT A UNE APRES-MIDI THEMATIQUE */

ApremTH **chargerAPTH(ListeAdherent la,ApremTH **tapth,int tLog);
void AffichageAPTH (ListeAdherent la);
void sauvegardeAPTH (ApremTH **tapth,int Ins,Adherent A);
int appartientTH (ListeAdherent la, char *identifiant);
int longueur (ListeAdherent la);
void InsertionAdherentAPTH (ListeAdherent la);

/*choix6 --> LISTE EMPRUNT EN RETARD*/

void ListeEmpRetard(ListeEmprunt lEmp);

/*choix7* --> AFFICHAGE LISTE ADHERENT */

void afficherListe (ListeAdherent la);

/*choix8  -->   AFFICHAGE LISTE EMPRUNT  */

void afficherListeE(ListeEmprunt le);


void global(void);


















