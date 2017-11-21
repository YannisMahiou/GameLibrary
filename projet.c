#include "projet.h" 

/*****************  MENU ************************ */

void afficherMenu(void)
{
	printf("\n======================\n\n");
	printf("1-Ajouter un nouvel adhérent\n");
	printf("2-Supprimer un adhérent\n");
	printf("3-Ajouter un emprunt\n");
	printf("4-AJouter une après-midi thématique\n");
	printf("5-Inscription d'un adhérent à une après-midi thématique\n");
	printf("6-Liste des emprunts en retard\n");
	printf("7-Afficher liste des adhérents\n");
	printf("8-Afficher liste des Emprunts\n");
	printf("9-Quitter & Sauvegarder\n");
	printf("\n======================\n");
}

int menu(void)
{
	int choix;
	afficherMenu();
	printf("Quel est Votre choix? \n");
	scanf("%d%*c",&choix);
	while (choix<1 || choix>9)
	{
		printf("Erreur choix possible 1 à 9\n");
		afficherMenu();
		printf("Quel est votre Choix?");
		scanf("%d%*c",&choix);
	}
	return choix;
}

/********** Initialisation des Listes ********/

ListeAdherent ListeADvide(void)
{
	return NULL;
}

ListeEmprunt ListeEMvide(void)
{
	return NULL;
}

/**************** ENREGISTRER ADHERENT ***********************/

Adherent LireAdherent(FILE *flot)
{	
	Adherent A;

	fscanf(flot,"%s%*c",A.identifiant);	
	
	fgets(A.nom,27,flot);
	A.nom[strlen(A.nom)-1]='\0';
	
	fgets(A.prenom,27,flot);
	A.prenom[strlen(A.prenom)-1]='\0';
	
	fscanf(flot,"%d%*c",&A.NbEmprunts);

	if(A.NbEmprunts>=4)
		A.NbEmprunts=3;
	
	fscanf(flot,"%d%*c%d%*c%d%*c",&A.DateAd.jour,&A.DateAd.mois,&A.DateAd.an);

	return A;
}

Adherent EntrerAdherent(void)
{
	Adherent A;
	FILE *flot;
		
	printf("Rentrer le nom de l'Adhérent \n");
	fgets(A.nom,27,stdin);
	A.nom[strlen(A.nom)-1]='\0';

	printf("Rentrer le prenom de l'Adhérent \n");
	fgets(A.prenom,27,stdin);
	A.prenom[strlen(A.prenom)-1]='\0';

	printf("Rentrer l'identifiant de l'Adhérent: exemple->P123 \n");
	scanf("%s",A.identifiant);
	

	A.NbEmprunts=0;
	
	system("date +%Y-%m-%d >> date.don");
	flot=fopen("date.don","r");
	if(flot==NULL)
	{
		printf("erreur fichier");
		exit(1);
	}
	fscanf(flot,"%d%*c%d%*c%d%*c",&A.DateAd.an,&A.DateAd.mois,&A.DateAd.jour);

	printf("Inscription le : \t %d/%d/%d \n",A.DateAd.jour,A.DateAd.mois,A.DateAd.an);
	fclose(flot);
	flot=fopen("date.don","w+");
	fclose(flot);
	return A;
}

/* Insere les adherents par ordres alphabetique selon leur Nom 	*/

ListeAdherent InsertionEnT (ListeAdherent la, Adherent A)
{
	MaillonAd *m;

	m=(MaillonAd*)malloc(sizeof(MaillonAd));
	if(m==NULL)
	{
		printf("Problème allocation \n");
		exit(1);
	}
	m->a=A;
	m->suiv=la;
	return m;
}

	
ListeAdherent InsertionAdherent(ListeAdherent la, Adherent A)
{
	if(la==NULL)
		return InsertionEnT(la,A);
	if(strcmp((la->a).nom,A.nom)>0) 
		return InsertionEnT(la,A);
	if(strcmp((la->a).nom,A.nom)==0 && strcmp((la->a).prenom,A.prenom)==0 )
		return InsertionEnT(la,A);
	la->suiv=InsertionAdherent(la->suiv,A);
	return la;
}

