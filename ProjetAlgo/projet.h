#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>



/* CODE LOGEMENT */ 
typedef struct{
	char idlog[6];
	char cite[20];
	char type[10];
	char disp[3];
	char adapte[3];
	char idoccup[7];
}Logement;

int Chargement(Logement **TLog, int maxLog);
void AffichLogement(Logement **Log, int tailleLog);
Logement lirelog(FILE *fe);;
int RechLogementOccup(Logement **Log, int n);
void testGlobal(void);
int rechRminLog(Logement **log,int d,int n);
void permuteLogement(Logement **log, int a, int b);
void triLogement(Logement **log,int n);

/* CODE ETUDIANT */ 

typedef struct 
{
	char idetud[6];
	char civ[4];
	char nom[15];
	char prenom[10];
	char boursier[3];
	int echelon;
	char handicap[3];
} Etudiant;


typedef struct liste
{
	Etudiant etudi;
	struct liste *suivant;
	
}Maillon,*Liste;


Liste RechercheIdentiteOccup(Liste e, char idEtudRech[]);
void AffichLogementEtudiantOccup(Liste e, Logement **TLog, int tailleLog);
Liste listeVide(void);
Liste insertiontet(Liste e, Etudiant x);
void afficherEnsemble(Liste e);
Etudiant lireetud(FILE *fe);
Liste ChargementListe (Liste l);
void afficherEnsemble(Liste e);
void AffichLogementOccup(Logement **Log, Liste e, int tailleLog, char *idEtudRech);
Etudiant Saisie();
Liste InsertionEtudiantEnTete(Liste Etud,Etudiant Etudiant);
Liste InsertionTrieeEtudiant(Liste Etud, Etudiant Etudiant);


/* ATTENTE */ 
typedef struct{
	char iddem[5];
	char idetud[6];
	int echelon;
	char cite[20];
	char type[10];
}Demande;

/* Fonctions liées au tableau des demandes en Attente */ 

int ChargementAttente(Demande *Tdem[], int maxLog);
void AffichLogementAttente(Demande **dem, int tailleLog);
Demande lirelogAttente(FILE *fe);

/* Fonctions pour le tri décroissant en fonction de l'échelon */ 
int rechRminAttente(Demande **dem,int d,int n);
void permuteAttente(Demande **dem, int a, int b);
void triDemandeAttente (Demande **dem,int n);

/* Fonctions qui permettent de traiter les demandes en attente et d'enregistrer les modifications dans les deux fichiers (logements.don demandeEnAttente.don) */
void DecalageSupp(Demande**dem,int pos,int *taille);
void traitementAttente(Demande **dem, Logement **log, int* tailleDem, int tailleLog);
int RechEtudLog(Logement **TLog, int tailleLog,char *idEtudRech);
void liberationLogement (Logement **Tlog, Demande **dem, int* tailleDem, int *tailleLog);
	
/* Fonctions qui pertmettent de saisir et d'insérer une nouvelle demande en attente */
int RechercheDemandeAttente(Demande **Dem, int tailleDem,char *IdDemRech);
void SaisieDemande(Demande *Dem, Demande **TDem, int *tailleDem, Liste etud);
void InsertionDemande(Demande **TDem, int *tailleDem, Liste etud, Demande *Dem);

/* Fonctions d'enregistrement des modifications dans le fichier etudiants.don */
void EffacFic (void);
Liste ReecritureChainee (Liste etud, FILE *fe);

/* Fonctions d'enregistrement des modifications dans les fichiers DemandeEnAttente.don et logements.don */
void ReecritureAttente(Demande**Tdem,int taille);  
void ReecritureLogement (Logement** TLog,int taille); 



/* CODE POUR LE MENU */ 
void Menu(void);
char ReponseUtilisateur();
int AffichageMenu();
