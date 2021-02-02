#include <string.h>
#include <stdio.h>
#include <math.h>
#include "projet.h"
#include <stdlib.h>



void testAffichLogement() 
{

	int tailleLog, maxlog=1000; //Initialisation de la taille logique, physque et du coderetour
	Logement *TLog[1000]; //Initialisation d'un tableau de pointeur 

	tailleLog=Chargement(TLog,maxlog); //Chargement du fichier des logements dans un tableau de pointeurs, on receptionne la taille logique
	triLogement(TLog,tailleLog); // On trie le tableau de pointeurs
	AffichLogement(TLog, tailleLog);//on affiche le tableau des logements

}

void testEtudiant()
{ 
	Liste l; //Initialisation d'une liste d'étudiant
	l=ChargementListe(l); //Chargement de la liste etudiant selon le fichier "etudiants.don"
	//affichage
	afficherEnsemble(l);	//Afficher l'ensemble des maillons de la liste des etudiants
}

void testDemandeAttente(void)
{
	int tailleDem, maxlog=1000; //Initialisation de la taille des du tableau des demandes, de sa taille physique.
	Demande *Tdem[1000]; //Initialisation d'un tableau de pointeur statique

	tailleDem=ChargementAttente(Tdem,maxlog); //Chargement du tableau des demandes en attente et retourne sa taille logique
	AffichLogementAttente(Tdem, tailleDem); //affiche le contenu du tableau de pointeur des demandes en attente

}

void testLogementOccup()
{
	int tailleLog, maxlog=1000, retour; //Initialisation taille, physique et logique avec un code retour
	Logement *TLog[1000]; 
	char idEtudRech;
	Liste l, position;
 
	tailleLog=Chargement(TLog,maxlog); //Chargement du tableau de logement et retourne la taille logique
	retour=RechLogementOccup(TLog,tailleLog); //Retourne la position de l'élement recherché
	
	l=ChargementListe(l); 
	AffichLogementOccup(TLog,l,tailleLog,&idEtudRech); //affiche les logement occupé

}

void TestCreationEtudiant()
{
	Liste l, position; //Initialise la liste des Etudiants et une position
	Etudiant Etud; //Initialise un maillon etudiant

	l=ChargementListe(l); //chargement la liste des Etudiants
	afficherEnsemble(l);  //Affiche la liste
	Etud=Saisie(); //Saisir les informations liées à l'étudiant
	l=InsertionTrieeEtudiant(l,Etud); //Insertion de l'étudiant dans la liste triée
	printf("\n");	
	afficherEnsemble(l); // afficher la nouvelle liste

	EffacFic(); //Efface tout le ficher etudiants

	FILE *fe; 
	fe=fopen("etudiants.don","a");
	ReecritureChainee(l,fe); //Ecris la nouvelle liste dans le fichier "etudiants.don"
	fclose(fe); 
}

void TestCreationDemande()
{
	int tailleDem, maxlog=1000, choix; //Initialisation d'un tableau de pointeur de demande, sa taille logique, sa taille physique et d'une variable de choix
	Demande *Tdem[1000], demande;
	Liste l; //initialisation liste etudiant

	l=ChargementListe(l); //Chargement de la lsite des etudiants
	printf("Voulez vous créer une demande de logement pour cet étudiant? 0/1 (Oui/Non)\n");
	scanf("%d",&choix);

	if(choix==0)
	{
		printf("----CREATION DE LA DEMANDE D'ETUDIANT----\n");

		tailleDem=ChargementAttente(Tdem,maxlog);  //On charge les demandes en attante dans un tableaux de pointeurs et on récupère sa taille logique
		InsertionDemande(Tdem, &tailleDem,l,&demande); //On insère la demande dans le tableau de des demandes en attente
		AffichLogementAttente(Tdem, tailleDem); //On affiche de le tableau des demandes en attente après insertion

		printf("----------------TABLEAU TRIE---------\n");
		triDemandeAttente(Tdem,tailleDem); //On trie le nouveau tableau
		AffichLogementAttente(Tdem, tailleDem); // On affiche le nouveau tableau

		ReecritureAttente(Tdem, tailleDem); // On réécris le nouveau tableau dans le fichier des demandes en attente par-dessus
	} 
	else
		Menu();

}

void RechercheAttente()
{

	int tailleDem, maxlog=1000,retourRech; //Initalisation du tableau de pointeur des demandes en attente, sa taille logique et physique et son code de retour 
	Demande *Tdem[1000]; 
	char IdDemRech;


	tailleDem=ChargementAttente(Tdem,maxlog); //Charge les demandes en attente et retourne sa taille logique
	printf("%d\n",tailleDem );
	AffichLogementAttente(Tdem, tailleDem);	//Affichage du tableau des logements
	printf("Veuillez saisir l'id du logement en attente que vous voulez rechercher:\n");
	scanf("%s",&IdDemRech); 
	retourRech=RechercheDemandeAttente(Tdem, tailleDem,&IdDemRech) ; //Recherche de la postion de l'id de la demande recherché
	if (retourRech!=-1)
		printf("La demande de logement en attente recherchée est: %s %s %d %s %s\n",Tdem[retourRech]->iddem, Tdem[retourRech]->idetud, Tdem[retourRech]->echelon, Tdem[retourRech]->cite, Tdem[retourRech]->type );
	else 
		printf("Cette demande de logement n'existe pas, voulez-vous en créer une nouvelle?\n");

}