/*************** Enregistrement d'un adherent **************/

ListeAdherent EnregistrerAdherent(ListeAdherent la)
{
	Adherent A;
	ListeAdherent l;
	int choix=1;
	
	while(choix!=0)
	{
		
		A=EntrerAdherent();
		la=InsertionAdherent(la,A);
		printf("Voulez vous rentrez un nouvel Adhérent? (oui-> 1 non-> 0) : \n");
		scanf("%d%*c",&choix);
		
	}
	l=ListeADvide();
	l=la;
	while(l!=NULL)
	{
		printf("************************************************************\n");
		printf("IDENTIFIANT : %s \n Nom: %s\t Prénom: %s\n\n Inscription le : \t %d/%d/%d \n",(l->a).identifiant,(l->a).nom,(l->a).prenom,(l->a).DateAd.jour,(l->a).DateAd.mois,(l->a).DateAd.an);
		printf("************************************************************\n");
		l=l->suiv;
	}
	printf("\n ****** FIN LISTE ADHERENTS ******  \n");
	return la;
}

/*******************SUPPRIMER ADHERENT******************************/

ListeAdherent suptAD (ListeAdherent l)
{
	MaillonAd *m;

	if(l==NULL)
	{
		printf("Opération Interdite\n");
		exit(1);
	}
	m=l;
	l=l->suiv;
	free(m);
	return l;
}

ListeAdherent supprimerAD (ListeAdherent l, Adherent A)
{
	if(l==NULL)
		return l;
	if(strcmp(A.identifiant,(l->a).identifiant)==0)
		return suptAD(l);
	l->suiv=supprimerAD(l->suiv,A);
	return l;
}

ListeAdherent SupprimerAdherent(ListeAdherent la)
{

	Adherent A;
	
	afficherListe(la);

	printf("Rentrer l'identifiant de l'Adhérent: \n");
	scanf("%s",A.identifiant);

	la=supprimerAD(la,A);

	return la;
}

/*************affiche les adherents actuels*********************/

void afficherListe(ListeAdherent la)
{
	while(la != NULL)
	{	
		printf("***********************************************\n");
		printf("IDENTIFIANT : %s \n Nom: %s\t Prénom: %s\t Nb d'emprunt :%d\n Inscription le : \t %d/%d/%d \n",(la->a).identifiant,(la->a).nom,(la->a).prenom,(la->a).NbEmprunts,(la->a).DateAd.jour,(la->a).DateAd.mois,(la->a).DateAd.an);
		printf("***********************************************\n");
		la=la->suiv;
	}
	printf("\n");
}

/*************************TRIER LES JEUX PAR ORDRE ALPHABETIQUE*****************************/

int plusGrandJ (Jeux *tJeux, int n)
{
	int i, pgJ=0;

	for(i=0;i<n;i++)
		if(strcmp(tJeux[i].nom,tJeux[pgJ].nom)>0)
			pgJ=i;
	return pgJ;
}

void echangerJ (Jeux *tJeux, int i, int j)
{
	Jeux aux;

	aux=tJeux[i];
	tJeux[i]=tJeux[j];
	tJeux[j]=aux;
}

Jeux *TrierJeux (Jeux *tJeux, int n)
{
	int pgJ;

	while(n>1)
	{
		pgJ=plusGrandJ(tJeux,n);
		echangerJ(tJeux,pgJ,n-1);
		n=n-1;
	}
	return tJeux;

}

/*************ENREGISTRER EMPRUNT*******************/
Emprunt LireEmprunt(FILE *flot)
{
	Emprunt E;

	fgets(E.a.identifiant,6,flot);
	E.a.identifiant[strlen(E.a.identifiant)-1]='\0';

	fscanf(flot,"%d%d%d%*c",&E.Demp.jour,&E.Demp.mois,&E.Demp.an);

	fgets(E.j.nom,27,flot);
	E.j.nom[strlen(E.j.nom)-1]='\0';
	return E;
}

Adherent rechercherAdherent(ListeAdherent la, char *identifiant,int *RA)
{
	while(la!=NULL)
	{
		if(strcmp(identifiant,(la->a).identifiant)==0)
			{
				printf("%s\t%s\n",(la->a).nom,(la->a).prenom);
				*RA=1;
				return la->a;
			}
		if(strcmp(identifiant,(la->a).identifiant)<0)
		{		
				*RA=0;
		}		
		la=la->suiv;
	}
	*RA=0;
}

int NombreEmpA(ListeAdherent la, char *identifiant)
{
	while(la!=NULL)
	{
		if(strcmp(identifiant,(la->a).identifiant)==0)
		{
			(la->a).NbEmprunts=(la->a).NbEmprunts+1;
			return (la->a).NbEmprunts;
		}
		la=la->suiv;
	}
}

Jeux lireJeux(FILE *flot)
{
	Jeux J;
	fscanf(flot,"%d%*c",&J.nbExemplaire);
	fgets(J.nom,50,flot);
	J.nom[strlen(J.nom)-1]='\0';
	fgets(J.type,50,flot);
	J.type[strlen(J.type)-1]='\0';
	
	return J;
}

Jeux *chargerJeux(FILE *flot,Jeux *tJeux,int *nb,int *max)
{	
	Jeux J;
	Jeux *aux;
	int m=0;
	
	J=lireJeux(flot);
	while(!feof(flot))
	{
		if(*nb==*max)
		{		
			*max=*max+100;
			aux=(Jeux*)realloc(tJeux,*max*sizeof(Jeux));
			if(aux==NULL)
				{
					printf("Problème Reallocation\n");
					exit(1);
				}
			tJeux=aux;
		}
		tJeux[m]=J;
		m=m+1;
		J=lireJeux(flot);
	}

	*nb=m;
	return tJeux;
	
}
void AfficherJeux(Jeux tJeux[],int nb)
{
	int i;
	for(i=0;i<nb;i++)
	{	
		printf("%d\t%s\t%s\n",tJeux[i].nbExemplaire,tJeux[i].nom,tJeux[i].type);
		printf("\n=========================\n");
	}
}
	

int rechercherJeux(Jeux *tJeux,char *nom,int max)
{
	int i,inf,sup;
	inf=0;
	sup=max-1;
	while(inf<=sup)
	{
		i=(inf+sup)/2;
		if(strcmp(nom,tJeux[i].nom)==0)
			return i;
		if(strcmp(nom,tJeux[i].nom)<0)
			sup=i-1;
		if(strcmp(nom,tJeux[i].nom)>0)
			inf=i+1;
	}
	return -1;
	
}

ListeEmprunt InsertionEmpT(ListeEmprunt le,Emprunt E)
{
	MaillonEmprunt *m;
	m=(MaillonEmprunt*)malloc(sizeof(MaillonEmprunt));
	if(m==NULL)
	{
		printf("Problème allocation \n");
		exit(1);
	}
	m->e=E;
	m->suiv=le;
	return m;
}

	/* Insere les emprunt par ordres alphabetique celon leur nom*/
	
ListeEmprunt InsertionEmprunt(ListeEmprunt le, Emprunt E)
{
	if(le==NULL)
		return InsertionEmpT(le,E);
	if(strcmp((le->e).a.nom,E.a.nom)>0) 
		return InsertionEmpT(le,E);
	if(strcmp((le->e).a.nom,E.a.nom)==0 && strcmp((le->e).a.prenom,E.a.prenom)==0 && strcmp((le->e).a.identifiant,E.a.identifiant)==0)
		return InsertionEmpT(le,E);
	le->suiv=InsertionEmprunt(le->suiv,E);
	
	return le;
}