void TestAnnulation(void)
{
	int tailleLog, maxlog=1000,pos; //Initialisation du tableau des demandes, sa taille logique et physique et d'une variable de position
	Demande *Tdem[1000];
	char demS[20];

	tailleLog=ChargementAttente(Tdem,maxlog); //Chargement des demandes en attente et retourne sa taille logique
	AffichLogementAttente(Tdem, tailleLog); //Affiche le tableau des demandes en attente
	printf("----------------------------------------\n");

	printf("Sasir l'id de la demande à supprimer :\n");
	scanf("%s",demS);
	printf("----------------------------------------\n");

	pos=RechercheDemandeAttente(Tdem, tailleLog,demS); //On recherche la demande en attente à supprimer et retourne sa position
	if (pos==-1) //si o nne trouve pas la position
	{
		printf("Cet identifiant de demande n'existe pas\n");
		exit(1);
	}
	
	DecalageSupp(Tdem, pos,&tailleLog); //Supprime par décalage la demande voulu
	printf("-------TABLEAU MIS À JOUR--------");
	AffichLogementAttente(Tdem, tailleLog); //affiche le tableau des demandes en attente après suppression
	
	//Recherche maillon correspondant avec 'etudSuppr'
	//Suppression maillon concerné

	ReecritureAttente(Tdem,tailleLog);
}

 void testTraitement (void)
{
    int tailleDem,maxdem=1000,tailleLog, maxlog=1000; //Initialisation d'un tableau de logement et attente, de sa taille physqiue et logique 
    Demande *Tdem[1000];
    Logement *TLog[1000];
    char idEtudOccup;

    tailleDem=ChargementAttente(Tdem,maxdem); //Chargement du tableau en attente
    tailleLog=Chargement(TLog,maxlog); //Chargment du tableau de logement
    triDemandeAttente(Tdem,tailleDem); //tri du tableau des demandes
    triLogement(TLog,tailleLog); //tri du tableau des logements
    traitementAttente(Tdem,TLog, &tailleDem, tailleLog); 
    ReecritureAttente(Tdem,tailleDem); 
    ReecritureLogement(TLog, tailleLog);

     
}

void testLiberationLogement (void)
{   
    int tailleDem,maxdem=1000,tailleLog, maxlog=1000; //Initalisation du tableau des demandes et logements, sa taille physqie et logique 
    Demande *Tdem[1000];
    Logement *TLog[1000];
    

    tailleDem=ChargementAttente(Tdem,maxdem); //Chargement du tableau des demandes en attente et retourne sa taille logique
    AffichLogementAttente(Tdem, tailleDem); //affiche le tableau des demandes en attente
    triDemandeAttente(Tdem,tailleDem);  //tri le tableau des demades en attente
    printf("\n");
    tailleLog=Chargement(TLog,maxlog); //Chargement du tbleau des logements et retourne sa taille logique
    AffichLogement(TLog,tailleLog);
    triLogement(TLog,tailleLog); // tri le tableau des logements
    liberationLogement (TLog, Tdem, &tailleDem, &tailleLog); //libère l'espace alloué vide
    ReecritureAttente(Tdem,tailleDem); //réécris le tableau des demandes en attente dans le fichiers 'demandesEnAttente.don'
    ReecritureLogement(TLog, tailleLog); //réécris le tableau des demandes en attente dans le fichiers 'logements.don'
   

}

void Menu(void)
{
	int option;
	char choix;

	option=AffichageMenu();

	while(option>=0 && option<=9)
	{
		switch(option)
		{
			case 0:
				break;

			case 1:
			{
				testAffichLogement();//Affichage des logements
				option=AffichageMenu();
				break;
			}

			case 2:
			{
				testEtudiant();
				option=AffichageMenu();
				break;

			}
			case 3:
			{
				testLogementOccup();
				option=AffichageMenu();
				break;
			}
			case 4:
			{ 
				testDemandeAttente();
				option=AffichageMenu();
				break;
			}
			case 5 :
			{
				testTraitement();
				option=AffichageMenu();
				break;
			}
			case 6:
			{
				RechercheAttente();
				option=AffichageMenu();
				break;
			}
			case 7:
			{	
				TestCreationEtudiant();
				TestCreationDemande();
				option=AffichageMenu();
				break;
			}
			case 8:
			{
				TestAnnulation();
				option=AffichageMenu();
				break;

			}
			case 9:
			{
				testLiberationLogement();
				option=AffichageMenu();
				break;
			}
		}
	}
}

	int main(void)
{

	Menu();
	return 0;	
}