ListeEmprunt EnregistreEmprunt(ListeAdherent la,ListeEmprunt lE)
{
	Adherent A;
	int RA,RJ,nbJ=0,nbE,maxJ=0,i;
	Jeux J,*tJeux;
	Emprunt E;
	
	FILE * flot;

	flot=fopen("jeux.don","r+");
	if(flot == NULL)
		exit(1);
	tJeux=(Jeux*)malloc(10*sizeof(Jeux));
	if(tJeux==NULL)
		{
			printf("Problème Malloc \n");
			exit(1);
		}
	
	tJeux=chargerJeux(flot,tJeux,&nbJ,&maxJ);
	afficherListe(la);

	tJeux=TrierJeux(tJeux,nbJ);

	printf("Rentrer l'identifiant de l'Adhérent: \n");
	scanf("%s%*c",A.identifiant);
	printf("******************************\n");
	A=rechercherAdherent(la,A.identifiant,&RA);

	while(RA==0)	
	{
		printf("Identifiant Adherent inexistant \n");
		printf("Rentrer l'identifiant de l'Adhérent: \n");
		scanf("%s%*c",A.identifiant);
		printf("******************************\n");
		A=rechercherAdherent(la,A.identifiant,&RA);
	}
	nbE=NombreEmpA(la,A.identifiant);
	A.NbEmprunts=nbE;	

	if(A.NbEmprunts>3)
	{
		printf("Trop d'emprunt \n");	
		return lE;
	}
	AfficherJeux(tJeux,nbJ);
	printf("Quel jeux emprunter\n");
	fgets(J.nom,27,stdin);
	J.nom[strlen(J.nom)-1]='\0';
	
	RJ=rechercherJeux(tJeux,J.nom,nbJ);
	while(RJ==-1)	
	{
		printf("Jeux inexistant \n");
		printf("Quel jeux emprunter?\n");
		fgets(J.nom,27,stdin);
		J.nom[strlen(J.nom)-1]='\0';
		RJ=rechercherJeux(tJeux,J.nom,nbJ);
	}
	
	if(tJeux[RJ].nbExemplaire == 0)
	{
		printf("Jeux indisponible \n");
		return lE;
	}

	tJeux[RJ].nbExemplaire = tJeux[RJ].nbExemplaire-1;
		 
	E.j=tJeux[RJ];
	strcpy(E.a.identifiant,A.identifiant);
	fclose(flot);

	flot=fopen("jeux.don","w+");
	if(flot==NULL)
	{
		printf("erreur fichier");
		exit(1);
	}
	for(i=0;i<nbJ;i++)
	{
		fprintf(flot, "%d\n%s\n%s\n",tJeux[i].nbExemplaire,tJeux[i].nom,tJeux[i].type);
	}

	fclose(flot);


	system("date +%Y-%m-%d >> dateEmp.don");
	flot=fopen("dateEmp.don","r");
	if(flot==NULL)
	{
		printf("erreur fichier");
		exit(1);
	}
	fscanf(flot,"%d%*c%d%*c%d%*c",&E.Demp.an,&E.Demp.mois,&E.Demp.jour);

	lE=InsertionEmprunt(lE,E);
	printf("Emprunt enregistré le :%d/%d/%d\n par identifiant : %s \n pour le jeux :%s \n",E.Demp.jour,E.Demp.mois,E.Demp.an,A.identifiant,E.j.nom);
	printf("******************************\n");
	fclose(flot);

	flot=fopen("dateEmp.don","w+");
	fclose(flot);
	return lE;
}

/*************affiche les adherents actuels*********************/

void afficherListeE(ListeEmprunt le)
{
	while(le != NULL)
	{	
		printf("***********************************************\n");
		printf("IDENTIFIANT : %s \n Emprunté le : \t %d/%d/%d \n Du Jeux :%s \n",(le->e).a.identifiant,(le->e).Demp.jour,(le->e).Demp.mois,(le->e).Demp.an,(le->e).j.nom);
		printf("***********************************************\n");
		le=le->suiv;
	}
	printf("\n");
}
/*************ENREGISTRER UN APRES-MIDI THEMATIQUE ************/

void afficherAP (ApremTH A)
{
	printf("NbPlaces : %d\n Nom De L'après-midi : %s\n\n",A.places,A.titre);
}

void afficher(ApremTH **tapth,int nb)
{
	int i;
	for(i=0;i<nb;i++)
		afficherAP(*tapth[i]);
}

ApremTH lireAP(FILE *flot)
{
	ApremTH A;
	fscanf(flot,"%d%*c",&A.places);
	fgets(A.titre,27,flot);
	A.titre[strlen(A.titre)-1]='\0';
	return A;
}

/*	Remplissage de tapth à partir du fichier des aprem thématiques 	*/

ApremTH **ChargeAPTH (int *max,int *i)
{
	ApremTH A,**aux;
	int m=0;
	FILE *flot;
	ApremTH **tapth;
	
	flot=fopen("am_thematiques.don","r");
	if(flot == NULL)
			exit(1);
	tapth=(ApremTH**)malloc((*max)*sizeof(ApremTH*));
	if(tapth==NULL)
		{
			printf("Problème Malloc \n");
			exit(1);
		}
	A=lireAP(flot);
	while(!feof(flot))
	{
		if (m==*max)
			{
				aux=(ApremTH**)realloc(tapth,(*max+5)*sizeof(ApremTH*));
				if(aux == NULL)
				{
					printf("Problème Realloc APTH \n");
					exit(1);
				}
				tapth=aux;
				*max=*max+5;
			}	
 		tapth[m]=(ApremTH*)malloc(sizeof(ApremTH));
 		if(tapth[m]==NULL)
 		{
 			printf("Problème Allocation \n");
 			exit(1);
 		}
 		*tapth[m]=A;
		m=m+1;
		A=lireAP(flot);
	}
	fclose(flot);
	*i=m;
	return tapth;
}

int rechercheAp (ApremTH **tapth, int max, char *nom, int *trouv)
{
	int inf=0, m;
	int sup;
	sup=max-1;
	while(inf<=sup)
	{
		m=(inf+sup)/2;
		if(strcmp(nom,tapth[m]->titre)==0)
		{
			*trouv=1;
			return m;
		}
		if(strcmp(nom,tapth[m]->titre)<0)
			sup=m-1;
		else inf=m+1;
	}
	*trouv=0;
	return inf;
}
/*	tri du tableau de pointeur tapth pour Enregistrer 	*/

int plusGrand (ApremTH **tapth, int n)
{
	int i, pge=0;

	for(i=0;i<n;i++)
		if(strcmp(tapth[i]->titre,tapth[pge]->titre)>0)
			pge=i;
	return pge;
}

void echanger (ApremTH **tapth, int i, int j)
{
	ApremTH *aux;

	aux=tapth[i];
	tapth[i]=tapth[j];
	tapth[j]=aux;
}

ApremTH **trierParEchange (ApremTH **tapth, int n)
{
	int pge;

	while(n>1)
	{
		pge=plusGrand(tapth,n);
		echanger(tapth,pge,n-1);
		n=n-1;
	}
	return tapth;
}

void sauvegarde(ApremTH **tapth,int tLog)
{
	FILE *flot;
	int i;
	flot=fopen("am_thematiques.don","w"); 
	if(flot==NULL)
	{
		printf("problème d'ouverture aprem_thematiques\n");
		exit(1);
	}
	for(i=0;i<tLog;i++)
		fprintf(flot,"%d\n%s\n",tapth[i]->places,tapth[i]->titre);
	fclose(flot);
}

/*	Insertion de la nouvelle Aprem thématique dans le tableau de pointeur */

int nouveauApTH (ApremTH **tapth, int pos, ApremTH A, int tLog)
{
	int i;

	for(i=tLog;i>pos;i--)
		tapth[i]=tapth[i-1];
	tapth[pos]=(ApremTH*)malloc(sizeof(ApremTH));
	if(tapth[pos]==NULL)
	{
		printf("Problème Malloc Nouvelle ApremTH\n");
		exit(1);
	}
	strcpy(tapth[pos]->titre,A.titre);
	tapth[pos]->places=A.places;
	tLog=tLog+1;

	return tLog;
}

void EnregistrerAPTH (void)
{
	int i,p,trouv;
	int max=5;
	ApremTH **tapth, A;

	tapth=ChargeAPTH(&max,&i);
	tapth=trierParEchange(tapth,i);
	afficher(tapth,i);
	printf("Quelle après midi thématique voulez vous enregistrer ?\n");
	fgets(A.titre,27,stdin);
	A.titre[strlen(A.titre)-1]='\0';
	p=rechercheAp(tapth,i,A.titre,&trouv);
	while(trouv == 1)
	{
		printf("\n 	L'après midi %s existe déjà ! \n",A.titre);
		printf("\n======== Enregistrer une nouvelle Aprèm-thématique ======== \n\n");
		EnregistrerAPTH();
	}
	printf("L'après midi est inexistante : création de l'après-midi thématique \n");
	printf("Combien de places maximum autorisées ? :");
	scanf("%d",&A.places);
	i=nouveauApTH(tapth,p,A,i);
	printf("\n\nVoici votre nouvelle liste d'après midi-thématiques \n\n");
	afficher(tapth,i);
	sauvegarde(tapth,i);
}

/************INSCRIRE UN ADHERENT A UNE APRES MIDI THEMATIQUE **********/

ApremTH **chargerAPTH(ListeAdherent la,ApremTH **tapth,int tLog)
{	
	ApremTH AP;
	Adherent A;
	int MP;
	int p,trouv,RA;
	FILE *flot;
	int m=0;
	
	flot=fopen("inscriptions_am_th.don","r+"); 
	if(flot==NULL)
	{
		printf("problème d'ouverture inscriptions_am_th\n");
		exit(1);
	}	
	fgets(AP.titre,27,flot);
	AP.titre[strlen(AP.titre)-1]='\0';
	fscanf(flot,"%s%*c",A.identifiant);
	p=rechercheAp (tapth,tLog,AP.titre,&trouv);
	A=rechercherAdherent(la,A.identifiant,&RA);
	while(!feof(flot))
	{
		tapth[p]->lAdh=InsertionAdherent(tapth[p]->lAdh,A);
		fgets(AP.titre,27,flot);
		AP.titre[strlen(AP.titre)-1]='\0';
		fscanf(flot,"%s%*c",A.identifiant);
		p=rechercheAp (tapth,tLog,AP.titre,&trouv);
		A=rechercherAdherent(la,A.identifiant,&RA);
	}
	fclose(flot);
	return tapth;
}

void AffichageAPTH (ListeAdherent la)
{
	if(la==NULL)
	{
		printf("\n");
		return;
	}
	printf("%s\t%s\t%s\n",(la->a).nom,(la->a).prenom,(la->a).identifiant);
	AffichageAPTH(la->suiv);	
}	

void sauvegardeAPTH (ApremTH **tapth,int Ins,Adherent A)
{
	int i;
	FILE *flot;

	flot=fopen("inscriptions_am_th.don","a"); 
	if(flot==NULL)
	{
		printf("Problème d'ouverture inscriptions_am_th\n");
		exit(1);
	}
	fprintf(flot,"%s\n%s",tapth[Ins]->titre,A.identifiant);
	fclose(flot);
}

int appartientTH (ListeAdherent la, char *identifiant)
{
	while(la != NULL)
	{
		if(strcmp(identifiant,(la->a).identifiant)==0)
			return 1;
		if(strcmp(identifiant,(la->a).identifiant)<0)
			return 0;
		la=la->suiv;	
	}
	return 0;
}

int longueur (ListeAdherent la)
{
	if(la==NULL)
		return 0;
	return 1+longueur(la->suiv);
}

void InsertionAdherentAPTH (ListeAdherent la)
{
	FILE *flot;
	Adherent A;	/* Pour la liste d'adhérent */
	int RA;
	int i=0,max=5,trouv;	/*Pour les après midi-thématiques */
	int p,a;
	int nb;
	ApremTH **tapth,AP;

	tapth=ChargeAPTH(&max,&i);
	tapth=trierParEchange(tapth,i);
	afficher(tapth,i);
	printf("A Quelle après midi thématique voulez vous enregistrer l'adherent ?\n");
	fgets(AP.titre,27,stdin);
	AP.titre[strlen(AP.titre)-1]='\0';
	p=rechercheAp(tapth,i,AP.titre,&trouv);
	if(trouv == 0)
	{
		printf("\n========================================\n");
		printf("\n 	L'après midi n'existe pas ! \n");
		printf("========================================\n");
		InsertionAdherentAPTH(la);
	}
	printf("=======================================\n");
	printf("Insertion de l'Adherent !! \n");
	printf("=======================================\n\n");
	
	afficherListe(la);
	printf("Rentrer l'identifiant de l'Adhérent: exemple->P123 \n");
	scanf("%s%*c",A.identifiant);
	A=rechercherAdherent(la,A.identifiant,&RA);
	if(RA==0)	
	{
		printf("Identifiant Adherent inexistant \n");
		printf("Rentrer l'identifiant de l'Adhérent: \n");
		scanf("%s%*c",A.identifiant);
		printf("******************************\n");
		A=rechercherAdherent(la,A.identifiant,&RA);
	}
	a=appartientTH(tapth[p]->lAdh,A.identifiant);
	if(a==1)	
	{
		printf("Adherent déjà trouvé dans l'aprem thématique !! \n");
		printf("Rentrer l'identifiant de l'Adhérent: \n");
		scanf("%s%*c",A.identifiant);
		printf("******************************\n");
		a=appartientTH(tapth[p]->lAdh,A.identifiant);
	}
	tapth=chargerAPTH(la,tapth,i);
	nb=longueur(tapth[p]->lAdh);
	if(nb<tapth[p]->places)
	{
		printf("\n\n Insertion de l'adhérent %s %s à l'après midi thématique %s \n\n",A.nom,A.prenom,AP.titre);
		tapth[p]->lAdh=InsertionAdherent(tapth[p]->lAdh,A);
	}
	if (nb==tapth[p]->places)
	{
		printf("Le Nombre maximal de places pour cette après-midi thématique est atteint !\n");
		printf("\n Choisissez en une autre !! \n\n");
		InsertionAdherentAPTH(la);

	}
	if(nb>tapth[p]->places)
	{
		printf("\n Erreur : Nombre de places trop grand par rapport au nombre d'inscrits à cette ApremTH\n");
		tapth[p]->places=nb;
	}
	printf("===============================================================\n");
	printf("Affichage de la liste des Adherents à 'Aprèm-thématique %s \n",AP.titre);		
	printf("===============================================================\n");
	AffichageAPTH(tapth[p]->lAdh);
	sauvegardeAPTH(tapth,p,A);

}	

/**************************LISTE DES EMPRUNTS EN RETARD********************************/

void ListeEmpRetard(ListeEmprunt lEmp)
{
	Date Da;
	int dEs, dAs;
	FILE *flot;
	ListeEmprunt lEmpR;

	lEmpR=ListeEMvide();

	system("date +%Y-%m-%d >> dateAct.don");
	flot=fopen("dateAct.don","r");
	if(flot==NULL)
	{
		printf("erreur fichier \n");
		exit(1);
	}
	fscanf(flot,"%d%*c%d%*c%d%*c",&Da.an,&Da.mois,&Da.jour);
	fclose(flot);
	flot=fopen("dateAct.don","w+");
	fclose(flot);
	
	flot=fopen("ListeEmpRetard.bin","wb+");
	if(flot==NULL)
	{
		printf("erreur fichier \n");
		exit(1);
	}
	dAs = Da.jour * 86400;
	dAs = dAs + (Da.mois * 2592000);
	dAs = dAs + (Da.an * 31536000);

	while(lEmp!=NULL)
	{
		dEs=(lEmp->e).Demp.jour * 86400;
		dEs= dEs + ((lEmp->e).Demp.mois * 2592000);
		dEs= dEs + ((lEmp->e).Demp.an * 31536000);	
		if(dAs-dEs >= 1814400)
		{
			lEmpR=InsertionEmprunt(lEmpR,lEmp->e);
			fwrite(&(lEmpR->e),sizeof(Emprunt),1,flot);
		}

		lEmp=lEmp->suiv;
	}
	afficherListeE(lEmpR);
	fclose(flot);
}


/***************	GLOBAL   	******************/

void global(void)
{
	Adherent A;
	ListeAdherent lAdh;
	ListeEmprunt lEmp;
	Emprunt E;
	int choix;
	lAdh=ListeADvide();
	lEmp=ListeEMvide();
	FILE *flot;

	flot=fopen("ListeAdherent.don","r+");
	A=LireAdherent(flot);
	while(!feof(flot))
		{
		
			lAdh=InsertionAdherent(lAdh,A);
			A=LireAdherent(flot);
		}
	fclose(flot);

	flot=fopen("ListeEmprunt.don","r+");
	E=LireEmprunt(flot);
	while(!feof(flot))
		{
		
			lEmp=InsertionEmprunt(lEmp,E);
			E=LireEmprunt(flot);
		}
	fclose(flot);
	choix = menu();
	while (choix != 9)
	{	
		switch(choix)
		{
			case 1 :
					{
					lAdh=EnregistrerAdherent(lAdh);
					break;
					}
			case 2 : 
					{	
					lAdh=SupprimerAdherent(lAdh);
					break;
					}
				
			case 3: 
					{
					lEmp=EnregistreEmprunt(lAdh,lEmp);
					break;
					}
			case 4:
					{
					EnregistrerAPTH();
					break;
					}
			case 5: 
					{
					InsertionAdherentAPTH(lAdh);
					break;
					}
			case 6: 
					{	
					ListeEmpRetard(lEmp);
					break;
					}		
				
			case 7:
					{
					afficherListe(lAdh);
					break;
					}

			case 8:
					{
					afficherListeE(lEmp);
					break;
					}	
		}
		choix=menu();
	}
	flot=fopen("ListeAdherent.don","w+");
	while(lAdh !=NULL)
	{
	fprintf(flot,"%s\n%s\n%s\n%d\n %d/%d/%d\n ",(lAdh->a).identifiant,(lAdh->a).nom,(lAdh->a).prenom,(lAdh->a).NbEmprunts,(lAdh->a).DateAd.jour,(lAdh->a).DateAd.mois,(lAdh->a).DateAd.an);
	lAdh=lAdh->suiv;
	}
	fclose(flot);
	flot=fopen("ListeAdherent.don","w+");
	while(lAdh !=NULL)
	{
	fprintf(flot,"%s\n%s\n%s\n%d\n %d/%d/%d\n ",(lAdh->a).identifiant,(lAdh->a).nom,(lAdh->a).prenom,(lAdh->a).NbEmprunts,(lAdh->a).DateAd.jour,(lAdh->a).DateAd.mois,(lAdh->a).DateAd.an);
	lAdh=lAdh->suiv;
	}
	fclose(flot);	
}

	


